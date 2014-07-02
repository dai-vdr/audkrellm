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

#include "audkrellm-options.h"
gchar    *audkrellm_opt_exec_command;
gchar    *audkrellm_opt_krell_label;
gchar    *audkrellm_opt_scroll_separator;

gboolean  audkrellm_opt_auto_start;
gboolean  audkrellm_opt_auto_main_close;
gboolean  audkrellm_opt_auto_hide_all;

gboolean  audkrellm_opt_scroll_enable;
gboolean  audkrellm_opt_draw_minus;

gint      audkrellm_opt_draw_in_time_bar;
gint      audkrellm_opt_krell_mmb_pause;
gint      audkrellm_opt_time_format;
gint      audkrellm_opt_always_load_info;

gboolean  audkrellm_opt_theme_show_button_bar;

/*
 * taken from gkrellmms-2.1.22/options.c#create_gkrellmms_config
 */
void audkrellm_create_config( GtkWidget *tab ) {
  GtkWidget *notebook, *frame, *vbox, *hseparator, *label;

  notebook = gtk_notebook_new();
  gtk_notebook_set_tab_pos( GTK_NOTEBOOK( notebook ), GTK_POS_TOP );
  gtk_box_pack_start( GTK_BOX( tab ), notebook, TRUE, TRUE, 0 );

  frame = gtk_frame_new( NULL );
  gtk_container_border_width( GTK_CONTAINER( frame ), 3 );

  vbox = gtk_vbox_new( FALSE, 0 );
  gtk_container_border_width( GTK_CONTAINER( vbox ), 3 );

  audkrellm_create_options_entries( vbox );

  hseparator = gtk_hseparator_new();
  gtk_container_add( GTK_CONTAINER( vbox ), hseparator );

  audkrellm_create_options_toggles( vbox );

  hseparator = gtk_hseparator_new();
  gtk_container_add( GTK_CONTAINER( vbox ), hseparator );

  audkrellm_create_options_switches( vbox );

  label = gtk_label_new( _( "Configs" ) );
  gtk_container_add( GTK_CONTAINER( frame ), vbox );
  gtk_notebook_append_page( GTK_NOTEBOOK( notebook ), frame, label );

  audkrellm_create_options_info( notebook );
}

/*
 * taken from gkrellmms-2.1.22/options.c#apply_gkrellmms_config
 */
void audkrellm_apply_config( void ) {
  audkrellm_apply_options_entries();
  audkrellm_apply_options_toggles();
  audkrellm_apply_options_switches();
}

/*
 * taken from gkrellmms-2.1.22/options.c#save_gkrellmms_config
 */
void audkrellm_save_config( FILE *f ) {
  fprintf( f, "%s audkrellm_exec_command %s\n",
           CONFIG_KEYWORD, audkrellm_opt_exec_command );
  fprintf( f, "%s audkrellm_krell_label %s\n",
           CONFIG_KEYWORD, audkrellm_opt_krell_label );
  fprintf( f, "%s audkrellm_scroll_separator \"%s\"\n",
           CONFIG_KEYWORD, audkrellm_opt_scroll_separator );

  fprintf( f, "%s audkrellm_auto_start %d\n",
           CONFIG_KEYWORD, audkrellm_opt_auto_start );
  fprintf( f, "%s audkrellm_auto_main_close %d\n",
           CONFIG_KEYWORD, audkrellm_opt_auto_main_close );
  fprintf( f, "%s audkrellm_auto_hide_all %d\n",
           CONFIG_KEYWORD, audkrellm_opt_auto_hide_all );

  fprintf( f, "%s audkrellm_scroll_enable %d\n",
           CONFIG_KEYWORD, audkrellm_opt_scroll_enable );
  fprintf( f, "%s audkrellm_draw_minus %d\n",
           CONFIG_KEYWORD, audkrellm_opt_draw_minus );

  fprintf( f, "%s audkrellm_draw_in_time_bar %d\n",
           CONFIG_KEYWORD, audkrellm_opt_draw_in_time_bar );
  fprintf( f, "%s audkrellm_krell_mmb_pause %d\n",
           CONFIG_KEYWORD, audkrellm_opt_krell_mmb_pause );
  fprintf( f, "%s audkrellm_time_format %d\n",
           CONFIG_KEYWORD, audkrellm_opt_time_format );
  fprintf( f, "%s audkrellm_always_load_info %d\n",
           CONFIG_KEYWORD, audkrellm_opt_always_load_info );

  fprintf( f, "%s theme_show_button_bar %d\n",
           CONFIG_KEYWORD, audkrellm_opt_theme_show_button_bar );
}

