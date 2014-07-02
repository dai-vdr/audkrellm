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

#define   SCROLL_SEPARATOR " ++++ "
#define   MAXLEN_SCROLL_SEPARATOR 25

extern gchar    *opt_audacious_exec_command;
extern gchar    *opt_audkrellm_krell_label;
extern gchar    *opt_audkrellm_scroll_separator;

extern gboolean  opt_audacious_auto_start;
extern gboolean  opt_audacious_auto_main_close;
extern gboolean  opt_audacious_auto_hide_all;

extern gboolean  opt_audkrellm_scroll_enable;
extern gboolean  opt_audkrellm_draw_minus;

extern gint      opt_audkrellm_draw_in_time_bar;
extern gint      opt_audkrellm_krell_mmb_pause;
extern gint      opt_audkrellm_time_format;

extern gboolean  opt_theme_show_button_bar;

void create_audkrellm_config( GtkWidget *tab );
void create_options_entries( GtkWidget *vbox );
void create_options_toggles( GtkWidget *vbox );
void create_options_switches( GtkWidget *vbox );
void create_options_info( GtkWidget *notebook );

void apply_audkrellm_config( void );
void apply_options_configs( void );
void apply_options_toggles( void );
void apply_options_switches( void );

void save_audkrellm_config( FILE *f );
void load_audkrellm_config( gchar *arg );
void set_audkrellm_default_config( void );

#endif /* __AUDKRELLM_OPTIONS_H__ */
