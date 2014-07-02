/*
  AudKrellM: GKrellM Audacious Plugin

  Copyright (C) 2007-2011 dai <d+audacious@vdr.jp>
  All rights reserved.

  Based on: GKrellMMS 2.1.22: GKrellM XMMS Plugin
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

GkrellmStyle *audkrellm_style;
gint          audkrellm_style_id;

DBusGProxy *audkrellm_session;
gboolean audacious_is_running;
gboolean audacious_is_playing;

static GkrellmMonitor *monitor;
static GkrellmTicks   *pGK;

#include "audkrellm-playlist.h"
#include "audkrellm-options.h"
#include "audkrellm-control-panel.h"
#include "audkrellm-scroll-panel.h"
#include "audkrellm-tooltip.h"
#include "audkrellm-popup-menu.h"
#include "audkrellm-button-bar.h"

/*
 * drag and drop support
 */
enum {
  DROP_PLAINTEXT,
  DROP_URLENCODED,
  DROP_STRING,
  NUM_DROP_TYPES
};
const static GtkTargetEntry drop_types[] = {
  { "text/plain",    0, DROP_PLAINTEXT  },
  { "text/uri-list", 0, DROP_URLENCODED },
  { "STRING",        0, DROP_STRING     }
};

/*
 * taken from audacious-1.3.99/src/audacious/dbus.c
 */
static DBusGProxy *audacious_get_dbus_proxy( void ) {
  DBusGConnection *connection = NULL;
  GError *err = NULL;

  connection = dbus_g_bus_get( DBUS_BUS_SESSION, &err );
  if( connection == NULL ) {
    g_warning( "Unable to connect to dbus: %s", err->message );
    g_error_free( err );
    return NULL;
  }

  return dbus_g_proxy_new_for_name( connection,
                                    AUDACIOUS_DBUS_SERVICE,
                                    AUDACIOUS_DBUS_PATH,
                                    AUDACIOUS_DBUS_INTERFACE );
}

/*
 * taken from gkrellmms-2.1.22/options.c#xmms_start_func
 */
