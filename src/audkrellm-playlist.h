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

#ifndef __AUDKRELLM_PLAYLIST_H_INCLUDED__
#define __AUDKRELLM_PLAYLIST_H_INCLUDED__

/* init the playlist */
void audkrellm_init_playlist( void );

/* check if the playlist is still correct 
 * returns TRUE when there where changes */ 
gint audkrellm_update_playlist( void );

/* gets the time/filename/title of the current song 
 * don't free !  */
gchar *audkrellm_get_current_file( void );
gchar *audkrellm_get_current_title( void );
gint   audkrellm_get_current_time( void );
gint   audkrellm_get_current_position( void );

#endif /* __AUDKRELLM_PLAYLIST_H_INCLUDED__ */
