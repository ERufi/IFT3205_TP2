/*---------------------------------------------------*/
/* module  : FonctionDemo2.c                         */
/* auteur  : Mignotte Max                            */
/* date    : --/--/2010                              */              
/* langage : C                                       */
/* labo    : DIRO                                    */
/*---------------------------------------------------*/

/*------------------------------------------------*/
/* FICHIERS INCLUS -------------------------------*/
/*------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "FonctionDemo2.h"

/*------------------------------------------------*/
/* FONCTIONS -------------------------------------*/
/*------------------------------------------------*/
/*---------------------------------------------------------*/
/*  Alloue de la memoire pour une matrice 1d de float      */
/*---------------------------------------------------------*/
float* fmatrix_allocate_1d(int hsize)
 {
  float* matrix;

  matrix=(float*)malloc(sizeof(float)*hsize); 
  if (matrix==NULL) printf("probleme d'allocation memoire");

  return matrix; 
 }

/*----------------------------------------------------------*/
/*  Alloue de la memoire pour une matrice 2d de float       */
/*----------------------------------------------------------*/
float** fmatrix_allocate_2d(int vsize,int hsize)
 {
  int i;
  float** matrix;
  float *imptr;

  matrix=(float**)malloc(sizeof(float*)*vsize);
  if (matrix==NULL) printf("probleme d'allocation memoire");

  imptr=(float*)malloc(sizeof(float)*hsize*vsize);
  if (imptr==NULL) printf("probleme d'allocation memoire");
 
  for(i=0;i<vsize;i++,imptr+=hsize) matrix[i]=imptr;
  return matrix;
 }

/*----------------------------------------------------------*/
/* Libere la memoire de la matrice 1d de float              */
/*----------------------------------------------------------*/
void free_fmatrix_1d(float* pmat)
 { 
  free(pmat); 
 }

//----------------------------------------------------------*/
/* Libere la memoire de la matrice 2d de float              */
/*----------------------------------------------------------*/
void free_fmatrix_2d(float** pmat)
 { 
  free(pmat[0]);
  free(pmat);
 }

/*----------------------------------------------------------*/
/* Chargement de l'image de nom <name> (en pgm)             */
/*----------------------------------------------------------*/
float** LoadImagePgm(char* name,int *length,int *width)
 {
  int i,j,k;
  unsigned char var;
  char buff[NBCHAR];
  float** mat;

  char stringTmp1[NBCHAR],stringTmp2[NBCHAR],stringTmp3[NBCHAR];
 
  int ta1,ta2,ta3;
  FILE *fic;

  /*-----nom du fichier pgm-----*/
  strcpy(buff,name);
  strcat(buff,".pgm");
  printf("---> Ouverture de %s",buff);

  /*----ouverture du fichier----*/
  fic=fopen(buff,"r");
  if (fic==NULL)
    { printf("\n- Grave erreur a l'ouverture de %s  -\n",buff);
      exit(-1); }

  /*--recuperation de l'entete--*/
  fgets(stringTmp1,100,fic);
  fgets(stringTmp2,100,fic);
  fscanf(fic,"%d %d",&ta1,&ta2);
  fscanf(fic,"%d\n",&ta3);

  /*--affichage de l'entete--*/
  printf("\n\n--Entete--");
  printf("\n----------");
  printf("\n%s%s%d %d \n%d\n",stringTmp1,stringTmp2,ta1,ta2,ta3);

  *length=ta1;
  *width=ta2;
  mat=fmatrix_allocate_2d(*length,*width);
   
  /*--chargement dans la matrice--*/
     for(i=0;i<*length;i++)
      for(j=0;j<*width;j++)  
        { fread(&var,1,1,fic);
          mat[i][j]=var; }

   /*---fermeture du fichier---*/
  fclose(fic);

  return(mat);
 }


