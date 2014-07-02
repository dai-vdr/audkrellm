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

#include "pixmaps/prev.xpm"
#include "pixmaps/play_pause.xpm"
#include "pixmaps/stop.xpm"
#include "pixmaps/next.xpm"
#include "pixmaps/eject.xpm"

#include "pixmaps/prev_clicked.xpm"
#include "pixmaps/play_pause_clicked.xpm"
#include "pixmaps/stop_clicked.xpm"
#include "pixmaps/next_clicked.xpm"
#include "pixmaps/eject_clicked.xpm"

#include "audkrellm.h"
#include "audkrellm-options.h"
#include "audkrellm-control-panel.h"
#include "audkrellm-button-bar.h"
#include "audkrellm-led.h"

static ControlButton prev_button,
                     play_button,
                     stop_button,
                     next_button,
                     eject_button;
static gboolean gkrellmrc_button_placement;

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
static void cb_control_button( GkrellmDecalbutton *button ) {
  gint control_id = GPOINTER_TO_INT( button->data );
  if( ! audacious_is_running && control_id == AUDKRELLM_PLAY ) {
    audkrellm_start_audacious();
  } else {
    audkrellm_do_audacious_command( control_id );
  }
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
static void stack_in_out_images( GkrellmPiximage *out_image,
                                 GkrellmPiximage *in_image ) {
  GdkPixbuf *pixbuf, *src_pixbuf;
  gint       w, h;

  src_pixbuf = out_image->pixbuf;
  w = gdk_pixbuf_get_width( src_pixbuf );
  h = gdk_pixbuf_get_height( src_pixbuf );

  pixbuf = gdk_pixbuf_new( GDK_COLORSPACE_RGB,
                           gdk_pixbuf_get_has_alpha( src_pixbuf ),
                           8, w, 2 * h );
  gdk_pixbuf_copy_area( src_pixbuf, 0, 0, w, h, pixbuf, 0, 0 );
  gdk_pixbuf_copy_area( in_image->pixbuf, 0, 0, w, h, pixbuf, 0, h );
  g_object_unref( out_image->pixbuf );
  out_image->pixbuf = pixbuf;
  gkrellm_destroy_piximage( in_image );
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
static void load_button( ControlButton *button, gchar *button_name,
                         gchar *out, gchar **out_xpm,
                         gchar *in,  gchar **in_xpm ) {
  GkrellmPiximage *clicked_image = NULL;

  if( ! gkrellm_load_piximage( button_name, NULL,
                               &button->image, GKRELLMMS_STYLE ) ) {
    gkrellm_load_piximage( out, out_xpm, &button->image, GKRELLMMS_STYLE );
    gkrellm_load_piximage( in,  in_xpm,  &clicked_image, GKRELLMMS_STYLE );
    stack_in_out_images( button->image, clicked_image );
  }
  /* Default size may be gkrellmrc reassigned later. */
  button->w = gdk_pixbuf_get_width(  button->image->pixbuf );
  button->h = gdk_pixbuf_get_height( button->image->pixbuf ) / 2;
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
static void load_button_images( void ) {
  load_button( &prev_button,  "prev_button",
               "prev",         prev_xpm,
               "prev_clicked", prev_clicked_xpm );
  load_button( &play_button,        "play_button",
               "play_pause",         play_pause_xpm,
               "play_pause_clicked", play_pause_clicked_xpm );
  load_button( &stop_button,  "stop_button",
               "stop",         stop_xpm,
               "stop_clicked", stop_clicked_xpm );
  load_button( &next_button,  "next_button",
               "next",         next_xpm,
               "next_clicked", next_clicked_xpm );
  load_button( &eject_button,  "eject_button",
               "eject",         eject_xpm,
               "eject_clicked", eject_clicked_xpm );
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
static gint set_x_position( gint x, gchar *anchor ) {
  x = x * gkrellm_get_theme_scale();

  /* left anchor is the default */
  if( anchor[ 0 ] == 'c' || anchor[ 0 ] == 'C' ) {
    x += gkrellm_chart_width() / 2;
  } else if( anchor[ 0 ] == 'r' || anchor[ 0 ] == 'R' ) {
    x = gkrellm_chart_width() - x - 1;
  }
  return x;
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
/* Look for custom button placement and size from the gkrellmrc.  The
|  button final size may later change yet again if user has set theme_scale.
*/
static void button_position( ControlButton *button, gchar *name ) {
  gchar *s, anchor[ 8 ];
  gint   x, w, h;

  if( ( s = gkrellm_get_gkrellmrc_string( name ) ) != NULL ) {
    anchor[ 0 ] = 'l';
    if( sscanf( s, "%d %d %d %d %8s", &x, &button->y, &w, &h, anchor ) >= 4 ) {
      button->x = set_x_position( x, anchor );
      if( w > 0 ) {
        button->w = w;
      }
      if( h > 0 ) {
        button->h = h;
      }
    }
    button->y = button->y * gkrellm_get_theme_scale();
    gkrellmrc_button_placement = TRUE;
  }
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
static void decal_position( GkrellmDecal *decal, gchar *name, gboolean text ) {
  gchar *s, anchor[ 8 ];
  gint   x, y;

  anchor[ 0 ] = 'l';
  if( ( s = gkrellm_get_gkrellmrc_string( name ) ) != NULL &&
      sscanf( s, "%d %d %8s", &x, &y, anchor ) >= 2 ) {
    x = set_x_position( x, anchor );
    y = y * gkrellm_get_theme_scale();

    gkrellm_move_decal( audkrellm_control_panel, decal, x, y );
  }
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
static void layout_control_panel( GkrellmStyle *lc_style, gint yoff ) {
  prev_button.y = play_button.y  = stop_button.y = yoff;
  next_button.y = eject_button.y = yoff;

  /* Next, look for custom theming button placements and sizes. */
  gkrellmrc_button_placement = FALSE;
  button_position( &prev_button,  GKRELLMMS_STYLE"_prev_button_position"  );
  button_position( &play_button,  GKRELLMMS_STYLE"_play_button_position"  );
  button_position( &stop_button,  GKRELLMMS_STYLE"_stop_button_position"  );
  button_position( &next_button,  GKRELLMMS_STYLE"_next_button_position"  );
  button_position( &eject_button, GKRELLMMS_STYLE"_eject_button_position" );

  decal_position( audkrellm_control_decal,
                  GKRELLMMS_STYLE"_label_position", TRUE  );
  decal_position( audkrellm_led_decal,
                  GKRELLMMS_STYLE"_led_position",   FALSE );
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
/* If the mouse is in the button decal and the mouse position is not on a
|  transparent pixel (look at the pixbuf), return TRUE.
*/
static gboolean cb_in_button( GkrellmDecalbutton *b, GdkEventButton *ev,
                              ControlButton *cbut ) {
  GdkPixbuf    *pixbuf;
  GkrellmDecal *d;
  guchar       *pixels, alpha;
  gint         rowstride, x, y;

  d = b->decal;
  if( gkrellm_in_decal( d, ev ) ) {
    pixbuf = cbut->image->pixbuf;
    if( ! gdk_pixbuf_get_has_alpha( pixbuf ) ) {
      return TRUE;
    }
    x = ev->x - d->x;
    x = x / cbut->x_scale;
    y = ev->y - d->y;
    y = y / cbut->y_scale;
    pixels = gdk_pixbuf_get_pixels( pixbuf );
    rowstride = gdk_pixbuf_get_rowstride( pixbuf );
    pixels += y * rowstride + 4 * x;
    alpha = *( pixels + 3 );
    //printf("in button x=%d y=%d alpha=%x\n", x, y, alpha);
    if( alpha > 0 ) {
      return TRUE;
    }
  }
  return FALSE;
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
static void move_buttons( void ) {
  gint x, w;

  if( ! gkrellmrc_button_placement ) {
    /* Place buttons according to GKrellMMS 0.5.5 */
    w = prev_button.w + play_button.w + stop_button.w
                      + next_button.w + eject_button.w;
    x = ( gkrellm_chart_width() - w ) / 2;
    if( x < 0 ) {
      x = 0;
    }
    prev_button.x  = x;
    play_button.x  = prev_button.x + prev_button.w;
    stop_button.x  = play_button.x + play_button.w;
    next_button.x  = stop_button.x + stop_button.w;
    eject_button.x = next_button.x + next_button.w;
  }
  gkrellm_move_decal( audkrellm_control_panel,  prev_button.button->decal,
                      prev_button.x,  prev_button.y  );
  gkrellm_move_decal( audkrellm_control_panel,  play_button.button->decal,
                      play_button.x,  play_button.y  );
  gkrellm_move_decal( audkrellm_control_panel,  stop_button.button->decal,
                      stop_button.x,  stop_button.y  );
  gkrellm_move_decal( audkrellm_control_panel,  next_button.button->decal,
                      next_button.x,  next_button.y  );
  gkrellm_move_decal( audkrellm_control_panel,  eject_button.button->decal,
                      eject_button.x, eject_button.y );
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c
 */
static void make_button( ControlButton *cbut, gint fn_id ) {
  cbut->button = gkrellm_make_scaled_button( audkrellm_control_panel, cbut->image,
                   cb_control_button, GINT_TO_POINTER( fn_id ),
                   FALSE, FALSE, 2, 0, 1, cbut->x, cbut->y, cbut->w, cbut->h );

  /* The button final size may be different from the requested size if the
  |  user has set a theme_scale other than 1.0.
  */
  cbut->w = cbut->button->decal->w;
  cbut->h = cbut->button->decal->h;

  /* x_scale and y_scale are the ratio of the button final size to the
  |  original button image size so cb_in_button() can map mouse events from
  |  the button decal to the button image.
  */
  cbut->x_scale = (double)cbut->w /
                  (double)gdk_pixbuf_get_width( cbut->image->pixbuf );
  cbut->y_scale = (double)cbut->h /
                ( (double)gdk_pixbuf_get_height( cbut->image->pixbuf ) / 2.0 );
  gkrellm_set_in_button_callback( cbut->button, cb_in_button, cbut );
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c#create_gkrellmms
 */
void audkrellm_create_button_bar( void ) {
  gint y = 0, y1;

  load_button_images();
  y  = audkrellm_control_decal->y + audkrellm_control_decal->h;
  y1 = audkrellm_time_krell->y0   + audkrellm_time_krell->h_frame;
  if( y1 > y ) {
    y = y1;
  }
  layout_control_panel( audkrellm_style, y + 3 );

  make_button( &prev_button,  AUDKRELLM_PREV  );
  make_button( &play_button,  AUDKRELLM_PLAY  );
  make_button( &stop_button,  AUDKRELLM_STOP  );
  make_button( &next_button,  AUDKRELLM_NEXT  );
  make_button( &eject_button, AUDKRELLM_EJECT );
  move_buttons();
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c#set_panel_status
 */
void audkrellm_set_button_status( void ) {
  gkrellm_set_button_sensitive( prev_button.button,  audacious_is_running );
  gkrellm_set_button_sensitive( stop_button.button,  audacious_is_running );
  gkrellm_set_button_sensitive( next_button.button,  audacious_is_running );
  gkrellm_set_button_sensitive( eject_button.button, audacious_is_running );
}

/*
 * [EOF]
 */
