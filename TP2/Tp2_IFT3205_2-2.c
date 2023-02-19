/*------------------------------------------------------*/
/* Prog    : Tp2_IFT3205-2-2.c                          */
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
#define NAME_IMG_IN1  "lena"
#define NAME_IMG_OUT1 "image-TpIFT3205-2-2"

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
  float** MatriceImgI1=fmatrix_allocate_2d(length,width);
  float** MatriceImgM1=fmatrix_allocate_2d(length,width);
  float** MatriceImgR1=fmatrix_allocate_2d(length,width);
  float** MatriceImgI2=fmatrix_allocate_2d(length,width);
  float** MatriceImgM2=fmatrix_allocate_2d(length,width);
  float** MatriceImgR2=fmatrix_allocate_2d(length,width);
  float** MatriceImgI3=fmatrix_allocate_2d(length,width);
  float** MatriceImgM3=fmatrix_allocate_2d(length,width);
  float** MatriceImgR3=fmatrix_allocate_2d(length,width);
  float** MatriceImg3=fmatrix_allocate_2d(length,width);

  //Lecture Image 
  MatriceImgR1=LoadImagePgm(NAME_IMG_IN1,&length,&width);
  //float** MatriceImg2=LoadImagePgm(NAME_IMG_IN2,&length,&width);

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
  
  /*FFT*/
 // FFTDD(MatriceImgR1,MatriceImgI1,length,width);

  

  /*Module*/
 // Mod(MatriceImgM1,MatriceImgR1,MatriceImgI1,length,width);

  /*Pour visu*/
 // Recal(MatriceImgM1,length,width);
 // Mult(MatriceImgM1,100.0,length,width);
  
  	
  /*Center Image real part*/
  //CenterImg(MatriceImgM1,length,width);
   /*Center Image imaginary part*/
  //CenterImg(MatriceImgI1,length,width);
  
   /*rotate image real part*/
  rotate_image(MatriceImgR1, length,width, 22.5);
  /*rotate image imaginary part*/
  //rotate_image(MatriceImgI1, length,width, 22.5);
  
  
 /*Center Image real part*/
  //CenterImg(MatriceImgR1,length,width);
   /*Center Image imaginary part*/
  //CenterImg(MatriceImgI1,length,width);
  
   /*inverse FFT*/
  //IFFTDD(MatriceImgR1,MatriceImgI1,length,width) ; 
  //Recal(MatriceImgR1,length,width);
  // .... .... .... .... .... .... ....


  //Sauvegarde
  SaveImagePgm(NAME_IMG_OUT1,MatriceImgR1,length,width);
  //SaveImagePgm(NAME_IMG_OUT2,MatriceImg2,length,width);

  //Commande systeme: VISU
  strcpy(BufSystVisuImg,NAME_VISUALISER);
  strcat(BufSystVisuImg,NAME_IMG_OUT1);
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
  free_fmatrix_2d(MatriceImg3);

  //retour sans probleme
  printf("\n C'est fini ... \n\n");
  return 0; 	 
}


