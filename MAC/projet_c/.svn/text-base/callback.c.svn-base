//
//  callback.c
//  projet_c
//
//  Created by Richard Guerci on 21/03/12.
//  Copyright © 2012 Charles Bessonnet & Richard Guerci. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "callback.h"
#include "structures.h"
#include "fenetre_image.h"
#include "error.h"
#include "ppm.h"
#include <time.h>
#include <math.h>
#include <regex.h>
#include "save.h"

#define imp(a) ((a%2)==0?a-1:a)
RGB **pixels_ref;
char *path;
char *default_path="test.ppm";

void cb_open (GtkWidget *p_widget, gpointer user_data){
    if (image_init.pixels==NULL){
        GtkWidget *p_dialog = NULL;
        int i,j;
        gint x,y;
        p_dialog = gtk_file_chooser_dialog_new ("Ouvrir un fichier", user_data,
                                                GTK_FILE_CHOOSER_ACTION_OPEN,
                                                GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                                GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                                NULL);
        if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT)
        {
            path = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
            regex_t preg;
            int err;
            const char *str_request = path;
            const char *str_regex = "\\.ppm$";
            err = regcomp (&preg, str_regex, REG_NOSUB | REG_EXTENDED);
            if (err == 0)
            {
                int match;
                match = regexec (&preg, str_request, 0, NULL, 0);
                regfree (&preg);
                if(match==0){
                    taille_pixel=1;
                    
                    lecturePPM(path);
                    
                    
                    //Duplication de l'image
                    image_modif.nbMagique=image_init.nbMagique;
                    image_modif.largeur=image_init.largeur;
                    image_modif.hauteur=image_init.hauteur;
                    image_modif.niveau_max=image_init.niveau_max;
                    image_modif.pixels=(RGB**) malloc(image_modif.hauteur*sizeof(RGB*));
                    for(i=0;i<image_modif.hauteur;i++){
                        image_modif.pixels[i]=(RGB *) malloc(image_modif.largeur*sizeof(RGB));
                    }
                    for(i=0;i<image_modif.hauteur;i++){
                        for(j=0;j<image_modif.largeur;j++){
                            image_modif.pixels[i][j]=image_init.pixels[i][j];
                        }
                    }
                    
                    pixels_ref=(RGB**) malloc(image_modif.hauteur*sizeof(RGB*));
                    for(i=0;i<image_modif.hauteur;i++){
                        pixels_ref[i]=(RGB *) malloc(image_modif.largeur*sizeof(RGB));
                    }
                    for(i=0;i<image_modif.hauteur;i++){
                        for(j=0;j<image_modif.largeur;j++){
                            pixels_ref[i][j]=image_init.pixels[i][j];
                        }
                    }
                    
                    //Fenetre image init
                    p_window_image_init = gtk_window_new (GTK_WINDOW_TOPLEVEL);
                    gtk_window_set_position(GTK_WINDOW(p_window_image_init), GTK_WIN_POS_CENTER);
                    gtk_window_get_position(GTK_WINDOW(p_window_image_init), &x, &y);
                    gtk_window_move(GTK_WINDOW(p_window_image_init), x-200, y-200);
                    gtk_window_set_default_size(GTK_WINDOW(p_window_image_init), image_init.largeur*taille_pixel, image_init.hauteur*taille_pixel);
                    gtk_window_set_title (GTK_WINDOW (p_window_image_init), "Image originale");
                    //zone de dessin
                    p_drawing_area_image_init = gtk_drawing_area_new();
                    g_signal_connect (G_OBJECT (p_drawing_area_image_init), "expose_event", G_CALLBACK(refresh_image_init), NULL);
                    gtk_container_add(GTK_CONTAINER(p_window_image_init),GTK_WIDGET(p_drawing_area_image_init));
                    g_signal_connect (G_OBJECT (p_window_image_init), "destroy", G_CALLBACK (cb_close), user_data);
                    
                    
                    //Fenetre image modif
                    p_window_image_modif = gtk_window_new (GTK_WINDOW_TOPLEVEL);
                    gtk_window_set_position(GTK_WINDOW(p_window_image_modif), GTK_WIN_POS_CENTER);
                    gtk_window_move(GTK_WINDOW(p_window_image_modif), x-200+image_init.largeur*taille_pixel+10, y-200);
                    gtk_window_set_default_size(GTK_WINDOW(p_window_image_modif), image_modif.largeur*taille_pixel, image_modif.hauteur*taille_pixel);
                    gtk_window_set_title (GTK_WINDOW (p_window_image_modif), "Image modifiée");
                    //zone de dessin
                    p_drawing_area_image_modif = gtk_drawing_area_new();
                    g_signal_connect (G_OBJECT (p_drawing_area_image_modif), "expose_event", G_CALLBACK(refresh_image_modif), NULL);
                    gtk_container_add(GTK_CONTAINER(p_window_image_modif),GTK_WIDGET(p_drawing_area_image_modif));
                    g_signal_connect (G_OBJECT (p_window_image_modif), "destroy", G_CALLBACK (cb_close), user_data);
                    
                    
                    gtk_widget_show_all (p_window_image_init);
                    gtk_widget_show_all (p_window_image_modif);
                }
                else{
                    dialog_error(user_data, "Le fichier choisi n'est pas au format PPM :%s\n",path);
                }
            }
            else{
                dialog_error(user_data, "ERROR : regex");
            }
        }
        gtk_widget_destroy (p_dialog);
    }
    else{
        dialog_error(user_data, "Une image est déjà ouverte");
    }
}

