/********************************************************************************
 *  File Name:
 *    hmi_encoder_msg_pump.cpp
 *
 *  Description:
 *
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/hmi>
#include <Aurora/logging>

/* Chimera Includes */
#include <Chimera/thread>

/* Project Includes */
#include <src/hmi/hmi_encoder.hpp>
#include <src/hmi/hmi_encoder_msg_pump.hpp>

namespace DC::HMI::Encoder
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static Chimera::Thread::Mutex s_data_lock; /**< Thread safety access */
  static ReportedState s_all_states;         /**< Cached IO state */

  /*-------------------------------------------------------------------------------
  Static Functions
  -------------------------------------------------------------------------------*/
  static void notifyEncoder0Rotate( Aurora::HMI::Encoder::State &state )
  {
    Chimera::Thread::LockGuard lck( s_data_lock );
    s_all_states.encoder0 = state;
  }


  static void notifyEncoder1Rotate( Aurora::HMI::Encoder::State &state )
  {
    Chimera::Thread::LockGuard lck( s_data_lock );
    s_all_states.encoder1 = state;
  }


  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void initMessagePump()
  {
    using namespace Aurora::HMI::Encoder;

    RotationCallback cb = RotationCallback::create<notifyEncoder0Rotate>();
    onRotate( Key::ENCODER_0, cb );

    cb = RotationCallback::create<notifyEncoder1Rotate>();
    onRotate( Key::ENCODER_1, cb );
  }


  void getCurrentState( ReportedState &state )
  {
    Chimera::Thread::LockGuard lck( s_data_lock );
    state = s_all_states;
  }

}  // namespace DC::HMI::Encoder