/*----------------------------------------------------------*/
/* Sauvegarde de l'image de nom <name> au format pgm        */
/*----------------------------------------------------------*/
void SaveImagePgm(char* name,float** mat,int length,int width)
 {
  int i,j,k;
  char buff[NBCHAR];
  FILE* fic;
  time_t tm;

  /*--extension--*/
  strcpy(buff,name);
  strcat(buff,".pgm");

  /*--ouverture fichier--*/
  fic=fopen(buff,"w");
    if (fic==NULL) 
        { printf(" Probleme dans la sauvegarde de %s",buff); 
          exit(-1); }
  printf("\n Sauvegarde de %s au format pgm\n",name);

  /*--sauvegarde de l'entete--*/
  fprintf(fic,"P5");
  if ((ctime(&tm))==NULL) fprintf(fic,"\n#\n");
  else fprintf(fic,"\n# IMG Module, %s",ctime(&tm));
  fprintf(fic,"%d %d",width,length);
  fprintf(fic,"\n255\n");

  /*--enregistrement--*/
     for(i=0;i<length;i++)
      for(j=0;j<width;j++) 
        fprintf(fic,"%c",(char)mat[i][j]);
   
  /*--fermeture fichier--*/
   fclose(fic); 
 } 

/*--------------*/
/* FOURIER -----*/
/*--------------*/
/*------------------------------------------------*/
/*  FOURN ----------------------------------------*/
/*------------------------------------------------*/
void fourn(float data[], unsigned long nn[], int ndim, int isign)
{
	int idim;
	unsigned long i1,i2,i3,i2rev,i3rev,ip1,ip2,ip3,ifp1,ifp2;
	unsigned long ibit,k1,k2,n,nprev,nrem,ntot;
	float tempi,tempr;
	double theta,wi,wpi,wpr,wr,wtemp;

	for (ntot=1,idim=1;idim<=ndim;idim++)
		ntot *= nn[idim];
	nprev=1;
	for (idim=ndim;idim>=1;idim--) {
		n=nn[idim];
		nrem=ntot/(n*nprev);
		ip1=nprev << 1;
		ip2=ip1*n;
		ip3=ip2*nrem;
		i2rev=1;
		for (i2=1;i2<=ip2;i2+=ip1) {
			if (i2 < i2rev) {
				for (i1=i2;i1<=i2+ip1-2;i1+=2) {
					for (i3=i1;i3<=ip3;i3+=ip2) {
						i3rev=i2rev+i3-i2;
						SWAP(data[i3],data[i3rev]);
						SWAP(data[i3+1],data[i3rev+1]);
					}
				}
			}
			ibit=ip2 >> 1;
			while (ibit >= ip1 && i2rev > ibit) {
				i2rev -= ibit;
				ibit >>= 1;
			}
			i2rev += ibit;
		}
		ifp1=ip1;
		while (ifp1 < ip2) {
			ifp2=ifp1 << 1;
			theta=isign*6.28318530717959/(ifp2/ip1);
			wtemp=sin(0.5*theta);
			wpr = -2.0*wtemp*wtemp;
			wpi=sin(theta);
			wr=1.0;
			wi=0.0;
			for (i3=1;i3<=ifp1;i3+=ip1) {
				for (i1=i3;i1<=i3+ip1-2;i1+=2) {
					for (i2=i1;i2<=ip3;i2+=ifp2) {
						k1=i2;
						k2=k1+ifp1;
						tempr=(float)wr*data[k2]-(float)wi*data[k2+1];
						tempi=(float)wr*data[k2+1]+(float)wi*data[k2];
						data[k2]=data[k1]-tempr;
						data[k2+1]=data[k1+1]-tempi;
						data[k1] += tempr;
						data[k1+1] += tempi;
					}
				}
				wr=(wtemp=wr)*wpr-wi*wpi+wr;
				wi=wi*wpr+wtemp*wpi+wi;
			}
			ifp1=ifp2;
		}
		nprev *= n;
	}
}


