//
//  callback.h
//  projet_c
//
//  Created by Richard Guerci on 21/03/12.
//  Copyright © 2012 Charles Bessonnet & Richard Guerci. All rights reserved.
//

#ifndef H_CALLBACK
#define H_CALLBACK

#include <gtk/gtk.h>

void cb_open (GtkWidget *, gpointer);
void cb_open_test (GtkWidget *, gpointer);
void cb_save (GtkWidget *, gpointer);
void cb_saveas (GtkWidget *, gpointer);
void close_image (GtkWidget *, gpointer);
void cb_close (GtkWidget *, gpointer);
void cb_quit (GtkWidget *, gpointer);

void cb_guide (GtkWidget *, gpointer);
void cb_about (GtkWidget *, gpointer);


void cb_zoom_in (GtkWidget *p_widget, gpointer user_data);
void cb_zoom_out (GtkWidget *p_widget, gpointer user_data);
void cb_zoom_init (GtkWidget *p_widget, gpointer user_data);

void cb_rouge (GtkWidget *p_widget, gpointer user_data);
void cb_vert (GtkWidget *p_widget, gpointer user_data);
void cb_bleu (GtkWidget *p_widget, gpointer user_data);

void cb_negatif (GtkWidget *p_widget, gpointer user_data);
void cb_gris (GtkWidget *p_widget, gpointer user_data);
void cb_sepia (GtkWidget *p_widget, gpointer user_data);
void cb_flou (GtkWidget *p_widget, gpointer user_data);

void cb_symetrie_horizontale (GtkWidget *p_widget, gpointer user_data);
void cb_symetrie_verticale (GtkWidget *p_widget, gpointer user_data);
void cb_rotation_droite (GtkWidget *p_widget, gpointer user_data);
void cb_rotation_gauche (GtkWidget *p_widget, gpointer user_data);

void cb_annuler (GtkWidget *p_widget, gpointer user_data);


void cb_taille_plus (GtkWidget *p_widget, gpointer user_data);
void cb_taille_moins (GtkWidget *p_widget, gpointer user_data);

#endif
