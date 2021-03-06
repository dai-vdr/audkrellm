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

#ifndef __AUDKRELLM_BUTTON_BAR_H_INCLUDED__
#define __AUDKRELLM_BUTTON_BAR_H_INCLUDED__

typedef struct {
  GkrellmPiximage    *image;
  GkrellmDecalbutton *button;
  gint x,y,w,h;
  double x_scale,y_scale;
} ControlButton;

void audkrellm_create_button_bar( void );
void audkrellm_set_button_status( void );

#endif /* __AUDKRELLM_BUTTON_BAR_H_INCLUDED__ */
