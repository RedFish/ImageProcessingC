//
//  menu.c
//  projet_c
//
//  Created by Richard Guerci on 21/03/12.
//  Copyright © 2012 Charles Bessonnet & Richard Guerci. All rights reserved.
//

#include <gtk/gtk.h>
#include "callback.h"
#include "menu.h"

static void menu_item_new (GtkMenu *p_menu, const gchar *type,const gchar *title, GCallback callback, gpointer user_data);
static void menu_new_separator (GtkMenu *p_menu);

GtkMenuBar *menu_new (gpointer user_data){
    GtkWidget *p_menu_bar = NULL;
    
    p_menu_bar = gtk_menu_bar_new ();
    
    /* Menu "Fichier" */
    {
        GtkWidget *p_menu_fichier = NULL;
        GtkWidget *p_menu_item_fichier = NULL;
        GtkWidget *p_menu_aide = NULL;
        GtkWidget *p_menu_item_aide = NULL;
        
        p_menu_fichier = gtk_menu_new ();
        p_menu_item_fichier = gtk_menu_item_new_with_mnemonic ("_Fichier");
        menu_item_new (GTK_MENU (p_menu_fichier), GTK_STOCK_OPEN    , "_Ouvrir"             , G_CALLBACK (cb_open)  , user_data);
        menu_item_new (GTK_MENU (p_menu_fichier), GTK_STOCK_DND    , "_Image Test"             , G_CALLBACK (cb_open_test)  , user_data);
        menu_new_separator (GTK_MENU (p_menu_fichier));
        menu_item_new (GTK_MENU (p_menu_fichier), GTK_STOCK_SAVE    ,   "_Enregistrer"      , G_CALLBACK (cb_save)  , user_data);
        menu_item_new (GTK_MENU (p_menu_fichier), GTK_STOCK_FLOPPY  ,"Enregistrer _sous"    , G_CALLBACK (cb_saveas), user_data);
        menu_item_new (GTK_MENU (p_menu_fichier), GTK_STOCK_CLOSE   ,"_Fermer"              , G_CALLBACK (cb_close) , user_data);
        menu_new_separator (GTK_MENU (p_menu_fichier));
        menu_item_new (GTK_MENU (p_menu_fichier), GTK_STOCK_QUIT    ,"_Quitter"             , G_CALLBACK (cb_quit)  , user_data);
        gtk_menu_item_set_submenu (GTK_MENU_ITEM (p_menu_item_fichier), p_menu_fichier);
        
        p_menu_item_aide = gtk_menu_item_new_with_mnemonic ("_Aide");
        p_menu_aide = gtk_menu_new ();
        menu_item_new (GTK_MENU (p_menu_aide), GTK_STOCK_HELP   ,"_Guide"       , G_CALLBACK (cb_guide)   , user_data);
        menu_item_new (GTK_MENU (p_menu_aide), GTK_STOCK_ABOUT  ,"_A propos"    , G_CALLBACK (cb_about)  , user_data);
        gtk_menu_item_set_submenu (GTK_MENU_ITEM (p_menu_item_aide), p_menu_aide);
        
        gtk_menu_shell_append (GTK_MENU_SHELL (p_menu_bar), p_menu_item_fichier);
        gtk_menu_shell_append (GTK_MENU_SHELL (p_menu_bar), p_menu_item_aide);
    }
    return GTK_MENU_BAR (p_menu_bar);
}

static void menu_item_new (GtkMenu *p_menu, const gchar *type,const gchar *title, GCallback callback, gpointer user_data){
    GtkWidget *p_menu_item = gtk_image_menu_item_new_with_mnemonic(title);
    GtkWidget* p_image = gtk_image_new_from_stock(type, GTK_ICON_SIZE_MENU);
    gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(p_menu_item), p_image);
    gtk_menu_shell_append (GTK_MENU_SHELL (p_menu), p_menu_item);
    g_signal_connect (G_OBJECT (p_menu_item), "activate", callback, user_data);
}

static void menu_new_separator (GtkMenu *p_menu){
    GtkWidget *p_menu_separator;
    
    p_menu_separator = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(p_menu),p_menu_separator);
}