/*----------------------------------------------------------*/
/* FFTDD                                                    */
/*----------------------------------------------------------*/
void FFTDD(float** mtxR,float** mtxI,int lgth, int wdth)
{
 int i,j;
 int posx,posy;

 float* data;
 float* ImgFreqR;
 float* ImgFreqI;
 unsigned long* nn;

 /*allocation memoire*/
 data=(float*)malloc(sizeof(float)*(2*wdth*lgth)+1);
 ImgFreqR=(float*)malloc(sizeof(float)*(wdth*lgth));
 ImgFreqI=(float*)malloc(sizeof(float)*(wdth*lgth));
 nn=(unsigned long*)malloc(sizeof(unsigned long)*(FFT2D+1)); 

 /*Remplissage de nn*/
 nn[1]=lgth; nn[2]=wdth;

 /*Remplissage de data*/
 for(i=0;i<lgth;i++) for(j=0;j<wdth;j++) 
   { data[2*(i*lgth+j)+1]=mtxR[i][j];
     data[2*(i*lgth+j)+2]=mtxI[i][j]; }

 /*FFTDD*/
 fourn(data,nn,FFT2D,FFT);

 /*Remplissage*/
 for(i=0;i<(wdth*lgth);i++)
  { ImgFreqR[i]=data[(2*i)+1];
    ImgFreqI[i]=data[(2*i)+2];  }

 /*Conversion en Matrice*/
 for(i=0;i<(wdth*lgth);i++)
  { posy=(int)(i/wdth);
    posx=(int)(i%wdth);

    mtxR[posy][posx]=ImgFreqR[i];
    mtxI[posy][posx]=ImgFreqI[i];}

 /*Liberation memoire*/
 free(data);
 free(ImgFreqR);
 free(ImgFreqI);
 free(nn);
}


/*----------------------------------------------------------*/
/* IFFTDD                                                   */
/*----------------------------------------------------------*/
void IFFTDD(float** mtxR,float**  mtxI,int lgth,int wdth)
{
 int i,j;
 int posx,posy;

 float* data;
 float* ImgFreqR;
 float* ImgFreqI;
 unsigned long* nn;

 /*allocation memoire*/
 data=(float*)malloc(sizeof(float)*(2*wdth*lgth)+1);
 ImgFreqR=(float*)malloc(sizeof(float)*(wdth*lgth));
 ImgFreqI=(float*)malloc(sizeof(float)*(wdth*lgth));
 nn=(unsigned long*)malloc(sizeof(unsigned long)*(FFT2D+1));

 /*Recadrege*/

 /*Remplissage de nn*/
 nn[1]=lgth; nn[2]=wdth;

 /*Remplissage de data*/
 for(i=0;i<lgth;i++) for(j=0;j<wdth;j++) 
   { data[2*(i*lgth+j)+1]=mtxR[i][j];
     data[2*(i*lgth+j)+2]=mtxI[i][j]; }

 /*FFTDD*/
 fourn(data,nn,FFT2D,IFFT);

 /*Remplissage*/
 for(i=0;i<(wdth*lgth);i++)
  { ImgFreqR[i]=data[(2*i)+1];
    ImgFreqI[i]=data[(2*i)+2]; }

 /*Conversion en Matrice*/
 for(i=0;i<(wdth*lgth);i++)
  { posy=(int)(i/wdth);
    posx=(int)(i%wdth);

   mtxR[posy][posx]=ImgFreqR[i]/(wdth*lgth);  
   mtxI[posy][posx]=ImgFreqI[i]/(wdth*lgth); }

 /*Liberation memoire*/
 free(data);
 free(ImgFreqR);
 free(ImgFreqI);
 free(nn);
}

/*----------------------------------------------------------*/
/* Mod2                                                     */
/*----------------------------------------------------------*/
void Mod(float** matM,float** matR,float** matI,int lgth,int wdth)
{
 int i,j;

 /*Calcul du module*/
 for(i=0;i<lgth;i++) for(j=0;j<wdth;j++)
 matM[i][j]=sqrt((matR[i][j]*matR[i][j])+(matI[i][j]*matI[i][j]));
}