void audkrellm_start_audacious( void ) {
  gint      timer;
  time_t    lt;
  gchar   **argv = 0;
  GError   *err  = NULL;
  gboolean  res;

  if( !g_shell_parse_argv( audkrellm_opt_exec_command, NULL, &argv, &err ) ) {
    gkrellm_message_window( _( "AudKrellM Error" ), err->message, NULL );
    g_error_free( err );
    return;
  }

  res = g_spawn_async( "/", argv, NULL,
                       G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, &err);

  if( !res && err ) {
    gkrellm_message_window( _( "AudKrellM Error" ), err->message, NULL );
    g_error_free( err );
  }

  /*
   | wait until audacious has started, but no longer than 10 secs.
   | This is so that there are actually windows to hide when
   | we get to down to the auto_hide_all part.
   */
  /* FIXME supposed ugly evil code */
  timer = time( &lt );
  while( ! audacious_remote_is_running( audkrellm_session ) &&
         ( ( time( &lt ) - timer ) < 10 ) ) {
    usleep( 0 );
  }
  audacious_is_running = audacious_remote_is_running( audkrellm_session );
  if( audkrellm_opt_auto_hide_all && audacious_is_running ) {
    audacious_remote_main_win_toggle( audkrellm_session, FALSE );
    audacious_remote_pl_win_toggle( audkrellm_session, FALSE );
    audacious_remote_eq_win_toggle( audkrellm_session, FALSE );
  }
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c#do_xmms_command
 */
void audkrellm_do_audacious_command( gint i ) {
  if( ! audacious_is_running ) {
    return;
  }

  switch( i ) {
    case AUDKRELLM_PREV:
      audacious_remote_playlist_prev( audkrellm_session );
      break;

    case AUDKRELLM_PLAY:
      if( audacious_remote_is_playing( audkrellm_session ) &&
        ! audacious_remote_is_paused( audkrellm_session ) ) {
        audacious_remote_pause( audkrellm_session );
      } else {
        audacious_remote_play( audkrellm_session );
      }
      break;

    case AUDKRELLM_PAUSE:
      audacious_remote_pause( audkrellm_session );
      break;

    case AUDKRELLM_STOP:
      audacious_remote_stop( audkrellm_session );
      // FIXME: audkrellm_time_krell->previous = t = 0;
      break;

    case AUDKRELLM_NEXT:
      audacious_remote_playlist_next( audkrellm_session );
      break;

    case AUDKRELLM_EJECT:
      audacious_remote_eject( audkrellm_session );
      break;
  }
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
static void drag_data_received( GtkWidget *window, GdkDragContext *context,
                                gint x, gint y, GtkSelectionData *data,
                                guint info, guint time, gpointer date ) {
  if( data->data ) {
    audacious_remote_playlist_clear( audkrellm_session );
    audacious_remote_playlist_add_url_string( audkrellm_session,
                                              (gchar*)data->data );
    audacious_remote_play( audkrellm_session );
    audkrellm_update_playlist();
  }
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
static gint panel_expose_event( GtkWidget *widget, GdkEventExpose *ev,
                                GkrellmPanel *p ) {
  gdk_draw_pixmap( widget->window,
                   widget->style->fg_gc[ GTK_WIDGET_STATE( widget ) ],
                   p->pixmap, ev->area.x, ev->area.y, ev->area.x, ev->area.y,
                   ev->area.width, ev->area.height );
  return FALSE;
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c#update_gkrellmms
 */
static void update_audkrellm( void ) {
  if( pGK->second_tick ) {
    audkrellm_set_panel_status();
    audkrellm_set_button_status();
  }
  audkrellm_update_control_panel();
}

/*
 * taken from gkrellmms-2.1.22/src/gkrellmms.c#create_gkrellmms
 *            audacious-1.3.99/src/audtool/audtool.c#audtool_connect
 */
void create_audkrellm( GtkWidget *vbox, gint first_create ) {
  if( first_create ) {
    audkrellm_session = audacious_get_dbus_proxy();

    audacious_is_running = audacious_remote_is_running( audkrellm_session );
    if( audkrellm_opt_auto_start && ! audacious_is_running ) {
      audkrellm_start_audacious();
    }

    if( audkrellm_opt_auto_main_close && audacious_is_running ) {
      audacious_remote_main_win_toggle( audkrellm_session, FALSE );
      audacious_remote_pl_win_toggle( audkrellm_session, FALSE );
      audacious_remote_eq_win_toggle( audkrellm_session, FALSE );
    }

    audkrellm_init_playlist();

    audkrellm_scroll_panel  = gkrellm_panel_new0();
    audkrellm_control_panel = gkrellm_panel_new0();
  } else {
    audkrellm_update_playlist();
  }

  audkrellm_style = gkrellm_meter_style( DEFAULT_STYLE );
  if( audkrellm_scroll_style ) {
    g_free( audkrellm_scroll_style );
  }
  audkrellm_scroll_style = gkrellm_copy_style( audkrellm_style );

  audkrellm_create_scroll_panel( vbox );
  audkrellm_create_control_panel( vbox );

  if( first_create ) {
    g_signal_connect( G_OBJECT( audkrellm_scroll_panel->drawing_area ),
                      "expose_event",
                      G_CALLBACK( panel_expose_event ), audkrellm_scroll_panel );
    g_signal_connect( G_OBJECT( audkrellm_scroll_panel->drawing_area ),
                      "button_press_event",
                      G_CALLBACK( audkrellm_scroll_bar_press ), NULL );
    g_signal_connect( G_OBJECT( audkrellm_scroll_panel->drawing_area ),
                      "button_release_event",
                      G_CALLBACK( audkrellm_scroll_bar_release ), NULL );
    g_signal_connect( G_OBJECT( audkrellm_scroll_panel->drawing_area ),
                      "motion_notify_event",
                      G_CALLBACK( audkrellm_scroll_bar_motion ), NULL );

    g_signal_connect( G_OBJECT( audkrellm_control_panel->drawing_area ),
                      "expose_event",
                      G_CALLBACK( panel_expose_event ), audkrellm_control_panel );
    g_signal_connect( G_OBJECT( audkrellm_control_panel->drawing_area ),
                      "button_press_event",
                      G_CALLBACK( audkrellm_panel_button_press ), NULL );
    g_signal_connect( G_OBJECT( audkrellm_control_panel->drawing_area ),
                      "button_release_event",
                      G_CALLBACK( audkrellm_panel_button_release ), NULL );
    g_signal_connect( G_OBJECT( audkrellm_control_panel->drawing_area ),
                      "motion_notify_event",
                      G_CALLBACK( audkrellm_slider_motion ), NULL );

    g_object_set( G_OBJECT( audkrellm_scroll_panel->drawing_area ),
                  "has-tooltip", TRUE, NULL );
    g_signal_connect( G_OBJECT( audkrellm_scroll_panel->drawing_area ),
                      "query-tooltip",
                      G_CALLBACK( audkrellm_get_tooltip_cb ), NULL );

    gtk_drag_dest_set( vbox, GTK_DEST_DEFAULT_ALL,
                       drop_types, NUM_DROP_TYPES, GDK_ACTION_COPY );
    g_signal_connect( G_OBJECT( vbox ), "drag_data_received",
                      G_CALLBACK( drag_data_received ), NULL );
  }
}

/*
 * taken from gkrellmms-2.1.22/src/gkrellmms.c
 */
void mainwin_back_func( void ) {
  if( audkrellm_opt_auto_main_close && audacious_is_running ) {
    audacious_remote_main_win_toggle( audkrellm_session, TRUE );
  }
}

/*
 * taken from gkrellmms-2.1.22/src/gkrellmms.c#plugin_gkrellmms
 */
static GkrellmMonitor plugin_audkrellm = {
  "AudKrellM",			/* Name, for config tab. */
  0,				/* ID, 0 if a plugin */

  create_audkrellm,		/* The create_plugin() function */
  update_audkrellm,		/* The update_plugin() function */

  audkrellm_create_config,	/* The create_plugin_tab() config function */
  audkrellm_apply_config, 	/* The apply_plugin_config() function */

  audkrellm_save_config,	/* The save_plugin_config() function */
  audkrellm_load_config,	/* The load_plugin_config() function */
  CONFIG_KEYWORD,		/* config keyword */

  NULL,				/* Undefined 2 */
  NULL,				/* Undefined 1 */
  NULL,				/* Undefined 0 */

  AUDKRELLM_PLACE,		/* Insert plugin before this monitor. */
  NULL,				/* Handle if a plugin, filled in by GKrellM */
  NULL				/* path if a plugin, filled in by GKrellM */
};

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c#gkrellmms_get_monitor
 */
GkrellmMonitor *audkrellm_get_monitor( void ) {
  return monitor;
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c#gkrellm_init_plugin
 */
GkrellmMonitor *gkrellm_init_plugin( void ) {
#ifdef ENABLE_NLS
  bind_textdomain_codeset( PACKAGE, "UTF-8" );
#endif

  /* Popup-menu set */
  audkrellm_init_popup_menu();

  audkrellm_control_panel        = NULL;
  audkrellm_scroll_panel         = NULL;
  audacious_is_running = FALSE;
  audacious_is_playing = FALSE;

  /* Default setting */
  audkrellm_set_default_config();

  g_atexit( mainwin_back_func );

  audkrellm_style_id = gkrellm_add_meter_style( &plugin_audkrellm, PACKAGE );
  pGK = gkrellm_ticks();

  monitor = &plugin_audkrellm;

  return &plugin_audkrellm;
}

/*
 * [EOF]
 */
