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
#include "audkrellm-scroll-panel.h"

#include "audkrellm-tooltip.h"
GtkTooltips *scrolling_tooltip;

static gchar *tooltip_text;

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c#update_gkrellmms
 */
void create_tooltip( void ) {
  if( scrolling_tooltip == NULL ) {
    scrolling_tooltip = gtk_tooltips_new();
    tooltip_text = g_strdup( "Audacious" );
    gtk_tooltips_set_tip( scrolling_tooltip, scroll_panel->drawing_area,
                          tooltip_text, NULL );
    gtk_tooltips_set_delay( scrolling_tooltip, 750 );
  }
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c#update_gkrellmms
 */
void update_tooltip( void ) {
  gchar *prev_tooltip_text;
  gchar *tooltip_utf8 = NULL, *tooltip_locale = NULL;
  gint   rate, freq, nch;
  gint   time;

  if( scrolling_tooltip != NULL ) {
    time = audacious_remote_get_output_time( session );
    prev_tooltip_text = tooltip_text;

    audacious_remote_get_info( session, &rate, &freq, &nch );

    tooltip_text = g_strdup_printf( "%s\n%d%s - %dHz - %s",
                                     scrolling_title_text,
                                     rate / 1000,
                                     ( time == -1 ) ? "bpm"  : "kb/s",
                                     freq,
                                     ( nch  ==  1 ) ? "mono" : "stereo" );

    if( ! strcmp( prev_tooltip_text, tooltip_text ) ) {
      gkrellm_locale_dup_string( &tooltip_utf8, tooltip_text, &tooltip_locale );
      gtk_tooltips_set_tip( scrolling_tooltip, scroll_panel->drawing_area,
                            tooltip_utf8, NULL );
      g_free( tooltip_utf8 );
      g_free( tooltip_locale );
    }

    g_free( prev_tooltip_text );
  }
}

/*
 * [EOF]
 */
