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
gchar    *opt_audacious_exec_command;
gchar    *opt_audkrellm_krell_label;
gchar    *opt_audkrellm_scroll_separator;

gboolean  opt_audacious_auto_start;
gboolean  opt_audacious_auto_main_close;
gboolean  opt_audacious_auto_hide_all;

gboolean  opt_audkrellm_scroll_enable;
gboolean  opt_audkrellm_draw_minus;

gint      opt_audkrellm_draw_in_time_bar;
gint      opt_audkrellm_krell_mmb_pause;
gint      opt_audkrellm_time_format;

gboolean  opt_theme_show_button_bar;

/*
 * taken from gkrellmms-2.1.22/options.c#create_gkrellmms_config
 */
void create_audkrellm_config( GtkWidget *tab ) {
  GtkWidget *notebook, *frame, *vbox, *hseparator, *label;

  notebook = gtk_notebook_new();
  gtk_notebook_set_tab_pos( GTK_NOTEBOOK( notebook ), GTK_POS_TOP );
  gtk_box_pack_start( GTK_BOX( tab ), notebook, TRUE, TRUE, 0 );

  frame = gtk_frame_new( NULL );
  gtk_container_border_width( GTK_CONTAINER( frame ), 3 );

  vbox = gtk_vbox_new( FALSE, 0 );
  gtk_container_border_width( GTK_CONTAINER( vbox ), 3 );

  create_options_entries( vbox );

  hseparator = gtk_hseparator_new();
  gtk_container_add( GTK_CONTAINER( vbox ), hseparator );

  create_options_toggles( vbox );

  hseparator = gtk_hseparator_new();
  gtk_container_add( GTK_CONTAINER( vbox ), hseparator );

  create_options_switches( vbox );

  label = gtk_label_new( _( "Configs" ) );
  gtk_container_add( GTK_CONTAINER( frame ), vbox );
  gtk_notebook_append_page( GTK_NOTEBOOK( notebook ), frame, label );

  create_options_info( notebook );
}

/*
 * taken from gkrellmms-2.1.22/options.c#apply_gkrellmms_config
 */
void apply_audkrellm_config( void ) {
  apply_options_configs();
  apply_options_toggles();
  apply_options_switches();
}

/*
 * taken from gkrellmms-2.1.22/options.c#save_gkrellmms_config
 */
void save_audkrellm_config( FILE *f ) {
  fprintf( f, "%s audacious_exec_command %s\n",
           CONFIG_KEYWORD, opt_audacious_exec_command );
  fprintf( f, "%s audkrellm_krell_label %s\n",
           CONFIG_KEYWORD, opt_audkrellm_krell_label );
  fprintf( f, "%s audkrellm_scroll_separator \"%s\"\n",
           CONFIG_KEYWORD, opt_audkrellm_scroll_separator );

  fprintf( f, "%s audacious_auto_start %d\n",
           CONFIG_KEYWORD, opt_audacious_auto_start );
  fprintf( f, "%s audacious_auto_main_close %d\n",
           CONFIG_KEYWORD, opt_audacious_auto_main_close );
  fprintf( f, "%s audacious_auto_hide_all %d\n",
           CONFIG_KEYWORD, opt_audacious_auto_hide_all );

  fprintf( f, "%s audkrellm_scroll_enable %d\n",
           CONFIG_KEYWORD, opt_audkrellm_scroll_enable );
  fprintf( f, "%s audkrellm_draw_minus %d\n",
           CONFIG_KEYWORD, opt_audkrellm_draw_minus );

  fprintf( f, "%s audkrellm_draw_in_time_bar %d\n",
           CONFIG_KEYWORD, opt_audkrellm_draw_in_time_bar );
  fprintf( f, "%s audkrellm_krell_mmb_pause %d\n",
           CONFIG_KEYWORD, opt_audkrellm_krell_mmb_pause );
  fprintf( f, "%s audkrellm_time_format %d\n",
           CONFIG_KEYWORD, opt_audkrellm_time_format );

  fprintf( f, "%s theme_show_button_bar %d\n",
           CONFIG_KEYWORD, opt_theme_show_button_bar );
}

/*
 * taken from gkrellmms-2.1.22/options.c#load_gkrellmms_config
 */
void load_audkrellm_config( gchar *arg ) {
  gchar config[ 64 ], item[ 256 ], command[ 64 ];
  gint n;

  n = sscanf( arg, "%s %[^\n]", config, item );

  if( n == 2 ) {
    if( strcmp( config, "audacious_auto_start" ) == 0 ) {
      sscanf( item, "%d\n", &opt_audacious_auto_start );
    } else if( strcmp( config, "audacious_auto_main_close" ) == 0 ) {
      sscanf( item, "%d\n", &opt_audacious_auto_main_close );
    } else if( strcmp( config, "audacious_auto_hide_all" ) == 0 ) {
      sscanf( item, "%d\n", &opt_audacious_auto_hide_all );

    } else if( strcmp( config, "audkrellm_scroll_enable" ) == 0 ) {
      sscanf( item, "%d\n", &opt_audkrellm_scroll_enable );
    } else if( strcmp( config, "audkrellm_draw_minus" ) == 0 ) {
      sscanf( item, "%d\n", &opt_audkrellm_draw_minus );

    } else if( strcmp( config, "audkrellm_draw_in_time_bar" ) == 0 ) {
      sscanf( item, "%d\n", &opt_audkrellm_draw_in_time_bar );
    } else if( strcmp( config, "audkrellm_krell_mmb_pause" ) == 0 ) {
      sscanf( item, "%d\n", &opt_audkrellm_krell_mmb_pause );
    } else if( strcmp( config, "audkrellm_time_format" ) == 0 ) {
      sscanf( item, "%d\n", &opt_audkrellm_time_format );

    } else if( strcmp( config, "audacious_exec_command" ) == 0 ) {
      opt_audacious_exec_command = g_strdup( item );

    } else if( strcmp( config, "audkrellm_krell_label" ) == 0 ) {
      sscanf( item, "%s\n", command );
      g_free( opt_audkrellm_krell_label );
      opt_audkrellm_krell_label = g_strdup( command );

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

      opt_audkrellm_scroll_separator
        = malloc( sizeof( char ) * ( sprt_len + 1 ) );
      memset( opt_audkrellm_scroll_separator, '\0', sprt_len + 1 );
      scroll_temp += sprt_str;
      memcpy( opt_audkrellm_scroll_separator, scroll_temp, sprt_len );
    }
  }

  if( !gkrellm_get_gkrellmrc_integer( "theme_show_button_bar",
                                      &opt_theme_show_button_bar ) ) {
    opt_theme_show_button_bar = TRUE;
  }
}

/*
 * taken from gkrellmms-2.1.22/gkrellmms.c#gkrellm_init_plugin
 */
void set_audkrellm_default_config( void ) {
  opt_audacious_exec_command     = g_strdup( "audacious" );
  opt_audkrellm_krell_label      = g_strdup( "audacious" );
  opt_audkrellm_scroll_separator = g_strdup( SCROLL_SEPARATOR );

  opt_audacious_auto_start       = FALSE;
  opt_audacious_auto_main_close  = FALSE;
  opt_audacious_auto_hide_all    = FALSE;
  opt_audkrellm_scroll_enable    = TRUE;
  opt_audkrellm_draw_minus       = TRUE;

  opt_audkrellm_krell_mmb_pause  = 0;
  opt_audkrellm_draw_in_time_bar = 0;
  opt_audkrellm_time_format      = 0;

  opt_theme_show_button_bar      = TRUE;
}

/*
 * [EOF]
 */