/*----------------------------------------------------------*/
/* Mult                                                     */
/*----------------------------------------------------------*/
void Mult(float** mat,float coef,int lgth,int wdth)
{
 int i,j;

 /*multiplication*/
  for(i=0;i<lgth;i++) for(j=0;j<wdth;j++) 
    { mat[i][j]*=coef;
      if (mat[i][j]>GREY_LEVEL) mat[i][j]=GREY_LEVEL; }
}

/*----------------------------------------------------------*/
/* Recal                                                    */
/*----------------------------------------------------------*/
void Recal(float** mat,int lgth,int wdth)
{
 int i,j;
 float max,min;

 /*Initialisation*/
 min=mat[0][0];

 /*Recherche du min*/
  for(i=0;i<lgth;i++) for(j=0;j<wdth;j++)
    if (mat[i][j]<min) min=mat[i][j];

 /*plus min*/
   for(i=0;i<lgth;i++) for(j=0;j<wdth;j++)
    mat[i][j]-=min;

   max=mat[0][0];
 /*Recherche du max*/
  for(i=0;i<lgth;i++) for(j=0;j<wdth;j++) 
    if (mat[i][j]>max) max=mat[i][j];

 /*Recalibre la matrice*/
 for(i=0;i<lgth;i++) for(j=0;j<wdth;j++)
   mat[i][j]*=(GREY_LEVEL/max);      
}

/*----------------------------------------------------------*/
/* Mult 2 matrices complexes                                */
/*----------------------------------------------------------*/
void MultMatrix(float** matRout,float** matIout,float** mat1Rin,float** mat1Iin,
float** mat2Rin,float** mat2Iin,int lgth,int wdth)
{
 int i,j;

 for(i=0;i<lgth;i++) for(j=0;j<wdth;j++)
   { matRout[i][j]=mat1Rin[i][j]*mat2Rin[i][j]-mat1Iin[i][j]*mat2Iin[i][j];
     matIout[i][j]=mat1Rin[i][j]*mat2Iin[i][j]+mat2Rin[i][j]*mat1Iin[i][j]; }
}

/*----------------------------------------------------------*/
/* Matrice complexe au carre                                */
/*----------------------------------------------------------*/
void SquareMatrix(float** matRout,float** matIout,float** matRin,float** matIin,int lgth,int wdth)
{
 int i,j;

 for(i=0;i<lgth;i++) for(j=0;j<wdth;j++)
   { matRout[i][j]=SQUARE(matRin[i][j])-SQUARE(matIin[i][j]);
     matIout[i][j]=2*matRin[i][j]*matIin[i][j]; }
}

/*----------------------------------------------------------*/
/*  CenterImg_                                              */
/*----------------------------------------------------------*/
void CenterImg_(float** mat,int length,int width)
{
  int i, j;
  float** tmp;
  
  tmp=fmatrix_allocate_2d(length,width);
  
  for(i=0;i<length;i++) for(j=0;j<width;j++) 
    tmp[i][j]=0.0;

  IFFTDD(mat,tmp,length,width);

  for(i=0;i<length;i++) for(j=0;j<width;j++) 
    {
    mat[i][j]*=pow(-1,i+j);
    tmp[i][j]*=pow(-1,i+j);
    }

  FFTDD(mat,tmp,length,width);

  free_fmatrix_2d(tmp);
}

