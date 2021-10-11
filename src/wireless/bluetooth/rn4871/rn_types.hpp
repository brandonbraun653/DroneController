/********************************************************************************
 *  File Name:
 *    rn_types.hpp
 *
 *  Description:
 *    Common types used across the RN4871 driver
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef RN4871_TYPES_HPP
#define RN4871_TYPES_HPP

/* Aurora Includes */
#include <Aurora/utility>

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/serial>
#include <Chimera/thread>

/* ETL Includes */
#include <etl/string.h>
#include <etl/queue.h>

namespace RN4871
{
  /*-------------------------------------------------------------------------------
  Aliases
  -------------------------------------------------------------------------------*/
  using VersionString = etl::string<64>;
  using PacketString  = etl::string<128>;
  using PacketBuffer  = char[ PacketString::MAX_SIZE ];

  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr char CMD_TERM = '\n';

  /*-------------------------------------------------------------------------------
  Enumerations
  -------------------------------------------------------------------------------*/
  enum class StatusCode : uint8_t
  {
    OK,
    FAIL,
    NO_RESPONSE,
    TIMEOUT,
    OVERFLOW,

    NUM_OPTIONS,
    INVALID
  };


  enum class OpMode : uint8_t
  {
    UNKNOWN,
    COMMAND,
    DATA,

    NUM_OPTIONS,
    INVALID
  };

  enum class OutputPower : uint8_t
  {
    LEVEL_0, /* Maximum output power */
    LEVEL_1,
    LEVEL_2,
    LEVEL_3,
    LEVEL_4,
    LEVEL_5 /* Minimum output power */
  };

  enum class Feature : uint16_t
  {
    ENABLE_FLOW_CTRL           = 0x8000,
    NO_PROMPT                  = 0x4000,
    FAST_MODE                  = 0x2000,
    NO_BEACON_SCAN             = 0x1000,
    NO_CONNECT_SCAN            = 0x0800,
    NO_DUPLICATE_RESULT_FILTER = 0x0400,
    PASSIVE_SCAN               = 0x0200,
    UART_TRANSPARENT_NO_ACK    = 0x0100,
    REBOOT_AFTER_DISCONNECT    = 0x0080,
    RUN_SCRIPT_AFTER_POWER_ON  = 0x0040,
    SUPPORT_RN4020_STREAMING   = 0x0020,
    COMMAND_MODE_GUARD         = 0x0008,
    NONE                       = 0x0000
  };

  ENUM_CLS_BITWISE_OPERATOR( Feature, | );
  ENUM_CLS_BITWISE_OPERATOR( Feature, & );

  /*---------------------------------------------------------------------------
  Structures
  ---------------------------------------------------------------------------*/

  namespace Internal
  {
    /**
     * @brief Describes a transaction to the bluetooth module
     */
    struct Transfer
    {
      PacketString *message;                    /**< Message to send */
      PacketString *response;                   /**< Response data */
      Chimera::Thread::BinarySemaphore *signal; /**< Signal to wake up caller */
      StatusCode *result;                       /**< Result of the transaction */
      size_t timeout;                           /**< Response timeout */
      bool waitForResponse;                     /**< Wait for a response? */
      std::string_view termination;             /**< Expected termination of response */
    };

    /**
     * @brief Keeps state of an RN4871 device at runtime
     */
    struct ControlBlock
    {
      bool isInitialized;                     /**< Overall init state */
      Chimera::Thread::RecursiveMutex *lock;  /**< This structure's lock */
      Chimera::Thread::TaskId mgrID;          /**< Thread ID of manager task */
      Chimera::Serial::Channel serialChannel; /**< Serial channel device is on */
      OpMode currentMode;                     /**< Current operational mode of the device */
      size_t upTime;                          /**< Amount of time the device has been on */

      etl::queue<Transfer, 5> txfrQueue;

      ControlBlock()
      {
        currentMode   = OpMode::UNKNOWN;
        isInitialized = false;
        lock          = nullptr;
        mgrID         = Chimera::Thread::THREAD_ID_INVALID;
        serialChannel = Chimera::Serial::Channel::NOT_SUPPORTED;
        upTime        = 0;
      }
    };


  }    // namespace Internal

}    // namespace RN4871

#endif /* !RN4871_TYPES_HPP */