void cb_open_test (GtkWidget *p_widget, gpointer user_data){
    if (image_init.pixels==NULL){
        int i,j;
        gint x,y;
        taille_pixel=1;
        
        path=default_path;
        
        image_init.nbMagique=2;
        image_init.largeur=24;
        image_init.hauteur=7;
        image_init.niveau_max=15;
        image_init.pixels=(RGB**) malloc(image_init.hauteur*sizeof(RGB*));
        for(i=0;i<image_init.hauteur;i++){
            image_init.pixels[i]=(RGB *) malloc(image_init.largeur*sizeof(RGB));
        }
        int tmp[7][24] = {
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,3,3,3,3,0,0,7,7,7,7,0,0,11,11,11,11,0,0,15,15,15,15,0},
            {0,3,0,0,0,0,0,7,0,0,0,0,0,11,0,0,0,0,0,15,0,0,15,0},
            {0,3,3,3,0,0,0,7,7,7,0,0,0,11,11,11,0,0,0,15,15,15,15,0},
            {0,3,0,0,0,0,0,7,0,0,0,0,0,11,0,0,0,0,0,15,0,0,0,0},
            {0,3,0,0,0,0,0,7,7,7,7,0,0,11,11,11,11,0,0,15,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
        };
        for(i=0;i<image_init.hauteur;i++){
            for(j=0;j<image_init.largeur;j++){
                image_init.pixels[i][j].r=255*tmp[i][j]/image_init.niveau_max;
                image_init.pixels[i][j].g=255*tmp[i][j]/image_init.niveau_max;
                image_init.pixels[i][j].b=255*tmp[i][j]/image_init.niveau_max;
            }
        }
        image_init.nbMagique=3;
        image_init.niveau_max=255;
        //Duplication de l'image
        image_modif.nbMagique=image_init.nbMagique;
        image_modif.largeur=image_init.largeur;
        image_modif.hauteur=image_init.hauteur;
        image_modif.niveau_max=image_init.niveau_max;
        image_modif.pixels=(RGB**) malloc(image_modif.hauteur*sizeof(RGB*));
        for(i=0;i<image_modif.hauteur;i++){
            image_modif.pixels[i]=(RGB *) malloc(image_modif.largeur*sizeof(RGB));
        }
        for(i=0;i<image_modif.hauteur;i++){
            for(j=0;j<image_modif.largeur;j++){
                image_modif.pixels[i][j]=image_init.pixels[i][j];
            }
        }
        
        pixels_ref=(RGB**) malloc(image_modif.hauteur*sizeof(RGB*));
        for(i=0;i<image_modif.hauteur;i++){
            pixels_ref[i]=(RGB *) malloc(image_modif.largeur*sizeof(RGB));
        }
        for(i=0;i<image_modif.hauteur;i++){
            for(j=0;j<image_modif.largeur;j++){
                pixels_ref[i][j]=image_init.pixels[i][j];
            }
        }
        
        //Fenetre image init
        p_window_image_init = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        gtk_window_set_position(GTK_WINDOW(p_window_image_init), GTK_WIN_POS_CENTER);
        gtk_window_get_position(GTK_WINDOW(p_window_image_init), &x, &y);
        gtk_window_move(GTK_WINDOW(p_window_image_init), x-200, y-200);
        gtk_window_set_default_size(GTK_WINDOW(p_window_image_init), image_init.largeur*taille_pixel, image_init.hauteur*taille_pixel);
        gtk_window_set_title (GTK_WINDOW (p_window_image_init), "Image originale");
        //zone de dessin
        p_drawing_area_image_init = gtk_drawing_area_new();
        g_signal_connect (G_OBJECT (p_drawing_area_image_init), "expose_event", G_CALLBACK(refresh_image_init), NULL);
        gtk_container_add(GTK_CONTAINER(p_window_image_init),GTK_WIDGET(p_drawing_area_image_init));
        g_signal_connect (G_OBJECT (p_window_image_init), "destroy", G_CALLBACK (cb_close), user_data);
        
        
        //Fenetre image modif
        p_window_image_modif = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        gtk_window_set_position(GTK_WINDOW(p_window_image_modif), GTK_WIN_POS_CENTER);
        gtk_window_move(GTK_WINDOW(p_window_image_modif), x-200+image_init.largeur*taille_pixel+10, y-200);
        gtk_window_set_default_size(GTK_WINDOW(p_window_image_modif), image_modif.largeur*taille_pixel, image_modif.hauteur*taille_pixel);
        gtk_window_set_title (GTK_WINDOW (p_window_image_modif), "Image modifiée");
        //zone de dessin
        p_drawing_area_image_modif = gtk_drawing_area_new();
        g_signal_connect (G_OBJECT (p_drawing_area_image_modif), "expose_event", G_CALLBACK(refresh_image_modif), NULL);
        gtk_container_add(GTK_CONTAINER(p_window_image_modif),GTK_WIDGET(p_drawing_area_image_modif));
        g_signal_connect (G_OBJECT (p_window_image_modif), "destroy", G_CALLBACK (cb_close), user_data);
        
        
        gtk_widget_show_all (p_window_image_init);
        gtk_widget_show_all (p_window_image_modif);
    }
    else{
        dialog_error(user_data, "Une image est déjà ouverte");
    }
}