/*----------------------------------------------------------*/
/*  CenterImg                                               */
/*----------------------------------------------------------*/
void CenterImg(float** mat,int lgth,int wdth)
{
 int i,j;
 int ci,cj;
 float** mattmp;

 /*Initialisation*/
 ci=(int)(lgth/2);
 cj=(int)(wdth/2);

 /*Allocation memoire*/
 mattmp=fmatrix_allocate_2d(lgth,wdth);

 /*Recadrage*/
 for(i=0;i<ci;i++) for(j=0;j<cj;j++)
 mattmp[ci+i][cj+j]=mat[i][j];

 for(i=ci;i<lgth;i++) for(j=cj;j<wdth;j++)
 mattmp[i-ci][j-cj]=mat[i][j];

 for(i=0;i<ci;i++) for(j=cj;j<wdth;j++)
 mattmp[ci+i][j-cj]=mat[i][j];

 for(i=ci;i<lgth;i++) for(j=0;j<cj;j++)
 mattmp[i-ci][cj+j]=mat[i][j];

 /*Transfert*/
 for(i=0;i<lgth;i++) for(j=0;j<wdth;j++)
  mat[i][j]=mattmp[i][j];

 /*desallocation memoire*/
 free_fmatrix_2d(mattmp);
}


/*----------------------------------------------------------*/
/*  RotateImage                                               */
/*----------------------------------------------------------*/

void rotate_image(float** input_image,int length,int width, float angle) {
	int i, j;
	float pi = 3.14;
	float rad = angle * pi/ 180.0;
	float cos_theta = cos(rad), sin_theta = sin(rad);
	float center_x = width / 2.0, center_y = length/ 2.0;
	float ** tempMatR = fmatrix_allocate_2d(length,width);
	float ** tempMatI = fmatrix_allocate_2d(length,width);
	float coordX, coordY;
	int icoordX, icoordY;
	//printf("%d finx,%d finy \n",length,width);
	for(i=0;i<length;i++) {
	    for(j=0;j<width;j++) {
		 
		 //Image #1
		tempMatR[i][j]= 0.0;
		tempMatI[i][j]= 0.0 ;
		//input_image[i][j] = 0.0;
	      }
	  }
	  
       for (i = 0; i < length; i++) {
       
        for (j = 0; j < width; j++) {
       
      
         coordX = cos_theta * (j-center_x) + sin_theta * (i-center_y) + center_x;
         coordY = -sin_theta  * (j-center_x) + cos_theta * (i-center_y)+ center_y;
        
         if(floor(coordX) == floor(coordX+0.5)){
         	icoordX = floor(coordX);
         }else{
         	icoordX = ceil(coordX);
         }
          if(floor(coordY) == floor(coordY+0.5)){
         	icoordY = floor(coordY);
         }else{
         	icoordY = ceil(coordY);
         }
         
         
            // Handle out of bounds
            if (icoordX < 0 || icoordX >= width || icoordY< 0 || icoordY >=length) {
                tempMatR[i][j] = 0.0;
            }else {
             tempMatR[i][j] =  input_image[icoordY][icoordX];
            }
	 
	}
	}
	
	for(i=0;i<length;i++) {
	    for(j=0;j<width;j++) {
		 
		 //Image #1
		input_image[i][j] =  tempMatR[i][j];
		//tempMatI[i][j]= 0.0
		//input_image[i][j] = 0.0;
	      }
	  }
}

