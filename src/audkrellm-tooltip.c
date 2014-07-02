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
#include "audkrellm-playlist.h"
#include "audkrellm-scroll-panel.h"

#include "audkrellm-tooltip.h"

/*
 * taken from xfce4-weather-plugin-0.7.3/panel-plugin/weather.c
 */
gboolean audkrellm_get_tooltip_cb( GtkWidget *widget,
                                   gint x, gint y,
                                   gboolean keyboard_mode,
                                   GtkTooltip *tooltip ) {
  gchar *tooltip_text;
  gchar *tooltip_utf8 = NULL, *tooltip_locale = NULL;
  gint   rate = -1, freq = -1, nch = -1;
  gint   time;

  if( tooltip != NULL ) {
    time = audkrellm_get_current_time();

    audacious_remote_get_info( audkrellm_session, &rate, &freq, &nch );

    tooltip_text = g_strdup_printf( "%s\n%d%s - %dHz - %s",
                                     audkrellm_scrolling_title_text,
                                     rate / 1000,
                                     ( time == -1 ) ? "bpm"  : "kb/s",
                                     freq,
                                     ( nch  ==  1 ) ? "mono" : "stereo" );

    gkrellm_locale_dup_string( &tooltip_utf8, tooltip_text, &tooltip_locale );
    gtk_tooltip_set_text( tooltip, tooltip_utf8 );
    g_free( tooltip_utf8 );
    g_free( tooltip_locale );
  } else {
    gtk_tooltip_set_text( tooltip, "Audacious" );
  }

  return TRUE;
}

/*
 * [EOF]
 */
