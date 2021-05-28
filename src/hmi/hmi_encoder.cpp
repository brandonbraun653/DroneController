/********************************************************************************
 *  File Name:
 *    hmi_encoder.cpp
 *
 *  Description:
 *    Rotary encoder low level input processing
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/hmi>
#include <Aurora/logging>
#include <Aurora/utility>

/* Chimera Includes */
#include <Chimera/assert>
#include <Chimera/common>
#include <Chimera/gpio>
#include <Chimera/exti>
#include <Chimera/thread>

/* ETL Includes */
#include <etl/queue.h>

/* Project Includes */
#include <src/config/bsp/board_map.hpp>
#include <src/hmi/hmi_encoder.hpp>

namespace DC::HMI::Encoder
{
  /*-------------------------------------------------------------------------------
  Aliases
  -------------------------------------------------------------------------------*/
  template<size_t SIZE>
  using EventQueue = etl::queue<Aurora::HMI::Encoder::State, SIZE>;

  /*-------------------------------------------------------------------------------
  Private Structures
  -------------------------------------------------------------------------------*/
  struct ControlBlock
  {
    bool enabled;                                    /**< Key processing enabled */
    Key thisEnc;                                     /**< Which encoder this is */
    EventQueue<32> queue;                            /**< Queue for rotation events */
    Aurora::HMI::Encoder::RotationCallback onRotate; /**< Callback when a rotation occurs */
    Chimera::Thread::RecursiveMutex mutex;           /**< Resource lock */
    Aurora::HMI::Encoder::Encoder encoder;           /**< Basic encoder device driver */

    /**
     * @brief Initializes the control block to defaults
     */
    void clear()
    {
      enabled  = false;
      onRotate = {};
    }

    /**
     * @brief Operations to perform on a rotate event
     *
     * @param state
     */
    void rotateCallback( Aurora::HMI::Encoder::State &state )
    {
      /*-------------------------------------------------
      Push an event to the queue
      -------------------------------------------------*/
      mutex.lock();
      if( !queue.full() )
      {
        queue.push( state );
      }
      mutex.unlock();
    }
  };


  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static bool s_driver_enabled = false;
  static ControlBlock s_enc_ctrl[ EnumValue( Key::NUM_OPTIONS ) ];


  /*-------------------------------------------------------------------------------
  Static Functions
  -------------------------------------------------------------------------------*/
  static inline bool keyIsValid( const Key encoder )
  {
    return encoder < Key::NUM_OPTIONS;
  }


  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   *  Power up the GPIO inputs for processing inputs. By default
   *  this will leave all encoders disabled.
   *
   *  @return bool
   */
  bool initialize()
  {
    using namespace Chimera::GPIO;
    using namespace Aurora::HMI;

    s_driver_enabled = false;

    /*-------------------------------------------------
    Reset and then initialize the GPIO for each block
    -------------------------------------------------*/
    for ( size_t x = 0; x < ARRAY_COUNT( s_enc_ctrl ); x++ )
    {
      /*-------------------------------------------------
      Control block reset
      -------------------------------------------------*/
      s_enc_ctrl[ x ].clear();
      s_enc_ctrl[ x ].thisEnc = static_cast<Key>( x );

      /*-------------------------------------------------
      Prepare the input configuration
      -------------------------------------------------*/
      Aurora::HMI::Encoder::Config config;
      config.btnCfg  = {};
      config.encACfg = DC::IO::HMI::CommonInputCfg;
      config.encBCfg = DC::IO::HMI::CommonInputCfg;

      /*-------------------------------------------------
      Set up each key config. The default case will make
      it very obvious at runtime if a key was added but
      not initialized in this function.
      -------------------------------------------------*/
      switch ( s_enc_ctrl[ x ].thisEnc )
      {
        case Key::ENCODER_0:
          /* Center Button Configuration */
          config.btnCfg.validity = false;

          /* Rotary Encoder Configuration */
          config.encACfg.pin      = DC::IO::HMI::Encoder0::pinA;
          config.encACfg.port     = DC::IO::HMI::Encoder0::portA;
          config.encACfg.validity = true;

          config.encBCfg.pin      = DC::IO::HMI::Encoder0::pinB;
          config.encBCfg.port     = DC::IO::HMI::Encoder0::portB;
          config.encBCfg.validity = true;

          config.encActiveEdge = Button::ActiveEdge::BOTH_EDGES;
          break;

        case Key::ENCODER_1:
          /* Center Button Configuration */
          config.btnCfg.validity = false;

          /* Rotary Encoder Configuration */
          config.encACfg.pin      = DC::IO::HMI::Encoder1::pinA;
          config.encACfg.port     = DC::IO::HMI::Encoder1::portA;
          config.encACfg.validity = true;

          config.encBCfg.pin      = DC::IO::HMI::Encoder1::pinB;
          config.encBCfg.port     = DC::IO::HMI::Encoder1::portB;
          config.encBCfg.validity = true;

          config.encActiveEdge = Button::ActiveEdge::BOTH_EDGES;
          break;

        default:
          RT_HARD_ASSERT( false );
          break;
      };

      /*-------------------------------------------------
      Initialize the rotary encoder
      -------------------------------------------------*/
      auto rotateCB =
          Aurora::HMI::Encoder::RotationCallback::create<ControlBlock, &ControlBlock::rotateCallback>( s_enc_ctrl[ x ] );

      if ( s_enc_ctrl[ x ].encoder.initialize( config ) )
      {
        s_enc_ctrl[ x ].encoder.disable();
        s_enc_ctrl[ x ].encoder.onRotation( rotateCB );
      }
      else
      {
        Chimera::insert_debug_breakpoint();
      }
    }

    /*-------------------------------------------------
    Enable the encoders
    -------------------------------------------------*/
    enable( Encoder::Key::ENCODER_0 );
    enable( Encoder::Key::ENCODER_1 );

    s_driver_enabled = true;
    return s_driver_enabled;
  }


