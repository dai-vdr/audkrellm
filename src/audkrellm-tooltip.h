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

#ifndef __AUDKRELLM_TOOLTIP_H_INCLUDED__
#define __AUDKRELLM_TOOLTIP_H_INCLUDED__

gboolean audkrellm_get_tooltip_cb( GtkWidget *widget, gint x, gint y, gboolean keyboard_mode, GtkTooltip *tooltip );

#endif /* __AUDKRELLM_TOOLTIP_H_INCLUDED__ */
