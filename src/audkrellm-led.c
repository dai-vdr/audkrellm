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
#include "audkrellm-control-panel.h"

#include "audkrellm-led.h"
GkrellmDecal *led_decal;

static gint led_off_index     = 0,
            led_running_index = 1,
            led_paused_index  = 2,
            led_playing_index = 3;

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c#update_gkrellmms
 */
void update_led( void ) {
  static gint on_index = 0, off_index = 0, led_status = 0, led_on = FALSE;

  /* calculate if led should be on or off */
  if( led_status < 0 ) {
    /* want to blink for two seconds */
    led_status = gkrellm_update_HZ() * 2;
  }
  led_on = ( --led_status ) > gkrellm_update_HZ();

  if( ! audacious_is_running ) {
    on_index  = led_playing_index;
    off_index = led_off_index;
  } else if( audacious_remote_is_paused( session ) ) {
    on_index  = led_off_index; /* invert the duty cycle */
    off_index = led_paused_index;
  } else if( ! audacious_is_playing ) {
    on_index  = led_running_index;
    off_index = led_off_index;
  } else { /* Playing */
    led_on   = TRUE; /* no blinking */
    on_index = led_playing_index;
  }

  gkrellm_draw_decal_pixmap( control_panel, led_decal,
                             led_on ? on_index : off_index );
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c#create_gkrellmms
 */
void create_led( GkrellmMargin *m ) {
  GkrellmPiximage  *led_image = NULL;

  if( gkrellm_load_piximage( "led_indicator", NULL,
                             &led_image, GKRELLMMS_STYLE ) ) {
    led_decal = gkrellm_make_scaled_decal_pixmap( control_panel, led_image,
                                                  style, 4, 0, -1, 0, 0);
    led_off_index     = 0;
    led_running_index = 1;
    led_paused_index  = 2;
    led_playing_index = 3;
  } else {
    led_decal = gkrellm_create_decal_pixmap( control_panel,
                                             gkrellm_decal_misc_pixmap(),
                                             gkrellm_decal_misc_mask(),
                                             N_MISC_DECALS, style, 0, -1 );
    led_off_index     = D_MISC_LED0;
    led_running_index = D_MISC_LED1;
    led_paused_index  = D_MISC_LED1;
    led_playing_index = D_MISC_LED1;
  }
  led_decal->x = gkrellm_chart_width() - led_decal->w - m->right;

  gkrellm_draw_decal_pixmap( control_panel, led_decal, led_off_index );
}

/*
 * [EOF]
 */
