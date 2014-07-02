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

#ifndef __AUDKRELLM_OPTIONS_H__
#define __AUDKRELLM_OPTIONS_H__

#define SCROLL_SEPARATOR " ++++ "
#define MAXLEN_SCROLL_SEPARATOR 25

#define L_SWITCH 1
#define R_SWITCH 0

extern gchar    *audkrellm_opt_exec_command;
extern gchar    *audkrellm_opt_krell_label;
extern gchar    *audkrellm_opt_scroll_separator;

extern gboolean  audkrellm_opt_auto_start;
extern gboolean  audkrellm_opt_auto_main_close;
extern gboolean  audkrellm_opt_auto_hide_all;

extern gboolean  audkrellm_opt_scroll_enable;
extern gboolean  audkrellm_opt_draw_minus;

extern gint      audkrellm_opt_draw_in_time_bar;
extern gint      audkrellm_opt_krell_mmb_pause;
extern gint      audkrellm_opt_time_format;
extern gint      audkrellm_opt_always_load_info;

extern gboolean  audkrellm_opt_theme_show_button_bar;

void audkrellm_create_config( GtkWidget *tab );
void audkrellm_create_options_entries( GtkWidget *vbox );
void audkrellm_create_options_toggles( GtkWidget *vbox );
void audkrellm_create_options_switches( GtkWidget *vbox );
void audkrellm_create_options_info( GtkWidget *notebook );

void audkrellm_apply_config( void );
void audkrellm_apply_options_entries( void );
void audkrellm_apply_options_toggles( void );
void audkrellm_apply_options_switches( void );

void audkrellm_save_config( FILE *f );
void audkrellm_load_config( gchar *arg );
void audkrellm_set_default_config( void );

#endif /* __AUDKRELLM_OPTIONS_H__ */
