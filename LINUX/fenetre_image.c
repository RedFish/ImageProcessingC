//
//  fenetre_image.c
//  projet_c
//
//  Created by Richard Guerci on 21/03/12.
//  Copyright © 2012 Charles Bessonnet & Richard Guerci. All rights reserved.
//

#include <stdio.h>
#include <gtk/gtk.h>
#include "structures.h"
#include "fenetre_image.h"



int  get_color(int r, int g, int b){
    int result;
    result = 0;
    result += r << 16;
    result += g << 8;
    result += b;
    return (result);
}

gboolean refresh_image_init( GtkWidget *widget, GdkEventExpose *event){
    int i,j;
    GdkColor couleur;
    
    if (pixmap != NULL) gdk_pixmap_unref(pixmap);
    pixmap = gdk_pixmap_new(widget->window, taille_pixel, taille_pixel, -1);
    if (gc ==NULL) gc = gdk_gc_new(widget->window);
    
    for(i=0; i<image_init.hauteur; i++){
        for(j=0; j<image_init.largeur; j++){
            couleur.pixel=get_color(image_init.pixels[i][j].r,image_init.pixels[i][j].g,image_init.pixels[i][j].b);
            gdk_gc_set_foreground(gc, &couleur);
            gdk_draw_rectangle(GDK_DRAWABLE(pixmap), gc, TRUE, 0, 0, widget->allocation.width, widget->allocation.height);
            gdk_draw_drawable(widget->window, widget->style->fg_gc[GTK_WIDGET_STATE (widget)], pixmap,
                              event->area.x, event->area.y, j*taille_pixel, i*taille_pixel, event->area.width, event->area.height);
        }
    }
    return TRUE;
}


gboolean refresh_image_modif( GtkWidget *widget, GdkEventExpose *event){
    int i,j;
    GdkColor couleur;
    
    
    if (pixmap != NULL) gdk_pixmap_unref(pixmap);
    pixmap = gdk_pixmap_new(widget->window, taille_pixel, taille_pixel, -1);
    if (gc ==NULL) gc = gdk_gc_new(widget->window);
    
    for(i=0; i<image_modif.hauteur; i++){
        for(j=0; j<image_modif.largeur; j++){
            couleur.pixel=get_color(image_modif.pixels[i][j].r,image_modif.pixels[i][j].g,image_modif.pixels[i][j].b);
            gdk_gc_set_foreground(gc, &couleur);
            gdk_draw_rectangle(GDK_DRAWABLE(pixmap), gc, TRUE, 0, 0, widget->allocation.width, widget->allocation.height);
            gdk_draw_drawable(widget->window, widget->style->fg_gc[GTK_WIDGET_STATE (widget)], pixmap,
                              event->area.x, event->area.y, j*taille_pixel, i*taille_pixel, event->area.width, event->area.height);
        }
    }
    return TRUE;
}