void cb_save (GtkWidget *p_widget, gpointer user_data){
    int i,j;
    if (image_init.pixels!=NULL){
        if(isModified()){
            save(path,image_modif);
            
            for(i=0;i<image_init.hauteur;i++){
                free(image_init.pixels[i]);
            }
            free(image_init.pixels);
            image_init.nbMagique=image_modif.nbMagique;
            image_init.niveau_max=image_modif.niveau_max;
            image_init.hauteur=image_modif.hauteur;
            image_init.largeur=image_modif.largeur;
            
            image_init.pixels=(RGB**) malloc(image_init.hauteur*sizeof(RGB*));
            for(i=0;i<image_init.hauteur;i++){
                image_init.pixels[i]=(RGB *) malloc(image_init.largeur*sizeof(RGB));
            }
            for(i=0;i<image_modif.hauteur;i++){
                for(j=0;j<image_modif.largeur;j++){
                    image_init.pixels[i][j].r=image_modif.pixels[i][j].r;
                    image_init.pixels[i][j].g=image_modif.pixels[i][j].g;
                    image_init.pixels[i][j].b=image_modif.pixels[i][j].b;
                }
            }
            gtk_widget_queue_draw(GTK_WIDGET(p_drawing_area_image_init));
            gtk_window_resize(GTK_WINDOW(p_window_image_init), image_modif.largeur*taille_pixel, image_modif.hauteur*taille_pixel);
            if(GPOINTER_TO_INT(user_data)) dialog_info(user_data, "Image sauvegardé");
        }
        else{
            if(GPOINTER_TO_INT(user_data)) dialog_warning(user_data, "Aucune modification");
        }
    }
    else{
        if(GPOINTER_TO_INT(user_data)) dialog_warning(user_data, "Aucune image ouverte");
    }
}

void cb_saveas (GtkWidget *p_widget, gpointer user_data){
    int i,j;
    if (image_init.pixels!=NULL){
        GtkWidget *p_dialog = NULL;
        p_dialog = gtk_file_chooser_dialog_new ("Sauvegarder le fichier", user_data,
                                                GTK_FILE_CHOOSER_ACTION_SAVE,
                                                GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                                GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
                                                NULL);
        if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT){
            path = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
            gtk_widget_destroy (p_dialog);
            regex_t preg;
            int err;
            const char *str_request = path;
            const char *str_regex = "\\.ppm$";
            err = regcomp (&preg, str_regex, REG_NOSUB | REG_EXTENDED);
            if (err == 0) {
                int match;
                match = regexec (&preg, str_request, 0, NULL, 0);
                regfree (&preg);
                if(match==0){
                    save(path,image_modif);
                    
                    for(i=0;i<image_init.hauteur;i++){
                        free(image_init.pixels[i]);
                    }
                    free(image_init.pixels);
                    image_init.nbMagique=image_modif.nbMagique;
                    image_init.niveau_max=image_modif.niveau_max;
                    image_init.hauteur=image_modif.hauteur;
                    image_init.largeur=image_modif.largeur;
                    
                    image_init.pixels=(RGB**) malloc(image_init.hauteur*sizeof(RGB*));
                    for(i=0;i<image_init.hauteur;i++){
                        image_init.pixels[i]=(RGB *) malloc(image_init.largeur*sizeof(RGB));
                    }
                    for(i=0;i<image_modif.hauteur;i++){
                        for(j=0;j<image_modif.largeur;j++){
                            image_init.pixels[i][j].r=image_modif.pixels[i][j].r;
                            image_init.pixels[i][j].g=image_modif.pixels[i][j].g;
                            image_init.pixels[i][j].b=image_modif.pixels[i][j].b;
                        }
                    }
                    gtk_widget_queue_draw(GTK_WIDGET(p_drawing_area_image_init));
                    gtk_window_resize(GTK_WINDOW(p_window_image_init), image_modif.largeur*taille_pixel, image_modif.hauteur*taille_pixel);
                    if(GPOINTER_TO_INT(user_data)) dialog_info(user_data, "Image sauvegardé");
                }
                else{
                    dialog_error(user_data, "Le fichier choisi n'est pas au format PPM :%s\n",path);
                }
            }
            else{
                dialog_error(user_data, "ERROR : regex");
            }
        }
    }
    else{
        if(GPOINTER_TO_INT(user_data)) dialog_warning(user_data, "Aucune image ouverte");
    }
}

