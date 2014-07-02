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

static gint draw_in_time_bar_thing,
            krell_mmb_pause_thing,
            time_format_thing,
            always_load_info_thing;

/*
 * taken from gkrellmms-2.1.22/options.c#time_type_set
 */
static void set_type_draw_in_time_bar( GtkWidget *w, gpointer data ) {
  draw_in_time_bar_thing = GPOINTER_TO_INT( data );
}

/*
 * taken from gkrellmms-2.1.22/options.c#pause_type_set
 */
static void set_type_krell_mmb_pause( GtkWidget *w, gpointer data ) {
  krell_mmb_pause_thing = GPOINTER_TO_INT( data );
}

/*
 * taken from gkrellmms-2.1.22/options.c#time_fmt_type_set
 */
static void set_type_time_format( GtkWidget *w, gpointer data ) {
  time_format_thing = GPOINTER_TO_INT( data );
}

/*
 * taken from gkrellmms-2.1.22/options.c#load_type_set
 */
static void set_type_always_load_info( GtkWidget *w, gpointer data ) {
  always_load_info_thing = GPOINTER_TO_INT( data );
}

/*
 * taken from gkrellmms-2.1.22/options.c#create_gkrellmms_config
 */
void audkrellm_create_options_switches( GtkWidget *vbox ) {
  GtkWidget *table, *label,
            *draw_in_time_bar_radio,
            *krell_mmb_pause_radio,
            *time_format_radio,
            *always_load_info_radio;
  GSList *draw_in_time_bar_group = NULL,
         *krell_mmb_pause_group = NULL,
         *time_format_group = NULL,
         *always_load_info_group = NULL;

  table = gtk_table_new( 3, 4, FALSE );

  /* audkrellm_opt_draw_in_time_bar: label */
  label = gtk_label_new( _( "Draw in time bar:" ) );
  gtk_table_attach( GTK_TABLE( table ), label, 0, 1, 0, 1,
                    GTK_SHRINK, GTK_SHRINK, 0, 0 );

  /* audkrellm_opt_draw_in_time_bar: L_SWITCH */
  draw_in_time_bar_thing = audkrellm_opt_draw_in_time_bar;
  draw_in_time_bar_radio
    = gtk_radio_button_new_with_label( NULL, _( "Output time" ) );
  draw_in_time_bar_group
    = gtk_radio_button_group( GTK_RADIO_BUTTON( draw_in_time_bar_radio ) );
  gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( draw_in_time_bar_radio ),
                                audkrellm_opt_draw_in_time_bar );
  gtk_signal_connect( GTK_OBJECT( draw_in_time_bar_radio ), "pressed",
                      (GtkSignalFunc)set_type_draw_in_time_bar,
                      GINT_TO_POINTER( L_SWITCH ) );
  gtk_table_attach( GTK_TABLE( table ), draw_in_time_bar_radio, 1, 2, 0, 1,
                    GTK_SHRINK, GTK_SHRINK, 0, 0 );

  /* audkrellm_opt_draw_in_time_bar: R_SWITCH */
  draw_in_time_bar_radio
    = gtk_radio_button_new_with_label( draw_in_time_bar_group,
                                       _( "Audacious-text" ) );
  gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( draw_in_time_bar_radio ),
                                ! audkrellm_opt_draw_in_time_bar );
  gtk_signal_connect( GTK_OBJECT( draw_in_time_bar_radio ), "pressed",
                      (GtkSignalFunc)set_type_draw_in_time_bar,
                      GINT_TO_POINTER( R_SWITCH ) );
  gtk_table_attach( GTK_TABLE( table ), draw_in_time_bar_radio, 2, 3, 0, 1,
                    GTK_SHRINK, GTK_SHRINK, 0, 0 );

  /* audkrellm_opt_krell_mmb_pause: label */
  label = gtk_label_new( _( "Middle mouse click on krell will:" ) );
  gtk_table_attach( GTK_TABLE( table ), label, 0, 1, 1, 2,
                    GTK_SHRINK, GTK_SHRINK, 0, 0 );

  /* audkrellm_opt_krell_mmb_pause: L_SWITCH */
  krell_mmb_pause_thing = audkrellm_opt_krell_mmb_pause;
  krell_mmb_pause_radio
    = gtk_radio_button_new_with_label( NULL, _( "Pause/Continue song" ) );
  krell_mmb_pause_group
    = gtk_radio_button_group( GTK_RADIO_BUTTON( krell_mmb_pause_radio ) );
  gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( krell_mmb_pause_radio ),
                                audkrellm_opt_krell_mmb_pause );
  gtk_signal_connect( GTK_OBJECT( krell_mmb_pause_radio ), "pressed",
                      (GtkSignalFunc)set_type_krell_mmb_pause,
                      GINT_TO_POINTER( L_SWITCH ) );
  gtk_table_attach( GTK_TABLE( table ), krell_mmb_pause_radio, 1, 2, 1, 2,
                    GTK_SHRINK, GTK_SHRINK, 0, 0 );

  /* audkrellm_opt_krell_mmb_pause: R_SWITCH */
  krell_mmb_pause_radio
    = gtk_radio_button_new_with_label( krell_mmb_pause_group,
                                       _( "Stop/Play song" ) );
  gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( krell_mmb_pause_radio ),
                                ! audkrellm_opt_krell_mmb_pause );
  gtk_signal_connect( GTK_OBJECT( krell_mmb_pause_radio ), "pressed",
                      (GtkSignalFunc)set_type_krell_mmb_pause,
                      GINT_TO_POINTER( R_SWITCH ) );
  gtk_table_attach( GTK_TABLE( table ), krell_mmb_pause_radio, 2, 3, 1, 2,
                    GTK_SHRINK, GTK_SHRINK, 0, 0 );

  /* time_format: label */
  label = gtk_label_new( _( "Output time format:" ) );
  gtk_table_attach( GTK_TABLE( table ), label, 0, 1, 2, 3,
                    GTK_SHRINK, GTK_SHRINK, 0, 0 );

  /* time_format: L_SWITCH */
  time_format_thing = audkrellm_opt_time_format;
  time_format_radio
    = gtk_radio_button_new_with_label( NULL, _( "Elapsed time" ) );
  time_format_group
    = gtk_radio_button_group( GTK_RADIO_BUTTON( time_format_radio ) );
  gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( time_format_radio ),
                                audkrellm_opt_time_format );
  gtk_signal_connect( GTK_OBJECT( time_format_radio ), "pressed",
                      (GtkSignalFunc)set_type_time_format,
                      GINT_TO_POINTER( L_SWITCH ) );
  gtk_table_attach( GTK_TABLE( table ), time_format_radio, 1, 2, 2, 3,
                    GTK_SHRINK, GTK_SHRINK, 0, 0 );

  /* time_format: R_SWITCH */
  time_format_radio
    = gtk_radio_button_new_with_label( time_format_group,
                                       _( "Remaining time" ) );
  gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( time_format_radio ),
                                ! audkrellm_opt_time_format );
  gtk_signal_connect( GTK_OBJECT( time_format_radio ), "pressed",
                      (GtkSignalFunc)set_type_time_format,
                      GINT_TO_POINTER( R_SWITCH ) );
  gtk_table_attach( GTK_TABLE( table ), time_format_radio, 2, 3, 2, 3,
                    GTK_SHRINK, GTK_SHRINK, 0, 0 );

  /* always load info: label */
  label = gtk_label_new( _( "load info:" ) );
  gtk_table_attach( GTK_TABLE( table ), label, 0, 1, 3, 4,
                    GTK_SHRINK, GTK_SHRINK, 0, 0 );

  /* always load info : L_SWITCH */
  always_load_info_thing = audkrellm_opt_always_load_info;
  always_load_info_radio
    = gtk_radio_button_new_with_label( NULL,
                                       _( "Always" ) );
  always_load_info_group
    = gtk_radio_button_group( GTK_RADIO_BUTTON( always_load_info_radio ) );
  gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( always_load_info_radio ),
                                audkrellm_opt_always_load_info );
  gtk_signal_connect( GTK_OBJECT( always_load_info_radio ), "pressed",
                      (GtkSignalFunc)set_type_always_load_info,
                      GINT_TO_POINTER( L_SWITCH ) );
  gtk_table_attach( GTK_TABLE( table ), always_load_info_radio, 1, 2, 3, 4,
                    GTK_SHRINK, GTK_SHRINK, 0, 0 );

  /* always load info : R_SWITCH */
  always_load_info_radio
    = gtk_radio_button_new_with_label( always_load_info_group,
                                       _( "On File play only" ) );
  gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( always_load_info_radio ),
                                ! audkrellm_opt_always_load_info );
  gtk_signal_connect( GTK_OBJECT( always_load_info_radio ), "pressed",
                      (GtkSignalFunc)set_type_always_load_info,
                      GINT_TO_POINTER( R_SWITCH ) );
  gtk_table_attach( GTK_TABLE( table ), always_load_info_radio, 2, 3, 3, 4,
                    GTK_SHRINK, GTK_SHRINK, 0, 0 );

  gtk_container_add( GTK_CONTAINER( vbox ), table );
}

/*
 * taken from gkrellmms-2.1.22/options.c#apply_gkrellmms_config
 */
void audkrellm_apply_options_switches( void ) {
  audkrellm_opt_krell_mmb_pause  = krell_mmb_pause_thing;
  audkrellm_opt_draw_in_time_bar = draw_in_time_bar_thing;
  audkrellm_opt_time_format      = time_format_thing;
  audkrellm_opt_always_load_info = always_load_info_thing;
}

/*
 * [EOF]
 */
