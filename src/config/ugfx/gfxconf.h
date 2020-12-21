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

#define GDISP_HARDWARE_DRAWPIXEL        ( GFXON )
#define GDISP_HARDWARE_SCROLL           ( GFXON )
#define GDISP_NEED_MULTITHREAD          ( GFXON )
#define GDISP_NEED_STARTUP_LOGO         ( GFXON )
#define GDISP_PIXELFORMAT               ( GDISP_PIXELFORMAT_BGR565 )
#define GDISP_STARTUP_COLOR             ( GFX_BLACK )
#define GDISP_TOTAL_DISPLAYS            ( 1 )

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
#define GFX_USE_OS_FREERTOS             ( GFXON )
#define GFX_CPU                         ( GFX_CPU_CORTEX_M4_FP )
#define GFX_CPU_ENDIAN                  ( GFX_CPU_ENDIAN_LITTLE )
#define GFX_OS_NO_INIT                  ( GFXON )

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