  /**
   *  Register a callback to execute on encoder rotation
   *
   *  @param[in]  encoder       Which encoder to register against
   *  @param[in]  cb            The callback to execute
   *  @return bool
   */
  bool onRotate( const Key encoder, Aurora::HMI::Encoder::RotationCallback &cb )
  {
    if ( keyIsValid( encoder ) )
    {
      auto k = static_cast<size_t>( encoder );
      s_enc_ctrl[ k ].mutex.lock();
      s_enc_ctrl[ k ].onRotate = cb;
      s_enc_ctrl[ k ].mutex.unlock();
      return true;
    }
    else
    {
      return false;
    }
  }


  /**
   *  Enable input processing for a particular key
   *
   *  @param[in]  encoder       Which encoder to enable
   *  @return bool
   */
  bool enable( const Key encoder )
  {
    auto k = static_cast<size_t>( encoder );
    if ( keyIsValid( encoder ) )
    {
      s_enc_ctrl[ k ].enabled = true;
      s_enc_ctrl[ k ].encoder.enable();
      return true;
    }
    else
    {
      return false;
    }
  }


  /**
   *  Disable input processing for a particular key
   *
   *  @param[in]  encoder       Which encoder to disable
   *  @return void
   */
  void disable( const Key encoder )
  {
    auto k = static_cast<size_t>( encoder );

    if ( keyIsValid( encoder ) )
    {
      s_enc_ctrl[ k ].encoder.disable();
      s_enc_ctrl[ k ].enabled = false;
    }
  }


  /**
   * @brief Gets the latest event on the encoder
   *
   * @param encoder   Which encoder to retrieve
   * @param event     The event data to fill in
   * @return true     Data retrieved
   * @return false    Error or no data available
   */
  bool nextEvent( const Key encoder, Aurora::HMI::Encoder::State &event )
  {
    /*-------------------------------------------------
    Input Protection
    -------------------------------------------------*/
    if( !keyIsValid( encoder ) )
    {
      return false;
    }

    /*-------------------------------------------------
    Check the queue for emptiness
    -------------------------------------------------*/
    Chimera::Thread::LockGuard lck( s_enc_ctrl[ EnumValue( encoder ) ].mutex );
    if( s_enc_ctrl[ EnumValue( encoder ) ].queue.empty() )
    {
      return false;
    }

    /*-------------------------------------------------
    Grab the event data
    -------------------------------------------------*/
    s_enc_ctrl[ EnumValue( encoder ) ].queue.pop_into( event );
    return true;
  }


  void doPeriodicProcessing()
  {
    /*-------------------------------------------------
    Don't do anything before enabled
    -------------------------------------------------*/
    if( !s_driver_enabled )
    {
      return;
    }

    /*-------------------------------------------------
    Process all generated events
    -------------------------------------------------*/
    Aurora::HMI::Encoder::State event;

    for( size_t idx = EnumValue( Key::ENCODER_0 ); idx < EnumValue( Key::NUM_OPTIONS ); idx++ )
    {
      while( nextEvent( static_cast<Key>( idx ), event ) )
      {
        /*-------------------------------------------------
        Print a debug message if needed
        -------------------------------------------------*/
        if constexpr( DEBUG )
        {
          LOG_DEBUG( "Encoder %d Position: %d\r\n", idx, event.absolutePosition );
        }

        /*-------------------------------------------------
        Invoke the user callback
        -------------------------------------------------*/
        Chimera::Thread::LockGuard lck( s_enc_ctrl[ idx ].mutex );
        if( s_enc_ctrl[ idx ].onRotate )
        {
          s_enc_ctrl[ idx ].onRotate( event );
        }
      }
    }
  }

}    // namespace DC::HMI::Encoder
