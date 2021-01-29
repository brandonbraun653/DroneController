/********************************************************************************
 *  File Name:
 *    power_up.hpp
 *
 *  Description:
 *    Power up the various technologies and software libraries used on the board.
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_POWER_UP_HPP
#define DC_POWER_UP_HPP


namespace DC::SYS
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   *  Powers on all resource peripherals, modules, components, etc that
   *  are used on the controller. After this executes, the system should
   *  be in a ready-to-use state.
   *
   *  @return void
   */
  void powerUpModules();

  /**
   *  Configures all serial driver instances
   *  @return void
   */
  void powerUpSerial();

  /**
   *  Powers up the filesystem and verifies integrity
   *  @return void
   */
  void powerUpFileSystem();

}  // namespace DC::SYS

#endif  /* !DC_POWER_UP_HPP */
