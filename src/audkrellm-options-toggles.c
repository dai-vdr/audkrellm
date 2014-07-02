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

static GtkWidget *auto_start_toggle,
                 *auto_main_close_toggle,
                 *auto_hide_all_toggle,
                 *scroll_enable_toggle,
                 *draw_minus_toggle;

/*
 * taken from gkrellmms-2.1.22/options.c#create_gkrellmms_config
 */
void audkrellm_create_options_toggles( GtkWidget *vbox ) {
  /* audkrellm_opt_auto_start */
  auto_start_toggle = gtk_check_button_new_with_label(
    _( "Auto launch Audacious on AudKrellM startup" ) );
  gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( auto_start_toggle ),
                                audkrellm_opt_auto_start );
  gtk_container_add( GTK_CONTAINER( vbox ), auto_start_toggle );

  /* audkrellm_opt_auto_main_close */
  auto_main_close_toggle = gtk_check_button_new_with_label(
    _( "Auto close (and open) Audacious Mainwin" ) );
  gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( auto_main_close_toggle ),
                                audkrellm_opt_auto_main_close );
  gtk_container_add( GTK_CONTAINER( vbox ), auto_main_close_toggle );

  /* audkrellm_opt_auto_hide_all */
  auto_hide_all_toggle = gtk_check_button_new_with_label(
    _( "Auto hide all Audacious windows on Audacious startup" ) );
  gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( auto_hide_all_toggle ),
                                audkrellm_opt_auto_hide_all );
  gtk_container_add( GTK_CONTAINER( vbox ), auto_hide_all_toggle );

  /* audkrellm_opt_scroll_enable */
  scroll_enable_toggle = gtk_check_button_new_with_label(
     _( "Enable scrolling title panel" ) );
  gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( scroll_enable_toggle ),
                                audkrellm_opt_scroll_enable );
  gtk_container_add( GTK_CONTAINER( vbox ), scroll_enable_toggle );

  /* audkrellm_opt_draw_minus */
  draw_minus_toggle = gtk_check_button_new_with_label(
    _( "Draw minus (-) when displaying remaining time" ) );
  gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( draw_minus_toggle ),
                                audkrellm_opt_draw_minus );
  gtk_container_add( GTK_CONTAINER( vbox ), draw_minus_toggle );
}

/*
 * taken from gkrellmms-2.1.22/options.c#apply_gkrellmms_config
 */
void audkrellm_apply_options_toggles( void ) {
  audkrellm_opt_auto_start
    = GTK_TOGGLE_BUTTON( auto_start_toggle )->active;
  audkrellm_opt_auto_main_close
    = GTK_TOGGLE_BUTTON( auto_main_close_toggle )->active;
  audkrellm_opt_auto_hide_all
    = GTK_TOGGLE_BUTTON( auto_hide_all_toggle )->active;

  audkrellm_opt_scroll_enable
    = GTK_TOGGLE_BUTTON( scroll_enable_toggle )->active;
  audkrellm_opt_draw_minus
    = GTK_TOGGLE_BUTTON( draw_minus_toggle )->active;
}

/*
 * [EOF]
 */
