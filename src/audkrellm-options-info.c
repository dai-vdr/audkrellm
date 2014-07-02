/*
  AudKrellM: GKrellM Audacious Plugin

  Copyright (C) 2007-2011 dai <d+audacious@vdr.jp>
  All rights reserved.

  Based on: GKrellMMS: GKrellM XMMS Plugin
  Copyright (C) 2000-2004 Sander Klein Lebbink

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
*/

#include "audkrellm.h"
#include "audkrellm-options.h"

/*
 * taken from gkrellmms-2.1.22/options.c#create_gkrellmms_config
 */
void audkrellm_create_options_info( GtkWidget *notebook ) {
  GtkWidget *vbox, *text, *label, *about_label;
  gchar *about_text = NULL;
  gint i;

  const static gchar *help_text[] = {

  N_( "AudKrellM is a GKrellM Audacious-plugin which allows you to control\n"
      "Audacious from within GKrellM. It features some cool things, such as:\n" ),
      "\n",
  N_( "- A scrolling title.\n"
      "- A Krell which indicates where you are in a song.\n"
      "- Themeable buttons for controlling Audacious.\n"
      "- A gtk-popup-menu with misc. Audacious-functions.\n" ),
      "\n",

  N_( "<b>How to use AudKrellM:\n" ),
      "\n",
  N_( "You can do some cool stuff with the AudKrellM-Krell,"
      "by using your mouse.\n" ),
      "\n",

  N_( "<b>Mouse actions:\n" ),
      "\n",
  N_( "<b>\tLeft mouse-button: " ),
  N_( "Jump through song.\n" ),

  N_( "<b>\tMiddle mouse-button: " ),
  N_( "Pause/stop/play Audacious (configurable),\n"
      "\t or launch Audacious if it's not running.\n" ),

  N_( "<b>\tRight mouse-button: " ),
  N_( "Popup-menu.\n" ),
      "\n",

  N_( "<b>The led indicator on the Krell indicates several things:\n" ),
      "\n",

  N_( "<b>\tConstant red: " ),
  N_( "Audacious is turned off.\n" ),

  N_( "<b>\tConstant green: " ),
  N_( "Audacious is playing.\n" ),

  N_( "<b>\tRed, blinking green: " ),
  N_( "Audacious is stopped.\n" ),

  N_( "<b>\tGreen, blinking red: " ),
  N_( "Audacious is paused.\n" ),
      "\n",

  N_( "<b>Configurabilities:\n" ),
      "\n",
  N_( "AudKrellM has some configurabilities for if you like to\n"
      "configure some stuff:\n" ),
      "\n",

  N_( "<b>\tAudacious Executable:\n" ),

  N_( "\tHow the Audacious-executable (+ eventually path)\n"
      "\tis called on your computer. Default is audacious\n" ),
      "\n",

  N_( "<b>\tKrell label:\n" ),
  N_( "\tThe text-label you want in the krell when audacious isn't running/playing.\n" ),
      "\n",
  
  N_( "<b>\tScroll separator:\n" ),
  N_( "\tThe little text that will be appended at the end of the scrolled text.\n"
      "\tIt defaults to ' ++++ ' (that's 1 space, 4 +'s and 1 space).\n" ),
      "\n",
      "\n",

  N_( "<b>\tAudacious Auto Launch:\n" ),
  N_( "\tAuto launch Audacious when starting AudKrellM.\n" ),
      "\n",
  
  N_( "<b>\tAuto Mainwindow Close:\n" ),
  N_( "\tAutomatically close the Audacious-mainwindow \n"
      "\twhen AudKrellM starts, and Audacious is already running, or when\n"
      "\tlaunching Audacious while AudKrellM runs. This option also enables the\n"
      "\tmainwindow back when you quit gkrellm (some people really do).\n" ),
      "\n",

  N_( "<b>\tAuto hide all Audacious windows:\n" ),
  N_( "\tAutomatically hide all Audacious windows when AudKrellM starts.\n" ),
      "\n",

  N_( "<b>\tDraw minus (-) with remaining time:\n" ),
  
  N_( "\tDraw a minus (-) before the remaining time, when you have\n"
      "\tthe output-time displaying remaining time.\n" ),
      "\n",

  N_( "<b>\tEnable scrolling title:\n" ),
  N_( "\tEnable/disable the scrolling title-panel.\n" ),
      "\n",
      "\n",
  
  N_( "<b>\tDraw in time bar:\n"),
  N_( "\tCheck whether to draw the output time or 'audacious' in\n"
      "\tthe time-krell panel. \n" ),
      "\n",

  N_( "<b>\tMMB on krell click:\n" ),
  N_( "\tCheck whether AudKrellM should pause/continue or\n"
      "\tstop/play the current song on a MMB-click on the krell. MMB Click will\n"
      "\talways start playing the song if Audacious isn't playing. \n" ),
      "\n",

  N_( "<b>\tOutput time format:\n" ),
  N_( "\tDecide whether to draw the elapsed time, or the remaining time\n"
      "\tas output-time in the Krell.\n" )
  };

  /* Help */
  vbox = gkrellm_gtk_framed_notebook_page( notebook, _( "Help" ) );
  text = gkrellm_gtk_scrolled_text_view( vbox, NULL,
                                         GTK_POLICY_AUTOMATIC,
                                         GTK_POLICY_AUTOMATIC );

  for( i = 0; i < sizeof( help_text ) / sizeof( gchar* ); i++ ) {
    gkrellm_gtk_text_view_append( text, _( help_text[ i ] ) );
  }
  gtk_text_view_set_editable( GTK_TEXT_VIEW( text ), FALSE );

  /* About */
  about_text = g_strdup_printf(
    _( "AudKrellM %s\n"
       "GKrellM Audacious Plugin\n"
       "\n"
       "Copyright (C) 2007-2011 dai <d+audacious@vdr.jp>\n"
       "\n"
       "Based on: GKrellMMS: GKrellM XMMS Plugin\n"
       "Copyright (C) 2000-2002 Sander Klein Lebbink <sander@cerberus.demon.nl>\n"
       "Current GKrellMMS Maintainer: Sjoerd Simons <sjoerd@luon.net>\n"
       "\n"
       "Released under the GNU General Public License\n" ), PACKAGE_VERSION );
  about_label = gtk_label_new( about_text );
  g_free( about_text );
  label = gtk_label_new( _( "About" ) );
  gtk_notebook_append_page( GTK_NOTEBOOK( notebook ), about_label, label );
}

/*
 * [EOF]
 */
