/********************************************************************************
 *  File Name:
 *    gfxconf.h
 *
 *  Description:
 *    Configuration file for uGFX
 *    https://wiki.ugfx.io/index.php/Configuration
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_UGFX_CONFIGURATION_HPP
#define DC_UGFX_CONFIGURATION_HPP

#include "gdisp_lld_config.h"

/* clang-format off */
/*-------------------------------------------------
Configuration: gadc
-------------------------------------------------*/
/*-------------------------------------------------
Configuration: gaudio
-------------------------------------------------*/
/*-------------------------------------------------
Configuration: gdisp
-------------------------------------------------*/
#define GFX_USE_GDISP         ( GFXON )

#define GDISP_DEFAULT_ORIENTATION       ( gOrientationLandscape )
#define GDISP_LINEBUF_SIZE              ( 128 )
#define GDISP_NEED_STARTUP_LOGO         ( GFXON )
#define GDISP_STARTUP_COLOR             ( GFX_BLACK )
#define GDISP_TOTAL_DISPLAYS            ( 1 )
#define GDISP_PIXELFORMAT               ( GDISP_PIXELFORMAT_RGB666 )
#define GDISP_LLD_PIXELFORMAT           ( GDISP_PIXELFORMAT )
#define GDISP_HARDWARE_STREAM_WRITE     ( GFXON )
#define GDISP_HARDWARE_STREAM_READ      ( GFXOFF )
#define GDISP_HARDWARE_STREAM_POS       ( GFXOFF )
#define GDISP_HARDWARE_DRAWPIXEL        ( GFXOFF )
#define GDISP_HARDWARE_CLEARS           ( GFXOFF )
#define GDISP_HARDWARE_FILLS            ( GFXOFF )
#define GDISP_HARDWARE_BITFILLS         ( GFXOFF )
#define GDISP_HARDWARE_SCROLL           ( GFXOFF )
#define GDISP_HARDWARE_PIXELREAD        ( GFXOFF )
#define GDISP_HARDWARE_CONTROL          ( GFXOFF )
#define GDISP_HARDWARE_QUERY            ( GFXOFF )
#define GDISP_HARDWARE_CLIP             ( GFXOFF )

/*-------------------------------------------------
Configuration: gdriver
-------------------------------------------------*/
/*-------------------------------------------------
Configuration: gevent
-------------------------------------------------*/
/*-------------------------------------------------
Configuration: gfile
-------------------------------------------------*/
/*-------------------------------------------------
Configuration: ginput
-------------------------------------------------*/
/*-------------------------------------------------
Configuration: gmisc
-------------------------------------------------*/
/*-------------------------------------------------
Configuration: gos
-------------------------------------------------*/
#define GFX_USE_OS_FREERTOS   ( GFXON )
#define GFX_CPU               ( GFX_CPU_CORTEX_M4_FP )
#define GFX_CPU_ENDIAN        ( GFX_CPU_ENDIAN_LITTLE )
#define GFX_OS_HEAP_SIZE      ( 1024 )
#define GFX_OS_NO_INIT        ( GFXON )

/*-------------------------------------------------
Configuration: gqueue
-------------------------------------------------*/
/*-------------------------------------------------
Configuration: gtimer
-------------------------------------------------*/
/*-------------------------------------------------
Configuration: gwin
-------------------------------------------------*/

/* clang-format on */

#endif /* !DC_UGFX_CONFIGURATION_HPP */
