//
//  structures.h
//  projet_c
//
//  Created by Richard Guerci on 21/03/12.
//  Copyright © 2012 Charles Bessonnet & Richard Guerci. All rights reserved.
//

#ifndef projet_c_structures_h
#define projet_c_structures_h

#include <gtk/gtk.h>

//#define MAC


typedef struct RGB RGB;
struct RGB{
    int r,g,b;
};

typedef struct PPM PPM;
struct PPM{
	int nbMagique;
	int largeur;
	int hauteur;
	int niveau_max;
	RGB **pixels;
};




int taille_pixel;
PPM image_init,image_modif;


GtkWidget *p_window_image_init;
GtkWidget *p_drawing_area_image_init;
GtkWidget *p_window_image_modif;
GtkWidget *p_drawing_area_image_modif;
GdkPixmap *pixmap;
GdkGC *gc;


#endif