void close_image (GtkWidget *p_widget, gpointer user_data){
    int i;
    if(isModified()){
        GtkWidget *p_dialog = NULL;
        
        p_dialog = gtk_dialog_new_with_buttons ("Sauvegarder",
                                                user_data,
                                                GTK_DIALOG_MODAL,
                                                GTK_STOCK_YES, GTK_RESPONSE_YES,
                                                GTK_STOCK_NO, GTK_RESPONSE_NO,
                                                GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
        
        switch (gtk_dialog_run (GTK_DIALOG (p_dialog)))
        {
            case GTK_RESPONSE_YES:
                cb_save (p_widget, user_data);
                //Desallocation de le memoire
                for(i=0;i<image_init.hauteur;i++){
                    free(image_init.pixels[i]);
                }
                free(image_init.pixels);
                for(i=0;i<image_modif.hauteur;i++){
                    free(image_modif.pixels[i]);
                }
                free(image_modif.pixels);
                for(i=0;i<image_modif.hauteur;i++){
                    free(pixels_ref[i]);
                }
                free(pixels_ref);
                
                image_init.pixels=NULL;
                
                gtk_widget_hide_all (p_window_image_init);
                gtk_widget_hide_all (p_window_image_modif);
                break;
            case GTK_RESPONSE_NO:
                
                //Desallocation de le memoire
                for(i=0;i<image_init.hauteur;i++){
                    free(image_init.pixels[i]);
                }
                free(image_init.pixels);
                for(i=0;i<image_modif.hauteur;i++){
                    free(image_modif.pixels[i]);
                }
                free(image_modif.pixels);
                for(i=0;i<image_modif.hauteur;i++){
                    free(pixels_ref[i]);
                }
                free(pixels_ref);
                
                image_init.pixels=NULL;
                
                gtk_widget_hide_all (p_window_image_init);
                gtk_widget_hide_all (p_window_image_modif);
                break;
            case GTK_RESPONSE_CANCEL:
                gtk_widget_destroy (p_dialog);
                return;
                break;
        }
        gtk_widget_destroy (p_dialog);
    }
    else{
        
        //Desallocation de le memoire
        for(i=0;i<image_init.hauteur;i++){
            free(image_init.pixels[i]);
        }
        free(image_init.pixels);
        for(i=0;i<image_modif.hauteur;i++){
            free(image_modif.pixels[i]);
        }
        free(image_modif.pixels);
        for(i=0;i<image_modif.hauteur;i++){
            free(pixels_ref[i]);
        }
        free(pixels_ref);
        
        image_init.pixels=NULL;
        
        gtk_widget_hide_all (p_window_image_init);
        gtk_widget_hide_all (p_window_image_modif);
    }
    
}

void cb_close (GtkWidget *p_widget, gpointer user_data){
    if (image_init.pixels!=NULL)
    {
        close_image(p_widget,user_data);
    }
    else
    {
        if(GPOINTER_TO_INT(user_data)) dialog_warning(user_data, "Aucune image ouverte");
    }
}

void cb_quit (GtkWidget *p_widget, gpointer user_data){
    close_image(p_widget,user_data);
    gtk_main_quit();
}

void cb_guide (GtkWidget *p_widget, gpointer user_data){
#ifdef MAC
    system("open site/index.html");
#else
    system("firefox site/index.html");
#endif
}

void cb_about (GtkWidget *p_widget, gpointer user_data){
    GtkWidget *p_about;    
    //Creation de la boite de dialogue
    p_about = gtk_message_dialog_new (GTK_WINDOW(user_data),
                                      GTK_DIALOG_MODAL,
                                      GTK_MESSAGE_INFO,
                                      GTK_BUTTONS_OK,
                                      "Projet de C réalisé par\nCharles BESSONNET et Richard GUERCI.\nAnnée 2011/2012");
    
    //Affichage de la boite de dialogue
    gtk_dialog_run(GTK_DIALOG(p_about));
    
    //Destruction de la boite dialogue
    gtk_widget_destroy(p_about);
}


void cb_zoom_in (GtkWidget *p_widget, gpointer user_data){
    if (image_init.pixels!=NULL){
        if(taille_pixel<60){
            taille_pixel++;
            gtk_widget_queue_draw(GTK_WIDGET(p_drawing_area_image_modif));
            gtk_window_resize(GTK_WINDOW(p_window_image_modif), image_modif.largeur*taille_pixel, image_modif.hauteur*taille_pixel);
        }
    }
    else{
        dialog_warning(user_data, "Aucune image ouverte");
    }
}

void cb_zoom_out (GtkWidget *p_widget, gpointer user_data){
    if (image_init.pixels!=NULL){
        if(taille_pixel>1){
            taille_pixel--;
            gtk_widget_queue_draw(GTK_WIDGET(p_drawing_area_image_modif));
            gtk_window_resize(GTK_WINDOW(p_window_image_modif), image_modif.largeur*taille_pixel, image_modif.hauteur*taille_pixel);
        }
    }
    else{
        dialog_warning(user_data, "Aucune image ouverte");
    }
}

void cb_zoom_init (GtkWidget *p_widget, gpointer user_data){
    taille_pixel=1;
    if (image_init.pixels!=NULL){
        gtk_widget_queue_draw(GTK_WIDGET(p_drawing_area_image_modif));
        gtk_window_resize(GTK_WINDOW(p_window_image_modif), image_modif.largeur*taille_pixel, image_modif.hauteur*taille_pixel);
    }
    else{
        dialog_warning(user_data, "Aucune image ouverte");
    }
}

void cb_rouge (GtkWidget *p_widget, gpointer user_data){
    int i,j,value;
    if (image_init.pixels!=NULL){
        for(i=0; i<image_modif.hauteur; i++){
            for(j=0; j<image_modif.largeur; j++){
                value=pixels_ref[i][j].r+(int)gtk_range_get_value(GTK_RANGE(p_widget));
                if(value<0) image_modif.pixels[i][j].r=0;
                else if(value>255) image_modif.pixels[i][j].r=255;
                else image_modif.pixels[i][j].r=value;
            }
        }
        gtk_widget_queue_draw(GTK_WIDGET(p_drawing_area_image_modif));
    }
    else{
        gtk_range_set_value(GTK_RANGE(p_widget), 0);
        dialog_warning(user_data, "Aucune image ouverte");
    }
}

void cb_vert (GtkWidget *p_widget, gpointer user_data){
    int i,j,value;
    if (image_init.pixels!=NULL){
        for(i=0; i<image_modif.hauteur; i++){
            for(j=0; j<image_modif.largeur; j++){
                value=pixels_ref[i][j].g+(int)gtk_range_get_value(GTK_RANGE(p_widget));
                if(value<0) image_modif.pixels[i][j].g=0;
                else if(value>255) image_modif.pixels[i][j].g=255;
                else image_modif.pixels[i][j].g=value;
            }
        }
        gtk_widget_queue_draw(GTK_WIDGET(p_drawing_area_image_modif));
    }
    else{
        gtk_range_set_value(GTK_RANGE(p_widget), 0);
        dialog_warning(user_data, "Aucune image ouverte");
    }
}

void cb_bleu (GtkWidget *p_widget, gpointer user_data){
    int i,j,value;
    if (image_init.pixels!=NULL){
        for(i=0; i<image_modif.hauteur; i++){
            for(j=0; j<image_modif.largeur; j++){
                value=pixels_ref[i][j].b+(int)gtk_range_get_value(GTK_RANGE(p_widget));
                if(value<0) image_modif.pixels[i][j].b=0;
                else if(value>255) image_modif.pixels[i][j].b=255;
                else image_modif.pixels[i][j].b=value;
            }
        }
        gtk_widget_queue_draw(GTK_WIDGET(p_drawing_area_image_modif));
    }
    else{
        gtk_range_set_value(GTK_RANGE(p_widget), 0);
        dialog_warning(user_data, "Aucune image ouverte");
    }
}

void cb_negatif (GtkWidget *p_widget, gpointer user_data){
    int i,j;
    if (image_init.pixels!=NULL){
        for(i=0; i<image_modif.hauteur; i++){
            for(j=0; j<image_modif.largeur; j++){
                image_modif.pixels[i][j].r=255-image_modif.pixels[i][j].r;
                image_modif.pixels[i][j].g=255-image_modif.pixels[i][j].g;
                image_modif.pixels[i][j].b=255-image_modif.pixels[i][j].b;
            }
        }
        gtk_widget_queue_draw(GTK_WIDGET(p_drawing_area_image_modif));
        
    }
    else{
        dialog_warning(user_data, "Aucune image ouverte");
    }
}

void cb_gris (GtkWidget *p_widget, gpointer user_data){
    int i,j,value;
    if (image_init.pixels!=NULL){
        for(i=0; i<image_modif.hauteur; i++){
            for(j=0; j<image_modif.largeur; j++){
                value=(image_modif.pixels[i][j].r+image_modif.pixels[i][j].g+image_modif.pixels[i][j].b)/3;
                image_modif.pixels[i][j].r=value;
                image_modif.pixels[i][j].g=value;
                image_modif.pixels[i][j].b=value;
            }
        }
        gtk_widget_queue_draw(GTK_WIDGET(p_drawing_area_image_modif));
    }
    else{
        dialog_warning(user_data, "Aucune image ouverte");
    }
}

void cb_sepia (GtkWidget *p_widget, gpointer user_data){
    int i,j;
    if (image_init.pixels!=NULL){
        for(i=0; i<image_modif.hauteur; i++){
            for(j=0; j<image_modif.largeur; j++){
                image_modif.pixels[i][j].r = MIN(255, (int)((image_modif.pixels[i][j].r * 0.393) + (image_modif.pixels[i][j].g * 0.769) + (image_modif.pixels[i][j].b * 0.189)));
                image_modif.pixels[i][j].g = MIN(255, (int)((image_modif.pixels[i][j].r * 0.349) + (image_modif.pixels[i][j].g * 0.686) + (image_modif.pixels[i][j].b * 0.168)));
                image_modif.pixels[i][j].b = MIN(255, (int)((image_modif.pixels[i][j].r * 0.272) + (image_modif.pixels[i][j].g * 0.534) + (image_modif.pixels[i][j].b * 0.131)));
            }
        }
        gtk_widget_queue_draw(GTK_WIDGET(p_drawing_area_image_modif));
    }
    else{
        dialog_warning(user_data, "Aucune image ouverte");
    }
}

void cb_flou (GtkWidget *p_widget, gpointer user_data){
    int i,j;
    const int MAX=6,MIN=1;
    srand(time(NULL));
    if (image_init.pixels!=NULL){
        for(i=0; i<image_modif.hauteur; i++){
            for(j=0; j<image_modif.largeur; j++){
                int nbMystere=(rand() %(MAX -MIN +1) )+MIN;
                image_modif.pixels[i][j].r=(image_modif.pixels[i][j].r+nbMystere);
                image_modif.pixels[i][j].g=(image_modif.pixels[i][j].g+nbMystere);
                image_modif.pixels[i][j].b=(image_modif.pixels[i][j].b+nbMystere);
            }
        }
        
        
        gtk_widget_queue_draw(GTK_WIDGET(p_drawing_area_image_modif));
    }
    else{
        dialog_warning(user_data, "Aucune image ouverte");
    }
}


void cb_symetrie_horizontale (GtkWidget *p_widget, gpointer user_data){
    int i,j;
    if (image_init.pixels!=NULL){
        //allocation d'un nouveau tableau
        RGB **pixels;
        pixels=(RGB**) malloc(image_modif.hauteur*sizeof(RGB*));
        for(i=0;i<image_modif.hauteur;i++){
            pixels[i]=(RGB *) malloc(image_modif.largeur*sizeof(RGB));
        }
        
        for(i=0; i<image_modif.hauteur; i++){
            for(j=0; j<image_modif.largeur; j++){
                pixels[i][j]=image_modif.pixels[image_modif.hauteur-i-1][j];
                
                pixels_ref[i][j]=image_modif.pixels[image_modif.hauteur-i-1][j];
            }
        }
        for(i=0;i<image_modif.hauteur;i++){
            free(image_modif.pixels[i]);
        }
        free(image_modif.pixels);
        
        image_modif.pixels=pixels;
        gtk_widget_queue_draw(GTK_WIDGET(p_drawing_area_image_modif));
    }
    else{
        dialog_warning(user_data, "Aucune image ouverte");
    }
}

void cb_symetrie_verticale (GtkWidget *p_widget, gpointer user_data){
    int i,j;
    if (image_init.pixels!=NULL){
        //allocation d'un nouveau tableau
        RGB **pixels;
        pixels=(RGB**) malloc(image_modif.hauteur*sizeof(RGB*));
        for(i=0;i<image_modif.hauteur;i++){
            pixels[i]=(RGB *) malloc(image_modif.largeur*sizeof(RGB));
        }
        
        for(i=0; i<image_modif.hauteur; i++){
            for(j=0; j<image_modif.largeur; j++){
                pixels[i][j]=image_modif.pixels[i][image_modif.largeur-j-1];
                
                pixels_ref[i][j]=image_modif.pixels[i][image_modif.largeur-j-1];
            }
        }
        for(i=0;i<image_modif.hauteur;i++){
            free(image_modif.pixels[i]);
        }
        free(image_modif.pixels);
        
        image_modif.pixels=pixels;
        gtk_widget_queue_draw(GTK_WIDGET(p_drawing_area_image_modif));
    }
    else{
        dialog_warning(user_data, "Aucune image ouverte");
    }
}

void cb_rotation_droite (GtkWidget *p_widget, gpointer user_data){
    int i,j,k;
    if (image_init.pixels!=NULL){
        //allocation d'un nouveau tableau avec la largeur et longueur inversé
        RGB **pixels;
        pixels=(RGB**) malloc(image_modif.largeur*sizeof(RGB*));
        for(i=0;i<image_modif.largeur;i++){
            pixels[i]=(RGB *) malloc(image_modif.hauteur*sizeof(RGB));
        }
        
        //maj ref
        for(i=0;i<image_modif.hauteur;i++){
            free(pixels_ref[i]);
        }
        free(pixels_ref);
        pixels_ref=(RGB**) malloc(image_modif.largeur*sizeof(RGB*));
        for(i=0;i<image_modif.largeur;i++){
            pixels_ref[i]=(RGB *) malloc(image_modif.hauteur*sizeof(RGB));
        }
        
        for(i=0; i<image_modif.hauteur; i++){
            for(j=0; j<image_modif.largeur; j++){
                pixels[j][i]=image_modif.pixels[image_modif.hauteur-i-1][j];
                
                pixels_ref[j][i]=image_modif.pixels[image_modif.hauteur-i-1][j];
            }
        }
        for(i=0;i<image_modif.hauteur;i++){
            free(image_modif.pixels[i]);
        }
        free(image_modif.pixels);
        
        image_modif.pixels=pixels;
        
        //swap
        k=image_modif.largeur;
        image_modif.largeur=image_modif.hauteur;
        image_modif.hauteur=k;
        gtk_widget_queue_draw(GTK_WIDGET(p_drawing_area_image_modif));
        gtk_window_resize(GTK_WINDOW(p_window_image_modif), image_modif.largeur*taille_pixel, image_modif.hauteur*taille_pixel);
    }
    else{
        dialog_warning(user_data, "Aucune image ouverte");
    }
}

void cb_rotation_gauche (GtkWidget *p_widget, gpointer user_data){
    int i,j,k;
    if (image_init.pixels!=NULL){
        //allocation d'un nouveau tableau avec la largeur et longueur inversé
        RGB **pixels;
        pixels=(RGB**) malloc(image_modif.largeur*sizeof(RGB*));
        for(i=0;i<image_modif.largeur;i++){
            pixels[i]=(RGB *) malloc(image_modif.hauteur*sizeof(RGB));
        }
        
        //maj ref
        for(i=0;i<image_modif.hauteur;i++){
            free(pixels_ref[i]);
        }
        free(pixels_ref);
        pixels_ref=(RGB**) malloc(image_modif.largeur*sizeof(RGB*));
        for(i=0;i<image_modif.largeur;i++){
            pixels_ref[i]=(RGB *) malloc(image_modif.hauteur*sizeof(RGB));
        }
        
        for(i=0; i<image_modif.hauteur; i++){
            for(j=0; j<image_modif.largeur; j++){
                pixels[j][i]=image_modif.pixels[i][image_modif.largeur-j-1];
                
                pixels_ref[j][i]=image_modif.pixels[i][image_modif.largeur-j-1];
            }
        }
        for(i=0;i<image_modif.hauteur;i++){
            free(image_modif.pixels[i]);
        }
        free(image_modif.pixels);
        
        image_modif.pixels=pixels;
        
        //swap
        k=image_modif.largeur;
        image_modif.largeur=image_modif.hauteur;
        image_modif.hauteur=k;
        gtk_widget_queue_draw(GTK_WIDGET(p_drawing_area_image_modif));
        gtk_window_resize(GTK_WINDOW(p_window_image_modif), image_modif.largeur*taille_pixel, image_modif.hauteur*taille_pixel);
    }
    else{
        dialog_warning(user_data, "Aucune image ouverte");
    }
}

void cb_annuler (GtkWidget *p_widget, gpointer user_data){
    int i,j;
    if (image_init.pixels!=NULL){
        //allocation d'un nouveau tableau
        RGB **pixels;
        pixels=(RGB**) malloc(image_init.hauteur*sizeof(RGB*));
        for(i=0;i<image_init.hauteur;i++){
            pixels[i]=(RGB *) malloc(image_init.largeur*sizeof(RGB));
        }
        
        for(i=0; i<image_init.hauteur; i++){
            for(j=0; j<image_init.largeur; j++){
                pixels[i][j].r=image_init.pixels[i][j].r;
                pixels[i][j].g=image_init.pixels[i][j].g;
                pixels[i][j].b=image_init.pixels[i][j].b;
            }
        }
        for(i=0;i<image_modif.hauteur;i++){
            free(image_modif.pixels[i]);
        }
        free(image_modif.pixels);
        
        image_modif.pixels=pixels;
        image_modif.largeur=image_init.largeur;
        image_modif.hauteur=image_init.hauteur;
        image_modif.nbMagique=image_init.nbMagique;
        image_modif.niveau_max=image_init.niveau_max;
        gtk_widget_queue_draw(GTK_WIDGET(p_drawing_area_image_modif));
        gtk_window_resize(GTK_WINDOW(p_window_image_modif), image_modif.largeur*taille_pixel, image_modif.hauteur*taille_pixel);
    }
    else{
        dialog_warning(user_data, "Aucune image ouverte");
    }
}

void cb_taille_plus (GtkWidget *p_widget, gpointer user_data){
    int i,j;
    if (image_init.pixels!=NULL){
        //allocation d'un nouveau tableau 2 fois plus grand
        RGB **pixels;
        pixels=(RGB**) malloc(image_modif.hauteur*2*sizeof(RGB*));
        for(i=0;i<image_modif.hauteur*2;i++){
            pixels[i]=(RGB *) malloc(image_modif.largeur*2*sizeof(RGB));
        }
        
        //maj ref
        for(i=0;i<image_modif.hauteur;i++){
            free(pixels_ref[i]);
        }
        free(pixels_ref);
        pixels_ref=(RGB**) malloc(image_modif.hauteur*2*sizeof(RGB*));
        for(i=0;i<image_modif.hauteur*2;i++){
            pixels_ref[i]=(RGB *) malloc(image_modif.largeur*2*sizeof(RGB));
        }
        
        for(i=0; i<image_modif.hauteur; i++){
            for(j=0; j<image_modif.largeur; j++){
                pixels[(i*2)][(j*2)]=image_modif.pixels[i][j];
                pixels[(i*2)+1][(j*2)]=image_modif.pixels[i][j];
                pixels[(i*2)][(j*2)+1]=image_modif.pixels[i][j];
                pixels[(i*2)+1][(j*2)+1]=image_modif.pixels[i][j];
                
                pixels_ref[(i*2)][(j*2)]=image_modif.pixels[i][j];
                pixels_ref[(i*2)+1][(j*2)]=image_modif.pixels[i][j];
                pixels_ref[(i*2)][(j*2)+1]=image_modif.pixels[i][j];
                pixels_ref[(i*2)+1][(j*2)+1]=image_modif.pixels[i][j];
            }
        }
        for(i=0;i<image_modif.hauteur;i++){
            free(image_modif.pixels[i]);
        }
        free(image_modif.pixels);
        
        image_modif.pixels=pixels;
        image_modif.hauteur*=2;
        image_modif.largeur*=2;
        gtk_widget_queue_draw(GTK_WIDGET(p_drawing_area_image_modif));
        gtk_window_resize(GTK_WINDOW(p_window_image_modif), image_modif.largeur*taille_pixel, image_modif.hauteur*taille_pixel);
    }
    else{
        dialog_warning(user_data, "Aucune image ouverte");
    }
}

void cb_taille_moins (GtkWidget *p_widget, gpointer user_data){
    int i,j;
    if (image_init.pixels!=NULL){
        
        if(image_modif.largeur>2&&image_modif.hauteur>2){
            //allocation d'un nouveau tableau 2 fois moins grand
            RGB **pixels;
            pixels=(RGB**) malloc(((int)(imp(image_modif.hauteur)/2))*sizeof(RGB*));
            for(i=0;i<(imp(image_modif.hauteur)/2);i++){
                pixels[i]=(RGB *) malloc(((int)(imp(image_modif.largeur)/2))*sizeof(RGB));
            }
            
            //maj ref
            for(i=0;i<image_modif.hauteur;i++){
                free(pixels_ref[i]);
            }
            free(pixels_ref);
            pixels_ref=(RGB**)  malloc(((int)(imp(image_modif.hauteur)/2))*sizeof(RGB*));
            for(i=0;i<image_modif.hauteur*2;i++){
                pixels_ref[i]=(RGB *) malloc(((int)(imp(image_modif.largeur)/2))*sizeof(RGB));
            }
            
            for(i=0; i<(imp(image_modif.hauteur)/2); i++){
                for(j=0; j<(imp(image_modif.largeur)/2); j++){
                    pixels[i][j].r=(image_modif.pixels[(i*2)][(j*2)].r+image_modif.pixels[(i*2)+1][(j*2)].r+image_modif.pixels[(i*2)][(j*2)+1].r+image_modif.pixels[(i*2)+1][(j*2)+1].r)/4;
                    pixels[i][j].g=(image_modif.pixels[(i*2)][(j*2)].g+image_modif.pixels[(i*2)+1][(j*2)].g+image_modif.pixels[(i*2)][(j*2)+1].g+image_modif.pixels[(i*2)+1][(j*2)+1].g)/4;
                    pixels[i][j].b=(image_modif.pixels[(i*2)][(j*2)].b+image_modif.pixels[(i*2)+1][(j*2)].b+image_modif.pixels[(i*2)][(j*2)+1].b+image_modif.pixels[(i*2)+1][(j*2)+1].b)/4;
                    
                    pixels_ref[i][j].r=(image_modif.pixels[(i*2)][(j*2)].r+image_modif.pixels[(i*2)+1][(j*2)].r+image_modif.pixels[(i*2)][(j*2)+1].r+image_modif.pixels[(i*2)+1][(j*2)+1].r)/4;
                    pixels_ref[i][j].g=(image_modif.pixels[(i*2)][(j*2)].g+image_modif.pixels[(i*2)+1][(j*2)].g+image_modif.pixels[(i*2)][(j*2)+1].g+image_modif.pixels[(i*2)+1][(j*2)+1].g)/4;
                    pixels_ref[i][j].b=(image_modif.pixels[(i*2)][(j*2)].b+image_modif.pixels[(i*2)+1][(j*2)].b+image_modif.pixels[(i*2)][(j*2)+1].b+image_modif.pixels[(i*2)+1][(j*2)+1].b)/4;
                }
            }
            for(i=0;i<image_modif.hauteur;i++){
                free(image_modif.pixels[i]);
            }
            free(image_modif.pixels);
            
            image_modif.pixels=pixels;
            image_modif.hauteur=(int)(imp(image_modif.hauteur)/2);
            image_modif.largeur=(int)(imp(image_modif.largeur)/2);
            gtk_widget_queue_draw(GTK_WIDGET(p_drawing_area_image_modif));
            gtk_window_resize(GTK_WINDOW(p_window_image_modif), image_modif.largeur*taille_pixel, image_modif.hauteur*taille_pixel);
        }
        else{
            dialog_error(p_window_image_modif, "Impossible de réduire l'image");
        }
    }
    else{
        dialog_warning(user_data, "Aucune image ouverte");
    }
}


