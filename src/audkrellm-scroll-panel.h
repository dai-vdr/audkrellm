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

#ifndef __AUDKRELLM_SCROLL_PANEL_H_INCLUDED__
#define __AUDKRELLM_SCROLL_PANEL_H_INCLUDED__

extern GkrellmPanel *audkrellm_scroll_panel;
extern GkrellmStyle *audkrellm_scroll_style;
extern GkrellmDecal *audkrellm_scroll_in_motion;

extern gchar *audkrellm_scrolling_title_text;

void audkrellm_create_scroll_panel( GtkWidget *vbox );
void audkrellm_update_scroll_panel( void );
void audkrellm_set_scroll_separator_len( void );
gchar *audkrellm_get_scrolling_title_text( gint *ret_width, gboolean reset );

void audkrellm_scroll_bar_press( GtkWidget *widget,
                                 GdkEventButton *ev, gpointer data );
void audkrellm_scroll_bar_release( GtkWidget *widget,
                                   GdkEventButton *ev, gpointer data );
void audkrellm_scroll_bar_motion( GtkWidget *widget,
                                  GdkEventButton *ev, gpointer data );

#endif /* __AUDKRELLM_SCROLL_PANEL_H_INCLUDED__ */