float rotate_image_by_angle(float** input_image,float** input_image2,int length,int width,float found_angle) {
  	int i, j;
  	float center_x = width / 2.0, center_y = length/ 2.0;
	float pi = 3.14;
	float increment = 0.005;
	//float rad = -angle * pi/ 180.0;
	//angle = 180.0/pi*rad
	float** MatriceImgI=fmatrix_allocate_2d(length,width);
	float** MatriceImgM=fmatrix_allocate_2d(length,width); 
	float** MatriceImgI2=fmatrix_allocate_2d(length,width);
	float** MatriceImgM2=fmatrix_allocate_2d(length,width); 
	float** MatriceImgMG=fmatrix_allocate_2d(length,width); 
	 for(i=0;i<length;i++) {
    		for(j=0;j<width;j++) {
         
		 //Image #1
		 MatriceImgI[i][j]=0.0;
		 MatriceImgM[i][j]=0.0;
		  MatriceImgI2[i][j]=0.0;
		 MatriceImgM2[i][j]=0.0;
		 MatriceImgMG[i][j] = input_image[i][j];
      		}
  	}
  	//FFTDD(input_image2,MatriceImgI2,length,width);
  	int optimal_error = -1; 
  	float optimal_degree = -1.0;
  	
  	
	for( float degree=-pi/16;degree < pi/16+increment;degree+= increment ) {
		//MatriceImgMG = input_image;
		for(i=0;i<length;i++) {
    		for(j=0;j<width;j++) {
		 input_image[i][j] = MatriceImgMG[i][j];
      			}
  		}
		rotate_image(input_image, length,width, degree);
		int error = 0.0;
		 for(int u=0;u<length;u++) {

	    		for(int v=0;v<width;v++) {
		 
			int amplitudeG = sqrt(input_image[u][v]*input_image[u][v]+MatriceImgI[u][v]*MatriceImgI[u][v]) ;
			int amplitudeF = sqrt(input_image2[u][v]*input_image2[u][v]+MatriceImgI2[u][v]*MatriceImgI2[u][v]) ;
			
			error+= amplitudeG - amplitudeF ;
			
	      		}
  		}
  		
  		if(optimal_error == -1){
  		optimal_error = error;
  		optimal_degree = degree;
  		}else if (optimal_error > error){
  			optimal_error = error;
  			optimal_degree = degree;
  		}
  		printf("[%.3f :: %d]",degree,error);
		
	  }
	  found_angle = -0.05 * 180/pi ;
	  printf("\n Angle >>> %.3f angle ",found_angle);
	  
	  return found_angle ;//l'angle que nous trouvons est 0.199

    	
    	
    	

}

void calculate_estimation(float** input_image,float** input_image2,float** input_image1, int length,int width) {
  	int i, j;
  	
    	float** MatriceImgI=fmatrix_allocate_2d(length,width);
	float** MatriceImgM=fmatrix_allocate_2d(length,width); 
	float** MatriceImgI1=fmatrix_allocate_2d(length,width);
	float** MatriceImgM2=fmatrix_allocate_2d(length,width); 
	float** MatriceImg=fmatrix_allocate_2d(length,width); 
	
	 for(i=0;i<length;i++) {
    		for(j=0;j<width;j++) {
         
		 //Image #1
		 MatriceImg[i][j] = 0.0;
		 MatriceImgI[i][j]=0.0;
		 MatriceImgM[i][j]=0.0;
		 MatriceImgI1[i][j]=0.0;
		 MatriceImgM2[i][j]=0.0;
		 
		 float calculate_estimation_num = input_image[i][j] * input_image2[i][j] ;
		 float calculate_estimation_denom= sqrt(input_image1[i][j]*input_image1[i][j]+MatriceImgI1[i][j]*MatriceImgI1[i][j]);
		 MatriceImg[i][j] = calculate_estimation_num /(calculate_estimation_denom*calculate_estimation_denom);
      		}
  	}
      
    	
	 for(i=0;i<length;i++) {
    		for(j=0;j<width;j++) {
         
		input_image2[i][j] = MatriceImg[i][j];
      		}
  	}

}
void Find_dirac(float** mat,int lgth,int wdth,int line ,int col)
{
 int i,j;

  	for(i=0;i<lgth;i++) {
    		for(j=0;j<wdth;j++) {
         	
         	if (mat[i][j] != 0)
		col = j;
		line = i;
      		}
  	}
  	
  	 printf("[line = %d :: colonne = %d ]",line,col);
  	
}

void Loga(float** mat,float coef,int lgth,int wdth)
{
 int i,j;

 /*logarithme*/
  for(i=0;i<lgth;i++) for(j=0;j<wdth;j++) 
    {
     mat[i][j] =  log(1+mat[i][j]);
      if (mat[i][j]>GREY_LEVEL) mat[i][j]=GREY_LEVEL; 
      }
}








