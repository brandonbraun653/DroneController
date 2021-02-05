/********************************************************************************
 *  File Name:
 *    tsk_graphics.cpp
 *
 *  Description:
 *    Implementation of the graphics thread
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/thread>

/* Project Includes */
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_graphics.hpp>

/* uGFX Includes */
#include "gfx.h"
#include <src/gwin/gwin.h>
#include <src/gdisp/gdisp.h>

namespace DC::Tasks::GFX
{
  static GHandle tabContainer;
  static GTabsetObject tabObject;
  static GDisplay *display;
  static gFont font;

  static GListener gl;
  static GHandle ghConsole;
  static GTimer FlashTimer;

  static GHandle ghTabset;
  static GHandle ghPgButtons, ghPgSliders, ghPgCheckboxes, ghPgLabels, ghPgRadios, ghPgLists, ghPgImages, ghPgProgressbars;
  static GHandle ghButton1, ghButton2, ghButton3, ghButton4;
  static GHandle ghSlider1, ghSlider2, ghSlider3, ghSlider4;
  static GHandle ghCheckbox1, ghCheckbox2, ghCheckbox3, ghCheckDisableAll;
  static GHandle ghLabelSlider1, ghLabelSlider2, ghLabelSlider3, ghLabelSlider4, ghLabelRadio1;
  static GHandle ghRadio1, ghRadio2;
  static GHandle ghRadioBlack, ghRadioWhite, ghRadioYellow;
  static GHandle ghList1, ghList2, ghList3, ghList4;
  static GHandle ghImage1;
  static GHandle ghProgressbar1;

/* Some useful macros */
#define ScrWidth gdispGetWidth()
#define ScrHeight gdispGetHeight()

#define BUTTON_PADDING 20
#define TAB_HEIGHT 30
#define LABEL_HEIGHT 15
#define BUTTON_WIDTH 50
#define BUTTON_HEIGHT 30
#define LIST_WIDTH 75
#define LIST_HEIGHT 80
#define SLIDER_WIDTH 20
#define CHECKBOX_WIDTH 80
#define CHECKBOX_HEIGHT 20
#define RADIO_WIDTH 50
#define RADIO_HEIGHT 20
#define COLOR_WIDTH 80
#define DISABLEALL_WIDTH 100
#define GROUP_TABS 0
#define GROUP_YESNO 1
#define GROUP_COLORS 2

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void GraphicsThread( void *arg )
  {
    using namespace Chimera::Threading;

    waitInit();

    /*-------------------------------------------------
    This function never returns and runs all the needed
    graphics functionality, provided by uGFX.
    -------------------------------------------------*/
    gfxInit();

    /*-------------------------------------------------
    Basic setup
    -------------------------------------------------*/
    display = gdispGetDisplay( 0 );
    font    = gdispOpenFont( "DejaVuSans12" );
    gwinSetDefaultFont( font );
    gwinSetDefaultStyle( &WhiteWidgetStyle, TRUE );
    gdispGClear( GDISP, White );
    gdispSetOrientation( GDISP_ROTATE_90 );

    auto x = ScrWidth;
    auto y = ScrHeight;

    GWidgetInit wi;
    gCoord border, pagewidth;

    gwinWidgetClearInit( &wi );

    // Calculate page borders based on screen size
    border = ScrWidth < 450 ? 1 : 5;

    // Create the Tabs
    wi.g.show      = gTrue;
    wi.g.x         = border;
    wi.g.y         = 0;
    wi.g.width     = ScrWidth - 2 * border;
    wi.g.height    = ScrHeight - wi.g.y - border;
    ghTabset       = gwinTabsetCreate( 0, &wi, GWIN_TABSET_BORDER );
    this_thread::yield();

    ghPgButtons    = gwinTabsetAddTab( ghTabset, "BTN", gFalse );
    this_thread::yield();

    gwinDrawString( ghTabset, 15, 30, "Hello" );

    // ghPgSliders    = gwinTabsetAddTab( ghTabset, "Sliders", gFalse );
    // this_thread::yield();

    // ghPgCheckboxes = gwinTabsetAddTab( ghTabset, "Checkbox", gFalse );
    // this_thread::yield();
    // ghPgRadios			= gwinTabsetAddTab(ghTabset, "Radios", gFalse);
    // ghPgLists			= gwinTabsetAddTab(ghTabset, "Lists", gFalse);
    // ghPgLabels			= gwinTabsetAddTab(ghTabset, "Labels", gFalse);
    // ghPgImages			= gwinTabsetAddTab(ghTabset, "Images", gFalse);
    // ghPgProgressbars	= gwinTabsetAddTab(ghTabset, "Progressbar", gFalse);

    //pagewidth = gwinGetInnerWidth( ghTabset ) / 2;

    // Console - we apply some special colors before making it visible
    //	We put the console on the tabset itself rather than a tab-page.
    //	This makes it appear on every page :)
    // wi.g.parent = ghTabset;
    // wi.g.x      = pagewidth;
    // wi.g.width  = pagewidth;
    // ghConsole   = gwinConsoleCreate( 0, &wi.g );
    // gwinSetColor( ghConsole, GFX_BLACK );
    // gwinSetBgColor( ghConsole, HTML2COLOR( 0xF0F0F0 ) );

    size_t lastWoken;
    while ( true )
    {
      lastWoken = Chimera::millis();

      /*-------------------------------------------------
      Redraw periodically
      -------------------------------------------------*/
      // gwinRedrawDisplay( display, false );
      Chimera::delayMilliseconds( lastWoken, 50 );
    }
  }
}    // namespace DC::Tasks::GFX
