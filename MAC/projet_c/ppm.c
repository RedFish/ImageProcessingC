//
//  ppm.c
//  projet_c
//
//  Created by Charles BESSONNET on 20/04/12.
//  Copyright © 2012 Charles Bessonnet & Richard Guerci. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "ppm.h"
#include "error.h"

void lecturePPM(char *path){
    PPM *pointeurSurImage=NULL;
    PPM image;
    pointeurSurImage=&image;
    int caractere=0;
    FILE *f=NULL;
    RGB **matrice=NULL;
    int ligne =0,collonne=0;
    int *lig=&ligne,*col=&collonne;
    f=fopen(path,"r+");
    
    if (f !=NULL) {
        caractere=fgetc(f);
        if (!caractere=='P') {
            dialog_error(NULL, "Le fichier n'est pas valide");
            return ;
        }
        caractere=fgetc(f);
        image.nbMagique=caractere-48;//-48 car le code ascii de 0 est 48
        //avant pour sortir du 2
        caractere=fgetc(f);
        //tant que ce n'est pas un chiffre avance
        while (!(caractere>47 && caractere<58)) {
            caractere=fgetc(f);
        }
        int longeur=0;
        while (caractere>47 && caractere<58) {
            longeur=longeur*10+caractere-48;
            caractere=fgetc(f);
        }
        image.largeur=longeur;
        int largeur=0;
        caractere=fgetc(f);
        
        while (caractere>47 && caractere<58) {
            largeur=largeur*10+caractere-48;
            caractere=fgetc(f);
        }
        
        image.hauteur=largeur;
        int niveau_max=0;
        caractere=fgetc(f);
        while (!(caractere>47 && caractere<58)) {
            caractere=fgetc(f);
        }
        
        
        
        
        //matrice de 0 à la bonne taille
        matrice=matriceZERO(image.hauteur, image.largeur);
        int nombre=0;
        //tabrgb contientra les 3 valeurs RGB à mettre dans la matrice
        int tabrgb[3];
        
        if (image.nbMagique==1) {
            while (!feof(f)) {
                nombre=0;
                while (caractere>47 && caractere<58) {//tant que c'est un chiffre
                    nombre=nombre*10+caractere-48;
                    caractere=fgetc(f);
                }                
                while ((caractere<=47 || caractere>=58) && !feof(f)) {//tant que ce n'est pas un chiffre
                    caractere=fgetc(f);
                }
                
                if(nombre==0){
                    nombre=255;
                }
                else{
                    nombre=0;
                }
                addMATRICE(matrice, nombre, lig, col, image.hauteur, image.largeur);
                image.niveau_max=255;
            }         
        }
        else{
            while (caractere>47 && caractere<58) {
                niveau_max=niveau_max*10+caractere-48;
                caractere=fgetc(f);
            }
            image.niveau_max=niveau_max;
            
            while (!(caractere>47 && caractere<58)) {
                caractere=fgetc(f);
            }
        }
        
        if (image.nbMagique==2) {
            while (!feof(f)) {
                nombre=0;
                while (caractere>47 && caractere<58) {//tant que c'est un chiffre
                    nombre=nombre*10+caractere-48;
                    caractere=fgetc(f);
                }
                
                while ((caractere<=47 || caractere>=58) && !feof(f)) {//tant que ce n'est pas un chiffre
                    caractere=fgetc(f);
                }
                
                
                addMATRICE(matrice, (nombre*255)/image.niveau_max, lig, col, image.hauteur, image.largeur);
            }         
        }
        else if (image.nbMagique==3) {
            tabrgb[0]=-1;
            tabrgb[1]=-1;
            tabrgb[2]=-1;
            int ajoute=0;
            while (!feof(f)) {
                
                while (caractere>47 && caractere<58 && ajoute==0) {//tant que c'est un chiffre
                    nombre=nombre*10+caractere-48;
                    caractere=fgetc(f);
                    ajoute=0;
                }
                
                
                
                if(ajoute==0) {
                    if(tabrgb[0]==-1) {
                        tabrgb[0]=(int)(nombre*255/image.niveau_max);
                    }
                    else if(tabrgb[1]==-1) {
                        tabrgb[1]=(int)(nombre*255/image.niveau_max);
                    }
                    else if(tabrgb[2]==-1) {
                        tabrgb[2]=(int)(nombre*255/image.niveau_max);
                        ajoute=2;
                    }
                }
                nombre=0;
                
                while ((caractere<=47 || caractere>=58) && !feof(f)) {//tant que ce n'est pas un chiffre
                    caractere=fgetc(f);
                }
                
                
                if(tabrgb[0]!=-1&&tabrgb[1]!=-1&&tabrgb[2]!=-1&&ajoute==2){
                    add3Matrice(matrice, tabrgb, lig, col, image.hauteur, image.largeur);
                    tabrgb[0]=-1;
                    tabrgb[1]=-1;
                    tabrgb[2]=-1;
                    ajoute=0;
                }
            }         
        }
        else if (image.nbMagique==6) {
            tabrgb[0]=-1;
            tabrgb[1]=-1;
            tabrgb[2]=-1;
            
            nombre=0;
            while (!feof(f)) {
                if(tabrgb[0]!=-1&&tabrgb[1]!=-1&&tabrgb[2]!=-1){
                    add3Matrice(matrice, tabrgb, lig, col, image.hauteur, image.largeur);
                    tabrgb[0]=-1;
                    tabrgb[1]=-1;
                    tabrgb[2]=-1;
                }
                tabrgb[(nombre)%3]=(int)(caractere*255/image.niveau_max);
                nombre++;
                caractere=fgetc(f);
            }         
        }
        else {
            if(image.nbMagique!=1)
            dialog_error(NULL, "Format ppm non reconnu");
        }
    }
    
    image.pixels=matrice;
    
    int i,j;    
    image_init.nbMagique=3;
    image_init.largeur=pointeurSurImage->largeur;
    image_init.hauteur=pointeurSurImage->hauteur;
    image_init.niveau_max=255;
    image_init.pixels=(RGB**) malloc(image_init.hauteur*sizeof(RGB*));
    for(i=0;i<image_init.hauteur;i++){
        image_init.pixels[i]=(RGB *) malloc(image_init.largeur*sizeof(RGB));
    }
    for(i=0;i<image_init.hauteur;i++){
        for(j=0;j<image_init.largeur;j++){
            image_init.pixels[i][j].r=image.pixels[i][j].r;
            image_init.pixels[i][j].g=image.pixels[i][j].g;
            image_init.pixels[i][j].b=image.pixels[i][j].b;
        }
    }
}
//permet d'ajouter un pixel gris à l'image
void addMATRICE(RGB **matrice,int chiffreAAjoute,int *lig,int *col,int ligneMax,int colloneMax){
    //image noir et blanc
    if(*col>=colloneMax){
        *col=0;
        *lig=*lig+1;
    }
    if (*lig>=ligneMax) {
        //printf("erreur dimension le fichier n'est pas au format annoncé");
    }
    else{
        matrice[*lig][*col].r=chiffreAAjoute;
        matrice[*lig][*col].g=chiffreAAjoute;
        matrice[*lig][*col].b=chiffreAAjoute;
    }
    
    *col=*col+1;
}
//permet d'ajouter un pixel de couleur à l'image
void add3Matrice(RGB **matrice,int * tab,int *lig,int *col,int ligneMax,int colloneMax){
    if(*col>=colloneMax){
        *col=0;
        *lig=*lig+1;
    }
    if (*lig>=ligneMax) {
        //printf("erreur dimension le fichier n'est pas au format annoncé");
    }
    else{
        matrice[*lig][*col].r=*tab;
        matrice[*lig][*col].g=*(tab+1);
        matrice[*lig][*col].b=*(tab+2);
    }
    
    *col=*col+1;
}

