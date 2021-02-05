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
#define GDISP_NEED_CONTROL              ( GFXON )
#define GDISP_NEED_MULTITHREAD          ( GFXON )
//#define GDISP_NEED_ANTIALIAS            ( GFXOFF )
//#define GDISP_NEED_KERNING              ( GFXOFF )
#define GDISP_NEED_STARTUP_LOGO         ( GFXOFF )
#define GDISP_NEED_TEXT                 ( GFXON )
//#define GDISP_NEED_TEXT_WORDWRAP        ( GFXOFF )
#define GDISP_NEED_CONVEX_POLYGON       ( GFXON )
#define GDISP_NEED_CIRCLE               ( GFXON )
#define GDISP_NEED_ARC                  ( GFXON )
#define GDISP_NEED_ELLIPSE              ( GFXON )
#define GDISP_NEED_DUALCIRCLE           ( GFXON )
//#define GDISP_NEED_UTF8                 ( GFXON )
//#define GDISP_NEED_CLIP                 ( GFXON )
#define GDISP_NEED_VALIDATION           ( GFXON )
// #define GDISP_INCLUDE_FONT_DEJAVUSANS10 ( GFXON )
// #define GDISP_INCLUDE_FONT_DEJAVUSANS20_AA ( GFXON )
// #define GDISP_INCLUDE_FONT_DEJAVUSANS32 ( GFXON )
// #define GDISP_INCLUDE_FONT_FIXED_7X14   ( GFXON )
// #define GDISP_INCLUDE_FONT_FIXED_10X20  ( GFXON )
// #define GDISP_INCLUDE_FONT_FIXED_5X8    ( GFXON )
// #define GDISP_INCLUDE_FONT_FIXED_7X14   ( GFXON )
// #define GDISP_INCLUDE_FONT_LARGENUMBERS ( GFXON )
// #define GDISP_INCLUDE_FONT_UI1          ( GFXON )
#define GDISP_INCLUDE_USER_FONTS        ( GFXON )
#define GDISP_PIXELFORMAT               ( GDISP_PIXELFORMAT_BGR565 )
#define GDISP_STARTUP_COLOR             ( GFX_BLACK )
#define GDISP_TOTAL_DISPLAYS            ( 1 )

/*-------------------------------------------------
Configuration: gdriver
-------------------------------------------------*/
/*-------------------------------------------------
Configuration: gevent
-------------------------------------------------*/
#define GFX_USE_GEVENT                  ( GFXON )

/*-------------------------------------------------
Configuration: gfile
-------------------------------------------------*/
/*-------------------------------------------------
Configuration: ginput
-------------------------------------------------*/
#define GFX_USE_GINPUT  ( GFXON )

#define GINPUT_NEED_TOGGLE              ( GFXOFF )

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
#define GFX_OS_INIT_NO_WARNING          ( GFXON )
// #define GOS_NEED_X_HEAP                 ( GFXON )
// #define GFX_OS_HEAP_SIZE                ( 10 * 1024)

/*-------------------------------------------------
Configuration: gqueue
-------------------------------------------------*/
#define GFX_USE_GQUEUE  ( GFXON )

#define GQUEUE_NEED_ASYNC               ( GFXON )

/*-------------------------------------------------
Configuration: gtimer
-------------------------------------------------*/
#define GFX_USE_GTIMER  ( GFXON )


/*-------------------------------------------------
Configuration: gwin
-------------------------------------------------*/
#define GFX_USE_GWIN ( GFXON )

#define GWIN_NEED_WINDOWMANAGER         ( GFXON )
#define GWIN_NEED_CONSOLE               ( GFXON )
#define GWIN_NEED_GRAPH                 ( GFXON )
#define GWIN_NEED_WIDGET                ( GFXON )
#define GWIN_NEED_TABSET                ( GFXON )
#define GWIN_NEED_LABEL                 ( GFXON )
#define GWIN_NEED_LABEL_ATTRIBUTE       ( GFXON )
#define GWIN_NEED_BUTTON                ( GFXON )
#define GWIN_NEED_BUTTON_LAZY_RELEASE   ( GFXON )
#define GWIN_NEED_SLIDER                ( GFXON )
#define GWIN_NEED_CHECKBOX              ( GFXON )
#define GWIN_NEED_RADIO                 ( GFXON )
#define GWIN_NEED_LIST                  ( GFXON )
#define GWIN_NEED_PROGRESSBAR           ( GFXON )
#define GWIN_NEED_PROGRESSBAR_AUTO      ( GFXON )
#define GWIN_NEED_CONTAINERS            ( GFXON )
#define GWIN_NEED_CONTAINER             ( GFXON )
#define GWIN_NEED_FRAME                 ( GFXON )

/* Console options */
#define GWIN_CONSOLE_USE_HISTORY        ( GFXON )
#define GWIN_CONSOLE_ESQSEQ             ( GFXON )
#define GWIN_CONSOLE_USE_FLOAT          ( GFXON )

/* clang-format on */

#endif /* !DC_UGFX_CONFIGURATION_HPP */
