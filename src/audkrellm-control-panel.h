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

#ifndef __AUDKRELLM_CONTROL_PANEL_H_INCLUDED__
#define __AUDKRELLM_CONTROL_PANEL_H_INCLUDED__

extern GkrellmPanel *control_panel;
extern GkrellmDecal *control_decal;
extern GkrellmKrell *time_krell;

void update_control_panel( void );
void create_control_panel( GtkWidget *vbox );
void set_panel_status( void );

gint panel_button_press( GtkWidget *widget, GdkEventButton *ev, gpointer data );
gint panel_button_release( GtkWidget *widget, GdkEventButton *ev, gpointer data );
gint slider_motion( GtkWidget *widget, GdkEventMotion *ev, gpointer data );

#endif /* __AUDKRELLM_CONTROL_PANEL_H_INCLUDED__ */
