//
//  main.c
//  projet_c
//
//  Created by Richard Guerci on 21/03/12.
//  Copyright © 2012 Charles Bessonnet & Richard Guerci. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "callback.h"
#include "structures.h"
#include "menu.h"
#include "fenetre_image.h"
//si on est sur mac
#ifdef MAC
#include "gtksdl.h"
#endif


int main (int argc, char **argv)
{
    GtkWidget *p_window;
    GtkWidget *p_main_box;
    GtkWidget *p_frame_box;
    GtkWidget *p_menu;
    GtkWidget *p_frame;
    GtkWidget *p_scale;
    GtkWidget *p_btn;
    GtkWidget *p_btn_quit;
    GtkWidget *p_image;
    
    gint x,y;
    
    //Initialisation de GTK+
    gtk_init (&argc, &argv);
    
    //Creation de la fenetre principale
    p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(p_window), GTK_WIN_POS_CENTER);
    gtk_window_get_position(GTK_WINDOW(p_window), &x, &y);
    gtk_window_move(GTK_WINDOW(p_window), x-350, y-200);
    gtk_window_set_default_size(GTK_WINDOW(p_window), 140, 410);
    gtk_window_set_title (GTK_WINDOW (p_window), "Portable PixMap Editor");
    g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (cb_quit), p_window);
    
    //Creation du conteneur principal
    p_main_box = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (p_window), p_main_box);
    
    //Creation du menu
    p_menu = gtk_text_view_new ();
    gtk_box_pack_start (GTK_BOX (p_main_box), GTK_WIDGET (menu_new (p_window)), FALSE, FALSE, 0);
    
    //boutons du zoom
    p_frame = gtk_frame_new("Zoom");
    gtk_box_pack_start(GTK_BOX(p_main_box), p_frame, TRUE, FALSE, 0);
    p_frame_box = gtk_hbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(p_frame), p_frame_box);
    p_btn = gtk_button_new();
    p_image = gtk_image_new_from_stock(GTK_STOCK_ZOOM_IN, GTK_ICON_SIZE_MENU);
    gtk_button_set_image(GTK_BUTTON(p_btn),p_image);
    gtk_container_add(GTK_CONTAINER(p_frame_box), p_btn);
    g_signal_connect(G_OBJECT(p_btn), "pressed", G_CALLBACK(cb_zoom_in), p_window);
    p_btn = gtk_button_new();
    p_image = gtk_image_new_from_stock(GTK_STOCK_ZOOM_100, GTK_ICON_SIZE_MENU);
    gtk_button_set_image(GTK_BUTTON(p_btn),p_image);
    gtk_container_add(GTK_CONTAINER(p_frame_box), p_btn);
    g_signal_connect(G_OBJECT(p_btn), "clicked", G_CALLBACK(cb_zoom_init), p_window);
    p_btn = gtk_button_new();
    p_image = gtk_image_new_from_stock(GTK_STOCK_ZOOM_OUT, GTK_ICON_SIZE_MENU);
    gtk_button_set_image(GTK_BUTTON(p_btn),p_image);
    gtk_container_add(GTK_CONTAINER(p_frame_box), p_btn);
    g_signal_connect(G_OBJECT(p_btn), "pressed", G_CALLBACK(cb_zoom_out), p_window);
    
    //boutons taille
    p_frame = gtk_frame_new("Taille");
    gtk_box_pack_start(GTK_BOX(p_main_box), p_frame, TRUE, FALSE, 0);
    p_frame_box = gtk_hbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(p_frame), p_frame_box);
    p_btn = gtk_button_new();
    p_image = gtk_image_new_from_stock(GTK_STOCK_ADD, GTK_ICON_SIZE_MENU);
    gtk_button_set_image(GTK_BUTTON(p_btn),p_image);
    gtk_container_add(GTK_CONTAINER(p_frame_box), p_btn);
    g_signal_connect(G_OBJECT(p_btn), "pressed", G_CALLBACK(cb_taille_plus), p_window);
    p_btn = gtk_button_new();
    p_image = gtk_image_new_from_stock(GTK_STOCK_REMOVE, GTK_ICON_SIZE_MENU);
    gtk_button_set_image(GTK_BUTTON(p_btn),p_image);
    gtk_container_add(GTK_CONTAINER(p_frame_box), p_btn);
    g_signal_connect(G_OBJECT(p_btn), "pressed", G_CALLBACK(cb_taille_moins), p_window);
    
    //boutons symétrie et rotation
    p_frame = gtk_frame_new("Symétrie et Rotation");
    gtk_box_pack_start(GTK_BOX(p_main_box), p_frame, TRUE, FALSE, 0);
    p_frame_box = gtk_hbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(p_frame), p_frame_box);
    p_btn = gtk_button_new();
    p_image = gtk_image_new_from_stock(GTK_STOCK_REDO, GTK_ICON_SIZE_MENU);
    gtk_button_set_image(GTK_BUTTON(p_btn),p_image);
    gtk_container_add(GTK_CONTAINER(p_frame_box), p_btn);
    g_signal_connect(G_OBJECT(p_btn), "pressed", G_CALLBACK(cb_rotation_droite), p_window);
    p_btn = gtk_button_new();
    p_image = gtk_image_new_from_stock(GTK_STOCK_ORIENTATION_REVERSE_PORTRAIT, GTK_ICON_SIZE_MENU);
    gtk_button_set_image(GTK_BUTTON(p_btn),p_image);
    gtk_container_add(GTK_CONTAINER(p_frame_box), p_btn);
    g_signal_connect(G_OBJECT(p_btn), "pressed", G_CALLBACK(cb_symetrie_horizontale), p_window);
    p_btn = gtk_button_new();
    p_image = gtk_image_new_from_stock(GTK_STOCK_ORIENTATION_REVERSE_LANDSCAPE, GTK_ICON_SIZE_MENU);
    gtk_button_set_image(GTK_BUTTON(p_btn),p_image);
    gtk_container_add(GTK_CONTAINER(p_frame_box), p_btn);
    g_signal_connect(G_OBJECT(p_btn), "pressed", G_CALLBACK(cb_symetrie_verticale), p_window);
    p_btn = gtk_button_new();
    p_image = gtk_image_new_from_stock(GTK_STOCK_UNDO, GTK_ICON_SIZE_MENU);
    gtk_button_set_image(GTK_BUTTON(p_btn),p_image);
    gtk_container_add(GTK_CONTAINER(p_frame_box), p_btn);
    g_signal_connect(G_OBJECT(p_btn), "pressed", G_CALLBACK(cb_rotation_gauche), p_window);
    
    //boutons du traitement de l'image
    p_frame = gtk_frame_new("Traitement");
    gtk_box_pack_start(GTK_BOX(p_main_box), p_frame, TRUE, FALSE, 0);
    p_frame_box = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(p_frame), p_frame_box);
    p_btn = gtk_button_new_with_label(" Negatif    ");
    p_image = gtk_image_new_from_stock(GTK_STOCK_SELECT_COLOR, GTK_ICON_SIZE_MENU);
    gtk_button_set_image(GTK_BUTTON(p_btn),p_image);
    gtk_container_add(GTK_CONTAINER(p_frame_box), p_btn);
    g_signal_connect(G_OBJECT(p_btn), "pressed", G_CALLBACK(cb_negatif), p_window);
    p_btn = gtk_button_new_with_label(" Gris        ");
    p_image = gtk_image_new_from_stock(GTK_STOCK_SELECT_COLOR, GTK_ICON_SIZE_MENU);
    gtk_button_set_image(GTK_BUTTON(p_btn),p_image);
    gtk_container_add(GTK_CONTAINER(p_frame_box), p_btn);
    g_signal_connect(G_OBJECT(p_btn), "pressed", G_CALLBACK(cb_gris), p_window);
    p_btn = gtk_button_new_with_label(" Sepia       ");
    p_image = gtk_image_new_from_stock(GTK_STOCK_SELECT_COLOR, GTK_ICON_SIZE_MENU);
    gtk_button_set_image(GTK_BUTTON(p_btn),p_image);
    gtk_container_add(GTK_CONTAINER(p_frame_box), p_btn);
    g_signal_connect(G_OBJECT(p_btn), "pressed", G_CALLBACK(cb_sepia), p_window);
    p_btn = gtk_button_new_with_label(" Flou        ");
    p_image = gtk_image_new_from_stock(GTK_STOCK_SELECT_COLOR, GTK_ICON_SIZE_MENU);
    gtk_button_set_image(GTK_BUTTON(p_btn),p_image);
    gtk_container_add(GTK_CONTAINER(p_frame_box), p_btn);
    g_signal_connect(G_OBJECT(p_btn), "pressed", G_CALLBACK(cb_flou), p_window);
    
    //Curseur RGB
    p_frame = gtk_frame_new("Rouge");
    p_scale = gtk_hscale_new_with_range(-255, 255, 1);
    gtk_range_set_value(GTK_RANGE(p_scale), 0);
    gtk_container_add(GTK_CONTAINER(p_frame), p_scale);
    gtk_box_pack_start(GTK_BOX(p_main_box), p_frame, FALSE, FALSE, 0);
    g_signal_connect (G_OBJECT (p_scale), "value-changed", G_CALLBACK(cb_rouge), p_window);
    p_frame = gtk_frame_new("Vert");
    p_scale = gtk_hscale_new_with_range(-255, 255, 1);
    gtk_range_set_value(GTK_RANGE(p_scale), 0);
    gtk_container_add(GTK_CONTAINER(p_frame), p_scale);
    gtk_box_pack_start(GTK_BOX(p_main_box), p_frame, FALSE, FALSE, 0);
    g_signal_connect (G_OBJECT (p_scale), "value-changed", G_CALLBACK(cb_vert), p_window);
    p_frame = gtk_frame_new("Bleu");
    p_scale = gtk_hscale_new_with_range(-255, 255, 1);
    gtk_range_set_value(GTK_RANGE(p_scale), 0);
    gtk_container_add(GTK_CONTAINER(p_frame), p_scale);
    gtk_box_pack_start(GTK_BOX(p_main_box), p_frame, FALSE, FALSE, 0);
    g_signal_connect (G_OBJECT (p_scale), "value-changed", G_CALLBACK(cb_bleu), p_window);
    
    
    //Bouton tout annuler
    p_btn_quit = gtk_button_new_with_mnemonic (" Tout annuler");
    p_image = gtk_image_new_from_stock(GTK_STOCK_CANCEL, GTK_ICON_SIZE_MENU);
    gtk_button_set_image(GTK_BUTTON(p_btn_quit),p_image);    
    gtk_box_pack_start(GTK_BOX(p_main_box), p_btn_quit, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(p_btn_quit), "clicked", G_CALLBACK(cb_annuler), p_window);
    
    //Bouton quitter
    p_btn_quit = gtk_button_new_with_mnemonic (" Quitter");
    p_image = gtk_image_new_from_stock(GTK_STOCK_QUIT, GTK_ICON_SIZE_MENU);
    gtk_button_set_image(GTK_BUTTON(p_btn_quit),p_image);    
    gtk_box_pack_start(GTK_BOX(p_main_box), p_btn_quit, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(p_btn_quit), "clicked", G_CALLBACK(cb_quit), p_window);
    
    //Affichage des fenetres
    gtk_widget_show_all (p_window);
    
    //Lancement de la boucle principale
    gtk_main ();
    
    return EXIT_SUCCESS;
}

