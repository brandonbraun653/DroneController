/********************************************************************************
 *  File Name:
 *    sys_debug.hpp
 *
 *  Description:
 *    Debug functionality for system level events/data
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_DBG_DEBUG_HPP
#define DC_DBG_DEBUG_HPP


namespace DC::DBG
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   * @brief Register handlers with observables to dump debug events
   * @return void
   */
  void registerDebugObservers();

  /**
   * @brief Perform periodic debug processing
   * @return void
   */
  void doPeriodicDebugProcessing();

}  // namespace DC::DBG

#endif  /* !DC_DBG_DEBUG_HPP */
