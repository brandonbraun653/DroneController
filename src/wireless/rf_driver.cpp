/********************************************************************************
 *  File Name:
 *    rf_driver.cpp
 *
 *  Description:
 *    Implementation of the RF driver
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Project Includes */
#include <src/wireless/rf_driver.hpp>
#include <src/wireless/rf_driver_internal.hpp>

namespace DC::RF
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  bool initialize( Ripple::Session::RadioConfig &cfg )
  {
    Chimera::Status_t initResult = Chimera::Status::OK;

    initResult |= initNetStack( cfg );
    initResult |= runNetThreads();

    return ( initResult == Chimera::Status::OK );
  }

}  // namespace DC::RF
