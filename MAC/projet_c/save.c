//
//  save.c
//  projet_c
//
//  Created by Charles BESSONNET on 28/04/12.
//  Copyright © 2012 Charles Bessonnet & Richard Guerci. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "save.h"
#include <math.h>

//methode qui permet de sauver un fichier à l'endroit indiquer

void save(char * path,PPM  image){
    FILE* fichier = NULL;
    
    fichier = fopen(path, "w");
    
    if (fichier != NULL){
        /*
         p3 -> 3
         3 chiffre speciaux 10 
         le tableau ligne*collone*(max taille chiffre+1)
         dernier fois 3 pour les couleur r g b
         */
        int pos=0;//variable qi indique la position dans le mot
        int posi;
        int tailleMot =3+5*3+(image.hauteur*image.largeur *5)*3;
        char mot[tailleMot];
        
        
        /***************************
         * mot vide                *
         ***************************/
        
        //printf("*%s*\n",mot);
        
        mot[pos]='P';
        pos++;
        fputc('P', fichier);
        //+48 pour etre en code ascii
        mot[pos]=image.nbMagique+48;
        fputc(mot[pos], fichier);
        pos++;
        mot[pos]='\n';
        fputc(mot[pos], fichier);
        pos++;
        int nombreLargeur=image.largeur,copieNL=nombreLargeur;
        int taille=1;
        
        /**************************************
         * mot P +chiffre + saut ligne        *
         **************************************/
        
        //printf("mot jusu'à chiffre magique :\n%s\n",mot);
        
        while (copieNL>9.999999) {
            copieNL=copieNL/10;
            taille++;
        }
        //printf("la largeur est :%d et la taille est %d\n",nombreLargeur,taille);
        int i=0;
        for (posi=pos; posi<pos+taille; posi++) {
            /*remplie grace au chiffre
             *ex :234
             * 234 -> taille 3
             *
             */
            i++;
            
            int exposant=pow(10, taille-i);
            int res=nombreLargeur/exposant +48;
            mot[posi]=res;
            fputc(mot[posi], fichier);
            nombreLargeur=nombreLargeur-(res-48)*exposant;
            //printf("place vaut %d\n",exposant);
            //printf("l'entier que l'on va ajouté est %d et corespond à %c\n",res,res);
            //printf("(largeur save )le caractere ajouté est : %c\n",mot[posi]);
            //printf("%d\n",posi);
            
        }
        pos=pos+taille+1;
        mot[pos]='\n';
        fputc(mot[pos], fichier);
        pos++;
        
        /************************************
         * mot jusqu'à chiffre largeur      *
         ************************************/
        
        //printf("mot + largeur \n%s\n",mot);
        
        //idem hauteur
        int nombreHauteur=image.hauteur,copieNH=nombreHauteur;
        taille=1;
        while (copieNH>9.999999) {
            copieNH=copieNH/10;
            taille++;
        }
        //printf("la hauteur est :%d et la taille est %d\n",nombreHauteur,taille);
        i=0;
        
        for (posi=pos; posi<pos+taille; posi++) {
            i++;
            
            int exposant=pow(10, taille-i);
            int res=nombreHauteur/exposant +48;
            mot[posi]=res;
            fputc(mot[posi], fichier);
            nombreHauteur=nombreHauteur-(res-48)*exposant;   
            //printf("place vaut %d\n",exposant);
            //printf("l'entier que l'on va ajouté est %d et corespond à %c\n",res,res);
            //printf("(largeur save )le caractere ajouté est : %c\n",mot[posi]);
            //printf("%d\n",posi);
            //printf("verifie caractere hauteur : %c\n",mot[posi]);
            
        }
        pos=pos+taille+1;
        mot[pos]='\n';
        fputc(mot[pos], fichier);
        pos++;
        
        //printf("mot jusqu'à hauteur\n%s\n",mot);
        
        //idem couleur_max
        int nombreCouleur=image.niveau_max,copieNC=nombreCouleur;
        taille=1;
        while (copieNC>9.999999) {
            copieNC=copieNC/10;
            taille++;
        }
        //printf("la couleur est :%d et la taille est %d\n",nombreCouleur,taille);
        i=0;
        for (posi=pos; posi<pos+taille; posi++) {
            i++;
            
            int exposant=pow(10, taille-i);
            int res=nombreCouleur/exposant +48;
            mot[posi]=res;
            fputc(mot[posi], fichier);
            nombreCouleur=nombreCouleur-(res-48)*exposant;
            //printf("place vaut %d\n",exposant);
            //printf("l'entier que l'on va ajouté est %d et corespond à %c\n",res,res);
            //printf("(largeur save )le caractere ajouté est : %c\n",mot[posi]);
            //printf("%d\n",posi);
            //printf("verifie caractere couleur : %c\n",mot[posi]);
        }
        pos=pos+taille+1;
        mot[pos]='\n';
        fputc(mot[pos], fichier);
        pos++;
        //printf("mot jusqu'à couleur\n%s\n",mot);
        
        
        /*printf("------verifie mot--------\n");
         for (int q=0; q<tailleMot; q++) {
         printf("%c",mot[q]);
         }
         */
        
        //tableau
        //printf("---avant le tableau----");
        int ligne=0,colone =0;
        for (ligne=0; ligne<image.hauteur; ligne++) {
            //printf("entre premiere boucle");
            for (colone=0; colone<image.largeur; colone++) {
                //ecrire le chiffre et metre ' '
                if (image.nbMagique==2) {
                    int nombre=image.pixels[ligne][colone].r,copie=nombre;
                    int taille=1;
                    while (copie>9.999999) {
                        copie=copie/10;
                        taille++;
                    }
                    int i=0;
                    for (posi=pos; posi<pos+taille; posi++) {
                        i++;
                        int place=pow(10, taille-i);
                        int res=nombre/place+48;
                        mot[posi]=nombre/place+48;
                        nombre=nombre-(res -48)*place;
                        //printf("avant d'ecrire les valeurs du tableau %c\n",mot[posi]);
                        fputc(mot[posi], fichier);
                    }
                    pos=pos+taille+1;
                    mot[pos]=' ';
                    fputc(mot[pos], fichier);
                    pos++;
                }else{
                    //cas couleur r
                    int nombre=image.pixels[ligne][colone].r,copie=nombre;
                    int taille=1;
                    while (copie>9.999999) {
                        copie=copie/10;
                        taille++;
                    }
                    int i=0;
                    for (posi=pos; posi<pos+taille; posi++) {
                        i++;
                        int place=pow(10, taille-i);
                        int res=nombre/place+48;
                        mot[posi]=nombre/place+48;
                        nombre=nombre-(res -48)*place;
                        fputc(mot[posi], fichier);
                        
                    }
                    pos=pos+taille+1;
                    mot[pos]=' ';
                    fputc(mot[pos], fichier);
                    pos++;
                    //cas couleur g
                    nombre=image.pixels[ligne][colone].g;
                    copie=nombre;
                    taille=1;
                    while (copie>9.999999) {
                        copie=copie/10;
                        taille++;
                    }
                    i=0;
                    for (posi=pos; posi<pos+taille; posi++) {
                        i++;
                        int place=pow(10, taille-i);
                        int res=nombre/place+48;
                        mot[posi]=nombre/place+48;
                        nombre=nombre-(res -48)*place;
                        fputc(mot[posi], fichier);
                        
                        
                    }
                    pos=pos+taille+1;
                    mot[pos]=' ';
                    fputc(mot[pos], fichier);
                    pos++;
                    //cas couleur b
                    nombre=image.pixels[ligne][colone].b;
                    copie=nombre;
                    taille=1;
                    while (copie>9.999999) {
                        copie=copie/10;
                        taille++;
                    }
                    i=0;
                    for (posi=pos; posi<pos+taille; posi++) {
                        i++;
                        int place=pow(10, taille-i);
                        int res=nombre/place+48;
                        mot[posi]=nombre/place+48;
                        nombre=nombre-(res -48)*place;
                        fputc(mot[posi], fichier);
                        
                        
                    }
                    pos=pos+taille+1;
                    mot[pos]=' ';
                    fputc(mot[pos], fichier);
                    pos++;
                }
            }
        }
        fclose(fichier);
        
    } 
}

