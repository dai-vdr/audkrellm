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
#include "audkrellm-tooltip.h"

#include "audkrellm-scroll-panel.h"
GkrellmPanel *scroll_panel;
GkrellmStyle *scroll_style;
GkrellmDecal *scroll_in_motion;

gchar *scrolling_title_text;
gint   x_scroll;
gint   scroll_separator_len;

static GkrellmDecal *scroll_decal;
static gchar *playlist_title;
static gint   output_time;
static gint   scroll_motion_x;

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c#gkrellmms_set_scroll_separator_len
 */
void set_scroll_separator_len( void ) {
  scroll_separator_len = gkrellm_gdk_string_width( scroll_decal->text_style.font,
                                                   opt_audkrellm_scroll_separator );
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
gchar *get_scrolling_title_text( gint *ret_width, gboolean reset ) {
  static gint   time, position, width;
  static gchar *title, *scroll_text;
  static gint   playlist_pos;

  playlist_pos   = audacious_remote_get_playlist_pos( session );
  playlist_title = audacious_remote_get_playlist_title( session, playlist_pos );
  output_time    = audacious_remote_get_output_time( session );

  if( ! scroll_text ||
      reset ||
      output_time != time ||
      playlist_pos != position ||
      gkrellm_dup_string( &title, playlist_title ) ) {
    time = output_time;
    position = playlist_pos + 1;
    g_free( scroll_text );

    if( time > 0 ) {
      scroll_text = g_strdup_printf( "%d. %s (%d:%02d)",
                                     position, playlist_title,
                                     time / 1000 / 60, time / 1000 % 60 );
    } else {
      scroll_text = g_strdup_printf( "%d. %s", position, playlist_title );
    }
    width = gkrellm_gdk_string_width( scroll_decal->text_style.font,
                                      scroll_text );
  }

  if( ret_width ) {
    *ret_width = width;
  }
  if( reset ) {
    set_scroll_separator_len();
  }

  return scroll_text;
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c#update_gkrellmms
 */
void update_scroll_panel( void ) {
  GkrellmMargin *margin;
  static gint    len, w;
  gchar         *more_scrolled;

  margin = gkrellm_get_style_margins( style );
  w = gkrellm_chart_width() - margin->left - margin->right - 2;
  scrolling_title_text = get_scrolling_title_text( &len, FALSE );

  update_tooltip();

  /* gkrellm >= 2.2.0 has a scroll text decal which minimizes slow
  |  Pango renders as the decal text is scrolled (offset is changed).
  */
  if( len > w ) {
    more_scrolled = g_strdup_printf( "%s%s", scrolling_title_text,
                                             opt_audkrellm_scroll_separator );
    x_scroll = ( x_scroll + 1 ) % ( len + scroll_separator_len );
    gkrellm_decal_scroll_text_set_text( scroll_panel, scroll_decal,
                                        more_scrolled );
    gkrellm_decal_scroll_text_horizontal_loop( scroll_decal, TRUE );
    gkrellm_decal_text_set_offset( scroll_decal, -x_scroll, 0 );
  } else {
    more_scrolled = g_strdup( "" );
    x_scroll = 0;
    gkrellm_decal_text_set_offset( scroll_decal, 0, 0 );
    gkrellm_draw_decal_text( scroll_panel, scroll_decal,
                             scrolling_title_text, 0 );
  }

  gkrellm_draw_panel_layers( scroll_panel );
  g_free( more_scrolled );
}

/*
 * taken from gkrellmms/gkrellmms.c, a part of create_gkrellmms()
 *
 * XXX:WIP
 */
void create_scroll_panel( GtkWidget *vbox ) {
  GkrellmTextstyle *scroll_panel_ts;
  GkrellmMargin     mgn;
  static GkrellmPiximage *bg_scroll_image;

  scroll_panel_ts = gkrellm_meter_alt_textstyle( AUDKRELLM_STYLE );

  if( bg_scroll_image ) { /* Avoid memory leaks at theme changes */
    gkrellm_destroy_piximage( bg_scroll_image );
    bg_scroll_image = NULL;
  }
  gkrellm_load_piximage( "bg_scroll", NULL, &bg_scroll_image, GKRELLMMS_STYLE );
  if( bg_scroll_image ) {
    gkrellm_set_gkrellmrc_piximage_border( GKRELLMMS_STYLE"_bg_scroll",
                                           bg_scroll_image, scroll_style );
  }

  mgn = *gkrellm_get_style_margins( scroll_style );
  if( gkrellm_get_gkrellmrc_integer( GKRELLMMS_STYLE"_scroll_margin", &mgn.left ) ) {
    mgn.right = mgn.left;
  }
  gkrellm_get_gkrellmrc_integer( GKRELLMMS_STYLE"_scroll_top_margin", &mgn.top );
  gkrellm_get_gkrellmrc_integer( GKRELLMMS_STYLE"_scroll_bottom_margin", &mgn.bottom );
  gkrellm_set_style_margins( scroll_style, &mgn );

  scroll_decal = gkrellm_create_decal_text( scroll_panel, "Apif0",
                                            scroll_panel_ts, scroll_style,
                                            -1, -1, -1 );

  if( bg_scroll_image ) {
    gkrellm_panel_bg_piximage_override( scroll_panel, bg_scroll_image );
  }

  gkrellm_panel_configure( scroll_panel, NULL, scroll_style );
  gkrellm_panel_create( vbox, monitor, scroll_panel );

  create_tooltip();
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
void
scroll_bar_press( GtkWidget *widget, GdkEventButton *ev, gpointer data ) {
  if( ev->button == 1 ) {
    scroll_in_motion = scroll_decal;
    scroll_motion_x = ev->x;
  }
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
void
scroll_bar_release( GtkWidget *widget, GdkEventButton *ev, gpointer data ) {
  scroll_in_motion = NULL;
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
void
scroll_bar_motion( GtkWidget *widget, GdkEventButton *ev, gpointer data ) {
  GkrellmMargin   *margin;
  gint             w, len, change;
  GdkModifierType  state;
  gchar           *more_scrolled;

  if( scroll_in_motion != NULL ) {
    /* Check if button is still pressed, in case missed button_release */
    state = ev->state;
    if( ! ( state & GDK_BUTTON1_MASK ) ) {
      scroll_in_motion = NULL;
      return;
    }

    margin = gkrellm_get_style_margins( style );
    w = gkrellm_chart_width() - margin->left - margin->right - 2;

    change = scroll_motion_x - ev->x;
    scroll_motion_x = ev->x;

    scrolling_title_text = get_scrolling_title_text( &len, FALSE );

    if( len <= w ) {
      scroll_in_motion = NULL;
      return;
    }

    x_scroll = ( x_scroll + change ) % ( len + scroll_separator_len );
    if( x_scroll < 0 ) {
      x_scroll = len + scroll_separator_len;
    }

    more_scrolled = g_strdup_printf( "%s%s",
                                     scrolling_title_text,
                                     opt_audkrellm_scroll_separator );

    gkrellm_decal_scroll_text_set_text( scroll_panel,
                                        scroll_decal, more_scrolled );
    gkrellm_decal_scroll_text_horizontal_loop( scroll_decal, TRUE );
    gkrellm_decal_text_set_offset( scroll_decal, -x_scroll, 0 );

    gkrellm_draw_panel_layers( scroll_panel );
    g_free( more_scrolled );
  }
}

/*
 * [EOF]
 */
