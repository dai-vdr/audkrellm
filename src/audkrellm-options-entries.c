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
#include "audkrellm-scroll-panel.h"

#include "audkrellm-options.h"

static GtkWidget *exec_command_entry,
                 *label_entry,
                 *separator_entry;

/*
 * taken from gkrellmms-2.1.22/options.c#create_gkrellmms_config
 */
void audkrellm_create_options_entries( GtkWidget *vbox ) {
  GtkWidget *table, *label;

  table = gtk_table_new( 2, 2, FALSE );

  /* audkrellm_opt_exec_command */
  label = gtk_label_new( _( "Audacious Executable:" ) );
  gtk_table_attach( GTK_TABLE( table ), label, 0, 1, 0, 1,
                    GTK_SHRINK, GTK_SHRINK, 0, 0 );

  exec_command_entry = gtk_entry_new_with_max_length( 255 );
  gtk_entry_set_text( GTK_ENTRY( exec_command_entry ),
                      audkrellm_opt_exec_command );
  gtk_entry_set_editable( GTK_ENTRY( exec_command_entry ), TRUE );
  gtk_table_attach( GTK_TABLE( table ), exec_command_entry, 1, 2, 0, 1,
                    GTK_SHRINK, GTK_SHRINK, 0, 0 );

  /* audkrellm_opt_krell_label */
  label = gtk_label_new( _( "Krell label:" ) );
  gtk_table_attach( GTK_TABLE( table ), label, 0, 1, 1, 2,
                    GTK_SHRINK, GTK_SHRINK, 0, 0 );

  label_entry = gtk_entry_new_with_max_length( 16 );
  gtk_entry_set_text( GTK_ENTRY( label_entry ), audkrellm_opt_krell_label );
  gtk_entry_set_editable( GTK_ENTRY( label_entry ), TRUE );
  gtk_table_attach( GTK_TABLE( table ), label_entry, 1, 2, 1, 2,
                    GTK_SHRINK, GTK_SHRINK, 0, 0 );

  label = gtk_label_new( _( "Scroll separator:" ) );
  gtk_table_attach( GTK_TABLE( table ), label, 0, 1, 2, 3,
                    GTK_SHRINK, GTK_SHRINK, 0, 0 );

  separator_entry = gtk_entry_new_with_max_length( MAXLEN_SCROLL_SEPARATOR );
  gtk_entry_set_text( GTK_ENTRY( separator_entry ),
                      audkrellm_opt_scroll_separator );
  gtk_entry_set_editable( GTK_ENTRY( separator_entry ), TRUE );
  gtk_table_attach( GTK_TABLE( table ), separator_entry, 1, 2, 2, 3,
                    GTK_SHRINK, GTK_SHRINK, 0, 0 );

  gtk_container_add( GTK_CONTAINER( vbox ), table );
}

/*
 * taken from gkrellmms-2.1.22/options.c#apply_gkrellmms_config
 */
void audkrellm_apply_options_entries( void ) {
  g_free( audkrellm_opt_exec_command );
  audkrellm_opt_exec_command
    = g_strdup( gtk_entry_get_text( GTK_ENTRY( exec_command_entry ) ) );

  g_free( audkrellm_opt_krell_label );
  audkrellm_opt_krell_label
    = g_strdup(gtk_entry_get_text( GTK_ENTRY( label_entry ) ) );

  g_free( audkrellm_opt_scroll_separator );
  audkrellm_opt_scroll_separator
    = g_strdup( gtk_entry_get_text( GTK_ENTRY( separator_entry ) ) );
  audkrellm_set_scroll_separator_len();
}

/*
 * [EOF]
 */
