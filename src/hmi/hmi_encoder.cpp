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

/* Chimera Includes */
#include <Chimera/assert>
#include <Chimera/common>
#include <Chimera/gpio>
#include <Chimera/exti>
#include <Chimera/thread>

/* Project Includes */
#include <src/config/bsp/board_map.hpp>
#include <src/hmi/hmi_encoder.hpp>

namespace DC::HMI::Encoder
{
  /*-------------------------------------------------------------------------------
  Private Structures
  -------------------------------------------------------------------------------*/
  struct ControlBlock
  {
    bool enabled;                                      /**< Key processing enabled */
    Key thisEnc;                                       /**< Which encoder this is */
    Aurora::HMI::Button::EdgeCallback onCenterPress;   /**< Callback when key is pressed */
    Aurora::HMI::Button::EdgeCallback onCenterRelease; /**< Callback when key is released */
    Aurora::HMI::Encoder::RotationCallback onRotate;   /**< Callback when a rotation occurs */
    Chimera::GPIO::State btnActiveState;               /**< GPIO state that is considered as active */
    Chimera::Thread::RecursiveMutex mutex;          /**< Resource lock */
    Aurora::HMI::Encoder::Encoder encoder;

    void clear()
    {
      enabled         = false;
      onCenterPress   = {};
      onCenterRelease = {};
      onRotate        = {};
      btnActiveState  = Chimera::GPIO::State::LOW;
    }


    void edgeCallback( Aurora::HMI::Button::ActiveEdge edge )
    {
      using namespace Aurora::HMI::Button;
      using namespace Chimera::GPIO;

      switch ( edge )
      {
        case ActiveEdge::RISING_EDGE:
          if ( ( btnActiveState == State::HIGH ) && onCenterPress )
          {
            onCenterPress( edge );
          }
          else if ( onCenterRelease )    // btnActiveState == LOW
          {
            onCenterRelease( edge );
          }
          // else no registered callbacks
          break;

        case ActiveEdge::FALLING_EDGE:
          if ( ( btnActiveState == State::LOW ) && onCenterPress )
          {
            onCenterPress( edge );
          }
          else if ( onCenterRelease )    // btnActiveState == HIGH
          {
            onCenterRelease( edge );
          }
          // else no registered callbacks
          break;

        default:
          break;
      };
    }


    void rotateCallback( Aurora::HMI::Encoder::State &state )
    {
      if ( onRotate )
      {
        onRotate( state );
      }
    }
  };


  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static ControlBlock s_enc_ctrl[ static_cast<size_t>( Key::NUM_OPTIONS ) ];


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
  bool initialize()
  {
    using namespace Chimera::GPIO;
    using namespace Aurora::HMI;

    /*-------------------------------------------------
    Reset and then initialize the GPIO for each block
    -------------------------------------------------*/
    for ( auto x = 0; x < ARRAY_COUNT( s_enc_ctrl ); x++ )
    {
      Chimera::Status_t result = Chimera::Status::OK;

      /*-------------------------------------------------
      Control block reset
      -------------------------------------------------*/
      s_enc_ctrl[ x ].clear();
      s_enc_ctrl[ x ].thisEnc = static_cast<Key>( x );

      /*-------------------------------------------------
      Prepare the input configuration
      -------------------------------------------------*/
      Aurora::HMI::Encoder::Config config;
      config.btnCfg  = DC::IO::HMI::CommonInputCfg;
      config.encACfg = DC::IO::HMI::CommonInputCfg;
      config.encBCfg = DC::IO::HMI::CommonInputCfg;

      /*-------------------------------------------------
      Set up each key config. The default case will make
      it very obvious at runtime if a key was added but
      not initialized in this function.
      -------------------------------------------------*/
      switch ( s_enc_ctrl[ x ].thisEnc )
      {
        case Key::ENCODER_1:
          /* Center Button Configuration */
          // s_enc_ctrl[ x ].btnActiveState = State::LOW;
          // config.btnCfg.pin              = DC::IO::HMI::Encoder0::pin;
          // config.btnCfg.port             = DC::IO::HMI::Encoder0::p;
          // config.btnCfg.validity         = true;
          // config.btnActiveEdge           = Button::ActiveEdge::BOTH_EDGES;
          // config.btnDebounceTime         = 30;
          // config.btnSampleRate           = 10;
          // config.btnNumSamples           = 2;

          /* Rotary Encoder Configuration */
          config.encACfg.pin      = DC::IO::HMI::Encoder0::pinA;
          config.encACfg.port     = DC::IO::HMI::Encoder0::portA;
          config.encACfg.validity = true;

          config.encBCfg.pin      = DC::IO::HMI::Encoder0::pinB;
          config.encBCfg.port     = DC::IO::HMI::Encoder0::portB;
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
      auto centerCB = Button::EdgeCallback::create<ControlBlock, &ControlBlock::edgeCallback>( s_enc_ctrl[ x ] );
      auto rotateCB =
          Aurora::HMI::Encoder::RotationCallback::create<ControlBlock, &ControlBlock::rotateCallback>( s_enc_ctrl[ x ] );

      if ( s_enc_ctrl[ x ].encoder.initialize( config ) )
      {
        s_enc_ctrl[ x ].encoder.disable();
        s_enc_ctrl[ x ].encoder.onRotation( rotateCB );
        s_enc_ctrl[ x ].encoder.onCenterPush( centerCB );
      }
      else
      {
        Chimera::insert_debug_breakpoint();
      }
    }

    return true;
  }


  bool onCenterPress( const Key encoder, Aurora::HMI::Button::EdgeCallback &cb )
  {
    if ( keyIsValid( encoder ) )
    {
      auto k = static_cast<size_t>( encoder );
      s_enc_ctrl[ k ].mutex.lock();
      s_enc_ctrl[ k ].onCenterPress = cb;
      s_enc_ctrl[ k ].mutex.unlock();
      return true;
    }
    else
    {
      return false;
    }
  }


  bool onCenterRelease( const Key encoder, Aurora::HMI::Button::EdgeCallback &cb )
  {
    if ( keyIsValid( encoder ) )
    {
      auto k = static_cast<size_t>( encoder );
      s_enc_ctrl[ k ].mutex.lock();
      s_enc_ctrl[ k ].onCenterRelease = cb;
      s_enc_ctrl[ k ].mutex.unlock();
      return true;
    }
    else
    {
      return false;
    }
  }


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


  void disable( const Key encoder )
  {
    auto k = static_cast<size_t>( encoder );

    if ( keyIsValid( encoder ) )
    {
      s_enc_ctrl[ k ].encoder.disable();
      s_enc_ctrl[ k ].enabled = false;
    }
  }

}    // namespace DC::HMI::Encoder
