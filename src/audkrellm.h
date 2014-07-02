/*
  AudKrellM: GKrellM Audacious Plugin

  Copyright (C) 2007 dai <d+audacious@vdr.jp>
  All rights reserved.

  Based on: GKrellMMS: GKrellM XMMS Plugin
  Copyright (C) 2000-2004 Sander Klein Lebbink

  Original Author:  Sander Klein Lebbink <sander@cerberus.demon.nl>
  Current Maintainer: Sjoerd Simons <sjoerd@luon.net>
  Latest versions might be found at:  http://gkrellm.luon.net/

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

#ifndef __AUDKRELLM_H_INCLUDED__
#define __AUDKRELLM_H_INCLUDED__

#include "config.h"

#include <gkrellm2/gkrellm.h>

#undef  PACKAGE
#define PACKAGE         "audkrellm"
#define CONFIG_KEYWORD  PACKAGE
#define DEFAULT_STYLE   audkrellm_style_id
#define GKRELLMMS_STYLE "gkrellmms" /* it is GKrellM's internal style name */
#define AUDKRELLM_STYLE DEFAULT_STYLE
#define AUDKRELLM_PLACE (MON_APM | GRAVITY(8))

#define AUDKRELLM_PREV  1
#define AUDKRELLM_PLAY  2
#define AUDKRELLM_PAUSE 3
#define AUDKRELLM_STOP  4
#define AUDKRELLM_NEXT  5
#define AUDKRELLM_EJECT 6

#define AUDKRELLM_MAINWIN  7
#define AUDKRELLM_PLAYLIST 8   
#define AUDKRELLM_EQ       9
#define AUDKRELLM_REPEAT   10
#define AUDKRELLM_SHUFFLE  11
#define AUDKRELLM_AOT      12
#define AUDKRELLM_PREFS    13

extern GkrellmStyle *audkrellm_style;
extern gint          audkrellm_style_id;

#include <audacious/dbus.h>
#include <audacious/audctrl.h>
extern DBusGProxy *audkrellm_session;
extern gboolean    audkrellm_is_running;
extern gboolean    audkrellm_is_playing;
#define audacious_is_running audkrellm_is_running
#define audacious_is_playing audkrellm_is_playing

GkrellmMonitor *audkrellm_get_monitor( void );

void audkrellm_start_audacious( void );
void audkrellm_do_audacious_command( gint i );

#endif /* __AUDKRELLM_H_INCLUDED__ */
