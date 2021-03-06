/********************************************************************************
 *  File Name:
 *    logger.hpp
 *
 *  Description:
 *    Interface for logging messages with the system during runtime
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef THOR_TESTING_LOGGER_HPP
#define THOR_TESTING_LOGGER_HPP

/* Logging Includes */
#include <Aurora/logging>

namespace DC::UTL
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   *  Initializes the logger instance used for testing
   *
   *  @param[in]  lvl     Log level for the test run
   *  @return void
   */
  void initializeLogger( const Aurora::Logging::Level lvl );

}    // namespace DC::UTL

#endif /* !THOR_TESTING_LOGGER_HPP */
