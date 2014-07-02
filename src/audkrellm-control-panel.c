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
#include "audkrellm-button-bar.h"
#include "audkrellm-scroll-panel.h"
#include "audkrellm-led.h"
#include "audkrellm-popup-menu.h"

#include "audkrellm-control-panel.h"
GkrellmPanel *control_panel;
GkrellmDecal *control_decal;
GkrellmKrell *time_krell;

static GkrellmKrell *slider_in_motion;
static gint where_to_jump;
static gboolean got_motion;

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c#update_gkrellmms
 */
void update_control_panel( void ) {
  static gint prev_position = -1;
  gchar *audcious_string;
  gint playlist_changed = FALSE;
  gint position_changed = FALSE;
  gint slider_position  = 0;

  static gint output_time;
  static gint playlist_time;

  if( pGK->second_tick ) {
    set_panel_status();
    set_button_status();
  }

  if( ( audacious_is_running = audacious_remote_is_running( session ) ) ) {
    /* position is changed in the playlist when the playlist is changed too! */
    position_changed = audacious_remote_get_playlist_pos( session )
                       != prev_position || playlist_changed;
    prev_position = audacious_remote_get_playlist_pos( session );
    audacious_is_playing = audacious_remote_is_playing( session );

    if( scroll_panel ) {
      if( opt_audkrellm_scroll_enable && ! scroll_in_motion ) {
        update_scroll_panel();
      }
    }
  }

  /* Also draw xmms-status when xmms isn't running,
  |  but don't while seeking
  */
  if( slider_in_motion == NULL ) {
    control_decal->x_off = 1;
    if( audacious_is_running &&
        ( audacious_is_playing || position_changed ) &&
        opt_audkrellm_draw_in_time_bar ) {
      output_time   = audacious_remote_get_output_time( session ) / 1000;
      playlist_time = audacious_remote_get_playlist_time( session,
                      audacious_remote_get_playlist_pos( session ) ) / 1000;
      /* calculate slider position */
      slider_position = playlist_time ? ( ( output_time * 100 ) / playlist_time )
                                      : 0;
      if( slider_position < 0 ) {
        slider_position = 0;
      } else if ( slider_position > 100 ) {
        slider_position = 100;
      }

      /* render timer string */
      if( opt_audkrellm_time_format || output_time <= 0 ) {
        audcious_string = g_strdup_printf( "%02d:%02d",
                                           output_time / 60, output_time % 60 );
      } else {
        audcious_string = g_strdup_printf( opt_audkrellm_draw_minus
                                           ? "-%02d:%02d" : "%02d:%02d",
                                           ( playlist_time - output_time ) / 60,
                                           ( playlist_time - output_time ) % 60 );
        if( opt_audkrellm_draw_minus ) {
          control_decal->x_off = -1;
        }
      }
    } else {
      audcious_string = g_strdup( opt_audkrellm_krell_label );
    }
    gkrellm_draw_decal_text( control_panel, control_decal, audcious_string, -1 );

    update_led();

    gkrellm_update_krell( control_panel, time_krell, (gulong)slider_position );
    gkrellm_draw_panel_layers( control_panel );
    g_free( audcious_string );
  }
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
void set_panel_status( void ) {
  if( ! audacious_is_running || ! opt_audkrellm_scroll_enable ) {
    gkrellm_panel_hide( scroll_panel );
  } else {
    gkrellm_panel_show( scroll_panel );
  }
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c#create_gkrellmms
 */
void create_control_panel( GtkWidget *vbox ) {
  gint w;
  GkrellmTextstyle *ts;
  GkrellmMargin    *m;

  ts = gkrellm_meter_textstyle( AUDKRELLM_STYLE );

  time_krell = gkrellm_create_krell( control_panel,
    gkrellm_krell_meter_piximage( DEFAULT_STYLE ), style );

  gkrellm_monotonic_krell_values( time_krell, FALSE );
  gkrellm_set_krell_full_scale( time_krell, 100, 1 );

  m = gkrellm_get_style_margins( style );
  w = gkrellm_gdk_string_width( ts->font, "-000:00" );
  control_decal = gkrellm_create_decal_text( control_panel, (gchar*)"A0",
                                             ts, style, -1, -1, w );
  control_decal->x += m->left;

  create_led( m );

  gkrellm_draw_decal_text( control_panel, control_decal,
                           opt_audkrellm_krell_label, -1 );
  gkrellm_update_krell( control_panel, time_krell, (gulong)0 );

  if( opt_theme_show_button_bar ) {
    create_button_bar();
  }

  gkrellm_panel_configure( control_panel, NULL, style );
  gkrellm_panel_create( vbox, monitor, control_panel );

  /* Make led and label decals drawn on top of buttons. */
  gkrellm_remove_decal( control_panel, control_decal);
  gkrellm_remove_decal( control_panel, led_decal );
  gkrellm_insert_decal( control_panel, led_decal, TRUE );
  gkrellm_insert_decal( control_panel, control_decal, TRUE ); /* On top */

  get_scrolling_title_text( NULL, TRUE ); /* Sync with theme changes */
  gkrellm_draw_panel_layers( control_panel );

  set_panel_status();
  set_button_status();

  return;
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
gint panel_button_press( GtkWidget *widget, GdkEventButton *ev, gpointer data ) {
  switch( ev->button ) {
    case 1:
      if( audacious_is_running &&
          ev->y >= time_krell->y0 &&
          ev->y <  time_krell->y0 + time_krell->h_frame ) {
        slider_in_motion = time_krell;
      } else {
        slider_in_motion = NULL;
      }
      if( ( ev->type == GDK_2BUTTON_PRESS ) && ! audacious_is_running ) {
        audacious_start_func();
      }
      break;
    case 2:
      if( audacious_is_running && audacious_remote_is_playing( session ) ) {
        if( opt_audkrellm_krell_mmb_pause ) {
          audacious_remote_pause( session );
        } else {
          audacious_remote_stop (session );
        }
      } else if( audacious_is_running ) {
        audacious_remote_play( session );
      } else {
        audacious_start_func();
      }
      break;
    case 3:
      options_menu( ev );
      break;
  }
  return FALSE;
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
gint panel_button_release( GtkWidget *widget, GdkEventButton *ev, gpointer data ) {
  gint   z;
  gint   timer;
  time_t lt;
  gint   playlist_time = -1;

  if( slider_in_motion ) {
    playlist_time = audacious_remote_get_playlist_time( session,
                      audacious_remote_get_playlist_pos( session ) );

    if( ! got_motion ) {
      /* Also jump to time if you've clicked once on the Krell */
      z = ev->x * time_krell->full_scale / ( gkrellm_chart_width() - 1 );
      if( z < 0 ) {
        z = 0;
      } else if( z > 100 ) {
        z = 100;
      }

      where_to_jump = ( z * playlist_time ) / 100;
      if( where_to_jump >= playlist_time ) {
        where_to_jump = playlist_time - 1;
      }

      time_krell->previous = 0;
      gkrellm_update_krell( control_panel, time_krell, (gulong)z );
      gkrellm_draw_panel_layers( control_panel );
    }

    if( where_to_jump > playlist_time ) {
      return FALSE;
    }

    /*
     | Let gkrellm sleep for about 0 seconds when sending this commands
     | when xmms isn't playing, so that xmms received the functions for
     | sure, and gkrellm doesn't do weird stuff on it.
     | Maybe it's not neccasary if you've got a fast computer, but on my
     | P200 I really notice some bugs without it.
     */
    if( ! audacious_is_playing ) {
      audacious_remote_play( session );
    }
    timer = time( &lt );

    /* Do nothing, wait until xmms really plays;
     | stop waiting after 10 seconds.
     */
    /* FIXME ugly evil code */
    while( ! audacious_remote_is_playing( session ) &&
           ( ( time( &lt ) - timer ) < 10 ) ) {
      usleep( 0 );
    }

    audacious_remote_jump_to_time( session, where_to_jump );

    timer = localtime( &lt )->tm_sec;

    /* Wait till really jumped before we continue. */
    while( ( audacious_remote_get_output_time( session ) / 1000 )
           != ( where_to_jump / 1000 ) &&
           ( ( time( &lt ) - timer ) < 10 ) ) {
      usleep( 0 );
    }
  } else if( ( slider_in_motion != NULL ) && ! audacious_is_playing ) {
    audacious_remote_play( session );
  }

  slider_in_motion = NULL;
  got_motion = FALSE;

  return FALSE;
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
gint slider_motion( GtkWidget *widget, GdkEventMotion *ev, gpointer data ) {
  gint            z;
  GdkModifierType state;
  gint playlist_time = -1;

  if( slider_in_motion != NULL ) {
    /* Check if button is still pressed, in case missed button_release */
    state = ev->state;
    if( ! ( state & GDK_BUTTON1_MASK ) ) {
      slider_in_motion = NULL;
      return TRUE;
    }
    z = ev->x * time_krell->full_scale / ( gkrellm_chart_width() - 1 );
    if( z < 0 ) {
      z = 0;
    } else if( z > 100 ) {
      z = 100;
    }

    time_krell->previous = 0;
    gkrellm_update_krell( control_panel, time_krell, (gulong)z );
    gkrellm_draw_panel_layers( control_panel );

    playlist_time = audacious_remote_get_playlist_time( session,
                      audacious_remote_get_playlist_pos( session ) );

    where_to_jump = ( z * playlist_time ) / 100;
    if( where_to_jump >= playlist_time ) {
      where_to_jump = playlist_time - 1;
    }

    got_motion = TRUE;
  }

  return TRUE;
}

/*
 * [EOF]
 */
