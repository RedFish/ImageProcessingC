//
//  ppm.h
//  projet_c
//
//  Created by Charles BESSONNET on 20/04/12.
//  Copyright © 2012 Charles Bessonnet & Richard Guerci. All rights reserved.
//

#ifndef PPM_H
#define PPM_H
#include "structures.h"
#include <gtk/gtk.h>

void lecturePPM(char *path);
RGB **matriceZERO(int nbLigne,int nbCollone);
void add3Matrice(RGB **matrice,int * tab,int *lig,int *col,int ligneMax,int colloneMax);
void addMATRICE(RGB **matrice,int chiffreAAjoute,int *lig,int *col,int ligneMax,int colloneMax);
int isModified(void);

#endif
