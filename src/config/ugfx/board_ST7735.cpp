/********************************************************************************
 *  File Name:
 *    board_ST7735.cpp
 *
 *  Description:
 *    Implements hooks for the uGFX ST7735 low level driver.
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/spi>

/* Graphics Includes */
#include "gfx.h"
#include "board_ST7735.h"


void init_board( GDisplay *g )
{
}


void post_init_board( GDisplay *g )
{
}


void setpin_reset( GDisplay *g, gBool state )
{
}


void acquire_bus( GDisplay *g )
{
}


void release_bus( GDisplay *g )
{
}


void write_cmd( GDisplay *g, gU8 cmd )
{
}


void write_data( GDisplay *g, gU8 *data, gU16 length )
{
}


void write_data_byte( GDisplay *g, gU8 data )
{
}


void set_backlight( GDisplay *g, gU8 percent )
{
}
