//
//  error.c
//  projet_c
//
//  Created by Richard Guerci on 21/03/12.
//  Copyright © 2012 Charles Bessonnet & Richard Guerci. All rights reserved.
//

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void dialog_warning (gpointer user_data, char *format, ...){
    GtkWidget *p_warning;    
    //Creation de la boite de dialogue
    p_warning = gtk_message_dialog_new (GTK_WINDOW(user_data),
                                      GTK_DIALOG_MODAL,
                                      GTK_MESSAGE_WARNING,
                                      GTK_BUTTONS_OK,
                                      "%s",format);
    
    //Affichage de la boite de dialogue
    gtk_dialog_run(GTK_DIALOG(p_warning));
    
    //Destruction de la boite dialogue
    gtk_widget_destroy(p_warning);
}

void dialog_error (gpointer user_data, char *format, ...){
    GtkWidget *p_error;    
    //Creation de la boite de dialogue
    p_error = gtk_message_dialog_new (GTK_WINDOW(user_data),
                                      GTK_DIALOG_MODAL,
                                      GTK_MESSAGE_ERROR,
                                      GTK_BUTTONS_OK,
                                      "%s",format);
    
    //Affichage de la boite de dialogue
    gtk_dialog_run(GTK_DIALOG(p_error));
    
    //Destruction de la boite dialogue
    gtk_widget_destroy(p_error);
}

void dialog_info (gpointer user_data, char *format, ...){
    GtkWidget *p_error;    
    //Creation de la boite de dialogue
    p_error = gtk_message_dialog_new (GTK_WINDOW(user_data),
                                      GTK_DIALOG_MODAL,
                                      GTK_MESSAGE_INFO,
                                      GTK_BUTTONS_OK,
                                      "%s",format);
    
    //Affichage de la boite de dialogue
    gtk_dialog_run(GTK_DIALOG(p_error));
    
    //Destruction de la boite dialogue
    gtk_widget_destroy(p_error);
}
