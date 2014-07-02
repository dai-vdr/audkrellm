/*
  AudKrellM: GKrellM Audacious Plugin

  Copyright (C) 2007 dai <d+audacious@vdr.jp>
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

#include "audkrellm-popup-menu.h"
GtkItemFactory *running_item_factory;
GtkItemFactory *not_running_item_factory;

/*
 * taken from gkrellmms-2.1.22/options.c
 */
static void toggles_func( GtkWidget *w, gpointer what ) {
  gint type = GPOINTER_TO_INT( what );

  switch ( type ) {
    case AUDKRELLM_MAINWIN:
      audacious_remote_main_win_toggle( session,
        ! audacious_remote_is_main_win( session ) );
      break;
    case AUDKRELLM_PLAYLIST:
      audacious_remote_pl_win_toggle( session,
        ! audacious_remote_is_pl_win( session ) );
      break;
    case AUDKRELLM_EQ:
      audacious_remote_eq_win_toggle( session,
        ! audacious_remote_is_eq_win( session ) );
      break;
    case AUDKRELLM_REPEAT:
      audacious_remote_toggle_repeat( session );
      break;
    case AUDKRELLM_SHUFFLE:
      audacious_remote_toggle_shuffle( session );
      break;
    case AUDKRELLM_EJECT:
      audacious_remote_eject( session );
      break;
    case AUDKRELLM_PREFS:
      audacious_remote_show_prefs_box( session );
      break;
    default:
      do_audacious_command( type );
      break;
  }
}

/*
 * taken from gkrellmms-2.1.22/options.c
 */
static void aot_func( GtkWidget *w, gpointer data ) {
  audacious_remote_toggle_aot( session, GPOINTER_TO_INT( data ) );
}

/*
 * taken from gkrellmms-2.1.22/options.c
 */
static void open_options_cb( GtkWidget *widget, gpointer data ) {
  gkrellm_open_config_window( monitor );
}

/*
 * taken from gkrellmms-2.1.22/options.c
 */
static void quit_func( GtkWidget *w, gpointer data ) {
  time_t timer;
  time_t lt;

  time( &lt );
  timer = lt;

  audacious_remote_quit( session );

  while( audacious_remote_is_running( session ) &&
         ( ( time( &lt ) - timer ) < 10 ) )  {
    /* Do nothing; wait until xmms really quits, but not longer than 10sec! */
    usleep( 0 );
  }
}

/*
 * taken from gkrellmms-2.1.22/options.c
 */
static void start_func( GtkWidget *w, gpointer data ) {
  audacious_start_func();
}

/*
 * taken from gkrellmms-2.1.22/options.c#gkrellmms_factory
 */
static GtkItemFactoryEntry running_factory_entry[] = {
  { "/-", NULL, NULL, 0, "<Separator>" },

  { N_( "/Toggles..." ), NULL, NULL, 0, "<Branch>" },
  { N_( "/Toggles.../Main Window" ), NULL,
    toggles_func, AUDKRELLM_MAINWIN, "<Item>" },
  { N_( "/Toggles.../Playlist" ), NULL,
    toggles_func, AUDKRELLM_PLAYLIST, "<Item>" },
  { N_( "/Toggles.../EQ" ), NULL,
    toggles_func, AUDKRELLM_EQ, "<Item>" },
  { N_( "/Toggles.../Repeat" ), NULL,
    toggles_func, AUDKRELLM_REPEAT, "<Item>" },
  { N_( "/Toggles.../Shuffle" ), NULL,
    toggles_func, AUDKRELLM_SHUFFLE, "<Item>" },

#if 0 /* XXX: NOT IMPLEMENTED */
  { N_( "/Toggles.../-" ), NULL, NULL, 0, "<Separator>" },
  { N_( "/Toggles.../Always on top on" ), NULL,
    aot_func, ON, "<Item>" },
  { N_( "/Toggles.../Always on top off" ), NULL,
    aot_func, OFF, "<Item>" },
#endif

  { "/Audacious...", NULL, NULL, 0, "<Branch>" },
  { N_( "/Audacious.../Previous" ), NULL,
    toggles_func, AUDKRELLM_PREV, "<Item>" },
  { N_( "/Audacious.../Play" ), NULL,
    toggles_func, AUDKRELLM_PLAY, "<Item>" },
  { N_( "/Audacious.../Pause" ), NULL,
    toggles_func, AUDKRELLM_PAUSE, "<Item>" },
  { N_( "/Audacious.../Stop" ), NULL,
    toggles_func, AUDKRELLM_STOP, "<Item>" },
  { N_( "/Audacious.../Next" ), NULL,
    toggles_func, AUDKRELLM_NEXT, "<Item>" },

  { "/-", NULL, NULL, 0, "<Separator>" },

  { N_( "/AudKrellM Options" ), NULL,
    open_options_cb, 0, "<Item>" },

  { "/-", NULL, NULL, 0, "<Separator>" },

  { N_( "/Open file(s)" ), NULL,
    toggles_func, AUDKRELLM_EJECT, "<Item>" },
#if 0 /* XXX: NOT IMPLEMENTED */
  { N_( "/Audacious Prefs" ), NULL,
    toggles_func, AUDKRELLM_PREFS, "<Item>" },
#endif

  { "/-", NULL, NULL, 0, "<Separator>" },

  { N_( "/Quit Audacious" ), NULL,
    quit_func, 0, "<Item>" },

  { "/-", NULL, NULL, 0, "<Separator>" },
};

/*
 * taken from gkrellmms-2.1.22/options.c#gkrellmms_factory_norun
 */
static GtkItemFactoryEntry not_running_factory_entry[] = {
  { "/-", NULL, NULL, 0, "<Separator>" },

  { N_( "/Launch Audacious" ), NULL,
    start_func, 0, "<Item>" },

  { "/-", NULL, NULL, 0, "<Separator>" },

  { N_( "/AudKrellM Options" ), NULL,
    open_options_cb, 0, "<Item>" },

  { "/-", NULL, NULL, 0, "<Separator>" },
};

/*
 * taken from gkrellmms-2.1.22/options.c#options_menu_factory
 */
GtkItemFactory *create_options_menu_factory( gint run_menu ) {
  gint n,i;
  GtkItemFactory *music_factory;
  GtkAccelGroup  *axel;

  axel = gtk_accel_group_new();

  gtk_window_add_accel_group( GTK_WINDOW( gkrellm_get_top_window() ), axel );

  music_factory = gtk_item_factory_new( GTK_TYPE_MENU, "<Main>", axel );

  if( run_menu ) {
    n = sizeof( running_factory_entry ) / sizeof( GtkItemFactoryEntry );
    for( i = 0; i < n; i++ ) {
      running_factory_entry[i].path = _( running_factory_entry[i].path );
    }
    gtk_item_factory_create_items( music_factory,
                                   n, running_factory_entry, NULL );

  } else {
    n = sizeof( not_running_factory_entry ) / sizeof( GtkItemFactoryEntry );
    for( i = 0; i < n; i++ ) {
      not_running_factory_entry[i].path = _( not_running_factory_entry[i].path );
    }
    gtk_item_factory_create_items( music_factory,
                                   n, not_running_factory_entry, NULL );
  }

  return music_factory;
}

/*
 * taken from gkrellmms-2.1.22/options.c
 */
void options_menu( GdkEventButton *ev ) {
  gtk_menu_popup( GTK_MENU( audacious_is_running ?
                            running_item_factory->widget : 
                            not_running_item_factory->widget ),
                  NULL, NULL, NULL, NULL, ev->button, ev->time );
}

/*
 * [EOF]
 */