RGB **matriceZERO(int nbLigne,int nbCollone){
    RGB **matrice=NULL;
    int  erreur=0;
    int i,j,l;
    matrice=(RGB **) malloc(sizeof(RGB*)*nbLigne);
    if(matrice!=NULL){
        i=0;
        while ((i<nbLigne)&& !erreur) {
            matrice[i]=(RGB *) malloc(sizeof(RGB)*nbCollone);
            if(matrice[i]==NULL)
                erreur=1;
            else
                i++;
        }
        if(erreur){
            dialog_error(NULL, "Erreur allocation memoire!");
            while(i){
                i--;
                free(matrice[i]);
            }
            free(matrice);
        }
        //met à zero toutes les valeurs
        for (l=0; l<nbLigne; l++) {
            for (j=0; j<nbCollone;j++) {
                matrice[l][j].r=0;
                matrice[l][j].g=0;
                matrice[l][j].b=0;
            }
        }
        
    }
    return matrice;
}

int isModified(){
    int i,j;
    
    if(image_init.nbMagique!=image_modif.nbMagique) return 1;
    if(image_init.niveau_max!=image_modif.niveau_max) return 1;
    if(image_init.hauteur!=image_modif.hauteur) return 1;
    if(image_init.largeur!=image_modif.largeur) return 1;
    
    for(i=0;i<image_modif.hauteur;i++){
        for(j=0;j<image_modif.largeur;j++){
            if(image_modif.pixels[i][j].r!=image_init.pixels[i][j].r) return 1;
            if(image_modif.pixels[i][j].g!=image_init.pixels[i][j].g) return 1;
            if(image_modif.pixels[i][j].b!=image_init.pixels[i][j].b) return 1;
        }
    }
    
    return 0;
}



