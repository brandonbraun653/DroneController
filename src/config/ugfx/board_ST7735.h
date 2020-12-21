/********************************************************************************
 *  File Name:
 *    board_ST7735.h
 *
 *  Description:
 *    Board definition file for the ST7735 driver
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_UGFX_ST7735_BOARD_CONFIG_HPP
#define DC_UGFX_ST7735_BOARD_CONFIG_HPP

/*-------------------------------------------------------------------------------
Literals
-------------------------------------------------------------------------------*/
#define ST7735_TYPE ( BOARD_TYPE_R )

/*-------------------------------------------------------------------------------
Public Functions
-------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
  void init_board( GDisplay *g );
  void post_init_board( GDisplay *g );
  void setpin_reset( GDisplay *g, gBool state );
  void acquire_bus( GDisplay *g );
  void release_bus( GDisplay *g );
  void write_cmd( GDisplay *g, gU8 cmd );
  void write_data( GDisplay *g, gU16 data );
  void write_data_byte( GDisplay *g, gU8 data );
  void set_backlight( GDisplay *g, gU8 percent );
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !DC_UGFX_ST7735_BOARD_CONFIG_HPP */