/*
 * taken from gkrellmms-2.1.22/options.c#load_gkrellmms_config
 */
void audkrellm_load_config( gchar *arg ) {
  gchar config[ 64 ], item[ 256 ], command[ 64 ];
  gint n;

  n = sscanf( arg, "%s %[^\n]", config, item );

  if( n == 2 ) {
    if( strcmp( config, "audkrellm_auto_start" ) == 0 ) {
      sscanf( item, "%d\n", &audkrellm_opt_auto_start );
    } else if( strcmp( config, "audkrellm_auto_main_close" ) == 0 ) {
      sscanf( item, "%d\n", &audkrellm_opt_auto_main_close );
    } else if( strcmp( config, "audkrellm_auto_hide_all" ) == 0 ) {
      sscanf( item, "%d\n", &audkrellm_opt_auto_hide_all );

    } else if( strcmp( config, "audkrellm_scroll_enable" ) == 0 ) {
      sscanf( item, "%d\n", &audkrellm_opt_scroll_enable );
    } else if( strcmp( config, "audkrellm_draw_minus" ) == 0 ) {
      sscanf( item, "%d\n", &audkrellm_opt_draw_minus );

    } else if( strcmp( config, "audkrellm_draw_in_time_bar" ) == 0 ) {
      sscanf( item, "%d\n", &audkrellm_opt_draw_in_time_bar );
    } else if( strcmp( config, "audkrellm_krell_mmb_pause" ) == 0 ) {
      sscanf( item, "%d\n", &audkrellm_opt_krell_mmb_pause );
    } else if( strcmp( config, "audkrellm_time_format" ) == 0 ) {
      sscanf( item, "%d\n", &audkrellm_opt_time_format );
    } else if( strcmp( config, "audkrellm_always_load_info" ) == 0 ) {
      sscanf( item, "%d\n", &audkrellm_opt_always_load_info );

    } else if( strcmp( config, "audkrellm_exec_command" ) == 0 ) {
      audkrellm_opt_exec_command = g_strdup( item );

    } else if( strcmp( config, "audkrellm_krell_label" ) == 0 ) {
      sscanf( item, "%s\n", command );
      g_free( audkrellm_opt_krell_label );
      audkrellm_opt_krell_label = g_strdup( command );

    } else if( strcmp( config, "audkrellm_scroll_separator" ) == 0 ) {
      glong sprt_str, sprt_len;
      gchar *scroll_temp = item;

      sprt_str = 0;
      while( item[ sprt_str ] != '"' ) {
        sprt_str++;
      }
      sprt_str++;

      sprt_len = sprt_str;
      while( item[ sprt_len ] != '"' ) {
        sprt_len++;
      }

      sprt_len = sprt_len - sprt_str;

      audkrellm_opt_scroll_separator
        = malloc( sizeof( char ) * ( sprt_len + 1 ) );
      memset( audkrellm_opt_scroll_separator, '\0', sprt_len + 1 );
      scroll_temp += sprt_str;
      memcpy( audkrellm_opt_scroll_separator, scroll_temp, sprt_len );
    }
  }

  if( !gkrellm_get_gkrellmrc_integer( "theme_show_button_bar",
                                      &audkrellm_opt_theme_show_button_bar ) ) {
    audkrellm_opt_theme_show_button_bar = TRUE;
  }
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c#gkrellm_init_plugin
 */
void audkrellm_set_default_config( void ) {
  audkrellm_opt_exec_command     = g_strdup( "audacious" );
  audkrellm_opt_krell_label      = g_strdup( "audacious" );
  audkrellm_opt_scroll_separator = g_strdup( SCROLL_SEPARATOR );

  audkrellm_opt_auto_start       = FALSE;
  audkrellm_opt_auto_main_close  = FALSE;
  audkrellm_opt_auto_hide_all    = FALSE;
  audkrellm_opt_scroll_enable    = TRUE;
  audkrellm_opt_draw_minus       = TRUE;

  audkrellm_opt_krell_mmb_pause  = L_SWITCH;
  audkrellm_opt_draw_in_time_bar = L_SWITCH;
  audkrellm_opt_time_format      = L_SWITCH;
  audkrellm_opt_always_load_info = L_SWITCH;

  audkrellm_opt_theme_show_button_bar      = TRUE;
}

/*
 * [EOF]
 */
