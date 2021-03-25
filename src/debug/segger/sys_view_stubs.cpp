/********************************************************************************
 *  File Name:
 *    sys_view_stubs.cpp
 *
 *  Description:
 *    Stub functions for the Segger System View drivers
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Segger Includes */
#include "SEGGER_SYSVIEW.h"

#include "FreeRTOSConfig.h"


extern const SEGGER_SYSVIEW_OS_API SYSVIEW_X_OS_TraceAPI;

#define SYSVIEW_APP_NAME        "FreeRTOS Demo Application"

// The target device name
#define SYSVIEW_DEVICE_NAME     "Cortex-M4"

// Frequency of the timestamp. Must match SEGGER_SYSVIEW_GET_TIMESTAMP in SEGGER_SYSVIEW_Conf.h
#define SYSVIEW_TIMESTAMP_FREQ  (configCPU_CLOCK_HZ)

// System Frequency. SystemcoreClock is used in most CMSIS compatible projects.
#define SYSVIEW_CPU_FREQ        configCPU_CLOCK_HZ

// The lowest RAM address used for IDs (pointers)
#define SYSVIEW_RAM_BASE        (0x10000000)

#define DEMCR         (*(volatile U32*) (0xE000EDFCuL))  // Debug Exception and Monitor Control Register
#define TRACEENA_BIT  (1uL << 24)                        // Trace enable bit
#define DWT_CTRL      (*(volatile U32*) (0xE0001000uL))  // DWT Control Register
#define NOCYCCNT_BIT  (1uL << 25)                        // Cycle counter support bit
#define CYCCNTENA_BIT (1uL << 0)                         // Cycle counter enable bit


/*-------------------------------------------------------------------------------
Public Functions
-------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

  static void _cbSendSystemDesc( void )
  {
    SEGGER_SYSVIEW_SendSysDesc( "N=" SYSVIEW_APP_NAME ",D=" SYSVIEW_DEVICE_NAME ",O=FreeRTOS" );
    SEGGER_SYSVIEW_SendSysDesc( "I#15=SysTick" );
  }

  void SEGGER_SYSVIEW_Conf( void )
  {
#if ENABLE_DWT_CYCCNT
  //
  // If no debugger is connected, the DWT must be enabled by the application
  //
  if ((DEMCR & TRACEENA_BIT) == 0) {
    DEMCR |= TRACEENA_BIT;
  }
#endif
  //
  //  The cycle counter must be activated in order
  //  to use time related functions.
  //
  if ((DWT_CTRL & NOCYCCNT_BIT) == 0) {       // Cycle counter supported?
    if ((DWT_CTRL & CYCCNTENA_BIT) == 0) {    // Cycle counter not enabled?
      DWT_CTRL |= CYCCNTENA_BIT;              // Enable Cycle counter
    }
  }

    SEGGER_SYSVIEW_Init( SYSVIEW_TIMESTAMP_FREQ, SYSVIEW_CPU_FREQ, &SYSVIEW_X_OS_TraceAPI, _cbSendSystemDesc );
    SEGGER_SYSVIEW_SetRAMBase( SYSVIEW_RAM_BASE );
  }


  U32 SEGGER_SYSVIEW_X_GetTimestamp( void )
  {
    return 0;
  }


  U32 SEGGER_SYSVIEW_X_GetInterruptId( void )
  {
    return 0;
  }


  void SEGGER_SYSVIEW_X_StartComm( void )
  {
  }


  void SEGGER_SYSVIEW_X_OnEventRecorded( unsigned NumBytes )
  {
  }


#ifdef __cplusplus
} /* extern "C" */
#endif
