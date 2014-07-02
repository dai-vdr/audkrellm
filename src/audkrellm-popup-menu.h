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

#ifndef __AUDACIOUS_POPUP_MENU_H_INCLUDED__
#define __AUDACIOUS_POPUP_MENU_H_INCLUDED__

#define RUNNING     1
#define NOT_RUNNING 0

void audkrellm_options_menu( GdkEventButton *ev );
void audkrellm_init_popup_menu( void );

#endif /* __AUDACIOUS_POPUP_MENU_H_INCLUDED__ */

/*
 * [EOF]
 */
