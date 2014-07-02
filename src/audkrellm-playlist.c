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

#include "audkrellm-playlist.h"

enum { 
  PLAYLIST_POSITION = 0,
  PLAYLIST_TITLE,
  PLAYLIST_FILENAME,
  PLAYLIST_TIME,
  PLAYLIST_NRCOLUMNS
};

/* the store for the playlist */
static GtkListStore *playlist = NULL; 

/* fast access for the current functions */
static gchar *current_file = NULL;
static gchar *current_title = NULL;
static gint   current_time = 0;
static gint   current_position = 0;

/* playlist lenght is an indicator for changes */
static gint playlist_length = -1;

/*
 * taken from gkrellmms-2.1.22/playlist.c#pl_get_current_file
 */
gchar *audkrellm_get_current_file( void ) {
  return current_file == NULL ? "" : current_file;
}

/*
 * taken from gkrellmms-2.1.22/playlist.c#pl_get_current_title
 */
gchar *audkrellm_get_current_title( void ) {
  return current_title == NULL ? "" : current_title;
}

/*
 * taken from gkrellmms-2.1.22/playlist.c#pl_get_current_time
 */
gint audkrellm_get_current_time( void ) {
  return current_time;
}

/*
 * taken from gkrellmms-2.1.22/playlist.c#pl_get_current_position
 */
gint audkrellm_get_current_position( void ) {
  return current_position;
}

/*
 * taken from gkrellmms-2.1.22/playlist.c
 */
static void update_playlist_position( void ) {
  GtkTreeIter iter;

  current_position = audacious_remote_get_playlist_pos( audkrellm_session ) + 1;
  g_free( current_title );
  g_free( current_file );

  if( gtk_tree_model_iter_nth_child( GTK_TREE_MODEL( playlist ),
                                     &iter, NULL, (current_position - 1) ) )  {
    current_file  = audacious_remote_get_playlist_file( audkrellm_session,
                                                       current_position - 1 );
    current_title = audacious_remote_get_playlist_title( audkrellm_session,
                                                         current_position - 1 );
    current_time  = audacious_remote_get_playlist_time( audkrellm_session,
                                                        current_position - 1 );
    if( current_title == NULL && current_file != NULL ) { 
      current_title = g_strdup( current_file );
    }
    /* get the info from xmms to be sure it's up to data */
    gtk_list_store_set( playlist, &iter,
                        PLAYLIST_TITLE,
                        current_title == NULL ? "" : current_title,
                        PLAYLIST_FILENAME,
                        current_file == NULL ? "" : current_file,
                        PLAYLIST_TIME,
                        current_time,
                        -1 );
  } else {
    current_title    = NULL;
    current_file     = NULL;
    current_position = 0;
    current_time     = 0;
  }
}

/*
 * taken from gkrellmms-2.1.22/playlist.c
 */
static void empty_playlist( void ) {
  gtk_list_store_clear( playlist );
  update_playlist_position();
}

/*
 * taken from gkrellmms-2.1.22/playlist.c
 */
static void load_playlist( void ) {
  gint len, i;
  gint time;
  gchar *filename, *title, *basename;
  GtkTreeIter iter;

  if( ! audacious_remote_is_running( audkrellm_session ) ) {
    return;
  }

  len = audacious_remote_get_playlist_length( audkrellm_session );
  playlist_length = len;

  for( i = 0; i < len; i ++ ) {
    filename = audacious_remote_get_playlist_file( audkrellm_session, i );
    if( filename == NULL ) {
      /* error occurred empty playlist and try again */
      empty_playlist();
      return load_playlist();
    }

    while( gtk_events_pending() ) {
      gtk_main_iteration();
    }

    gtk_list_store_append( playlist, &iter );

    if( audkrellm_opt_always_load_info ) {
      title = audacious_remote_get_playlist_title( audkrellm_session, i );
      time = audacious_remote_get_playlist_time( audkrellm_session, i );
      gtk_list_store_set( playlist, &iter,
                          PLAYLIST_POSITION, i + 1,
                          PLAYLIST_TITLE,    title == NULL ? "" : title,
                          PLAYLIST_FILENAME, filename,
                          PLAYLIST_TIME,     time,
                          -1 );
      g_free( title );
    } else {
      basename = filename == NULL ? NULL : g_path_get_basename( filename );
      gtk_list_store_set( playlist, &iter,
                          PLAYLIST_POSITION, i + 1,
                          PLAYLIST_TITLE,    basename,
                          PLAYLIST_FILENAME, filename,
                          PLAYLIST_TIME,     0,
                          -1 );
      g_free( basename );
    }
    g_free( filename );
  }
  update_playlist_position();
}

/*
 * taken from gkrellmms-2.1.22/playlist.c#update_playlist
 */
gint audkrellm_update_playlist( void ) {
  gchar *filename = NULL;

  /* XXX: Workaround */
  current_position = audacious_remote_get_playlist_pos( audkrellm_session ) + 1;

  /* playlist length changed, reload */
  if( playlist_length
        != audacious_remote_get_playlist_length( audkrellm_session ) ) {
    empty_playlist();
    load_playlist();
    return TRUE;
  }
  filename = audacious_remote_get_playlist_file( audkrellm_session,
                                                 current_position - 1 );
  
  if( filename == NULL || strcmp( audkrellm_get_current_file(), filename ) ) {
    empty_playlist();
    load_playlist();
    g_free( filename );
    return TRUE;
  }
  g_free( filename );

  if( audacious_remote_get_playlist_pos( audkrellm_session )
        != current_position + 1 ) {
    update_playlist_position();
  }

  return TRUE;
}

/*
 * taken from gkrellmms-2.1.22/playlist.c#pl_init
 */
void audkrellm_init_playlist( void ) {
  playlist = gtk_list_store_new( PLAYLIST_NRCOLUMNS,
                                 GTK_TYPE_INT,
                                 GTK_TYPE_STRING,
                                 GTK_TYPE_STRING,
                                 GTK_TYPE_INT );
}

/*
 * [EOF]
 */
