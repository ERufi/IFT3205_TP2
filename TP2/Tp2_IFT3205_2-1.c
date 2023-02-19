/*------------------------------------------------------*/
/* Prog    : Tp2_IFT3205-2-1.c                          */
/* Auteur  : Émilie Rufiange 208376                     */
/* Date    : --/--/2010                                 */
/* version :                                            */ 
/* langage : C                                          */
/* labo    : DIRO                                       */
/*------------------------------------------------------*/

/*------------------------------------------------*/
/* FICHIERS INCLUS -------------------------------*/
/*------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "FonctionDemo2.h"

/*------------------------------------------------*/
/* DEFINITIONS -----------------------------------*/   
/*------------------------------------------------*/
#define NAME_VISUALISER "display "
#define NAME_IMG_IN1  "UdM_1"
#define NAME_IMG_IN2  "UdM_2"
#define NAME_IMG_OUT1 "image-TpIFT3205-2-1a"
#define NAME_IMG_OUT2 "image-TpIFT3205-2-1b"

/*------------------------------------------------*/
/* PROTOTYPE DE FONCTIONS  -----------------------*/   
/*------------------------------------------------*/

/*------------------------------------------------*/
/* PROGRAMME PRINCIPAL   -------------------------*/                     
/*------------------------------------------------*/
int main(int argc,char **argv)
 {
  int i,j,k;
  int length,width;
  float Theta0;
  int x0,y0;
  char BufSystVisuImg[100];

  //Constante
  length=512;
  width=512;
  
  //Allocation Memoire 
  float** MatriceImgI1=fmatrix_allocate_2d(length,width); //UdM_1-Imaginaire
  float** MatriceImgM1=fmatrix_allocate_2d(length,width); //UdM_1-Module
  float** MatriceImgR1=fmatrix_allocate_2d(length,width); //UdM_1-Réel
  float** MatriceImgI2=fmatrix_allocate_2d(length,width); //UdM_2-Imaginaire
  float** MatriceImgM2=fmatrix_allocate_2d(length,width); //UdM_2-Module
  float** MatriceImgR2=fmatrix_allocate_2d(length,width); //UdM_2-Réel
  float** MatriceImgI3=fmatrix_allocate_2d(length,width);
  float** MatriceImgM3=fmatrix_allocate_2d(length,width);
  float** MatriceImgR3=fmatrix_allocate_2d(length,width);
  float** MatriceImg3=fmatrix_allocate_2d(length,width);

  //Lecture Images
  MatriceImgR1=LoadImagePgm(NAME_IMG_IN1,&length,&width);
  MatriceImgR2=LoadImagePgm(NAME_IMG_IN2,&length,&width);
  

  /*Initialisation à zéros les matrices*/
  for(i=0;i<length;i++) {
    for(j=0;j<width;j++) {
         
         //Image #1
         MatriceImgI1[i][j]=0.0;
         MatriceImgM1[i][j]=0.0;
         
         //Image #2
         MatriceImgI2[i][j]=0.0;
         MatriceImgM2[i][j]=0.0;

      }
  }

  /*FFT Image 1 UdM_1*/
  FFTDD(MatriceImgR1,MatriceImgI1,length,width);

  /*FFT Image 2 UdM_2*/
  FFTDD(MatriceImgR2,MatriceImgI2,length,width);

  /*Module Image 1 UdM_1*/
  Mod(MatriceImgM1,MatriceImgR1,MatriceImgI1,length,width);

  /*Module Image 2 UdM_2*/
  Mod(MatriceImgM2,MatriceImgR2,MatriceImgI2,length,width);

  /*Pour visu Image 1 UdM_1*/
  Loga(MatriceImgM1,100.0,length,width); 
  Recal(MatriceImgM1,length,width);
  //Mult(MatriceImgM2,100.0,length,width);

  /*Pour visu Image 2 UdM_2*/
  Loga(MatriceImgM2,100.0,length,width);
  Recal(MatriceImgM2,length,width);
  //Mult(MatriceImgM2,100.0,length,width);	

  /*Centrer Image 1 UdM_1*/
  CenterImg(MatriceImgM1,length,width);

  /*Centrer Image 2 UdM_2*/
  CenterImg(MatriceImgM2,length,width);

  // .... .... .... .... .... .... ....
  
  //Sauvegarde images
  SaveImagePgm(NAME_IMG_OUT1,MatriceImgM1,length,width);
  SaveImagePgm(NAME_IMG_OUT2,MatriceImgM2,length,width);
  

  //Commande systeme: VISU
  strcpy(BufSystVisuImg,NAME_VISUALISER);
  strcat(BufSystVisuImg,NAME_IMG_OUT1);
  strcat(BufSystVisuImg,".pgm&");
  printf(" %s",BufSystVisuImg);
  system(BufSystVisuImg);
  strcpy(BufSystVisuImg,NAME_VISUALISER);
  strcat(BufSystVisuImg,NAME_IMG_OUT2);
  strcat(BufSystVisuImg,".pgm&");
  printf(" %s",BufSystVisuImg);
  system(BufSystVisuImg);


  //==End=========================================================

  //Liberation memoire 
  free_fmatrix_2d(MatriceImgR1);
  free_fmatrix_2d(MatriceImgI1);
  free_fmatrix_2d(MatriceImgM1);
  free_fmatrix_2d(MatriceImgR2);
  free_fmatrix_2d(MatriceImgI2);
  free_fmatrix_2d(MatriceImgM2);
  free_fmatrix_2d(MatriceImgR3);
  free_fmatrix_2d(MatriceImgI3);
  free_fmatrix_2d(MatriceImgM3);
  //free_fmatrix_2d(MatriceImg1);
  //free_fmatrix_2d(MatriceImg2);  
  //free_fmatrix_2d(MatriceImg3);

  //retour sans probleme
  printf("\n C'est fini ... \n\n");
  return 0; 	 
}


