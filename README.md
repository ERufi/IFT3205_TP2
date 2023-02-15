# IFT3205_TP2

----------------------------------
---- TP no 2 ---------------------
----------------------------------

Creer un repertoire TP2
  --> mkdir TP2

Aller dans TP2
  --> cd TP2

Copier les differents progs et images dans votre repertoire
données sur ma page web

Pour rendre executable les Programmes et Scripts
 --> chmod 700 *

Pour compiler le programme Tp2_IFT3205_2-1.c
 --> ./compilegcc Tp2_IFT3205_2-1

Pour executer le programme
 --> ./Tp2_IFT3205_2-1

Pour editer le programme
 --> emacs Tp2_IFT3205_2-1.c
 
 
 

L'énoncé du tp2 ainsi que les programmes fournis se trouvent sur le site 
du cours:

http://www.iro.umontreal.ca/~mignotte/ift3205.html

Le tp2 est à remettre le 19 Fevrier avant 18h30.
Pénalité de 20% par 24h de retard.

Il n'y a pas de rapport écrit; seulement des programmes a rendre et des images résultats
Vous devez fournir les programmes (qui doivent produire les images) suivants:

     [15 pts]
     Tp2_IFT3205_2-1.c
      affichant à l'écran le module des deux spectres (centrés au centre de l'image) 
      des deux images UdM_1.pgm et UdM_2.pgm
      >image-TpIFT3205-2-1a.pgm
      >image-TpIFT3205-2-1b.pgm
      

     [15 pts] 
     Tp2_IFT3205_2-2.c
      affichant à l'écran l'image Lena et Lena rotationé de 22.5 degré
      par interpolation bilinéaire (ou si vous n'y arrivé pas, par 
      interpolation au plus proche voisin pour 5 pts de moins)
      >image-TpIFT3205-2-2.pgm


     [15 pts] 
     Tp2_IFT3205_2-3.c
       affichant à l'écran la valeur de l'erreur pour les different angles considérés
       du style : [-0.196::3991]>[-0.191::3978]>[-0.186::3961]>[-0.181::3947]>[-0.176::3931] ....
       et affichant le résultat final du style : 
             Angle >>> [-0.051350]
       Si vous n'arrivez pas à faire cette question, prenez un angle qui vous semble bon (comme -0.05 radian)


     [20 pts] 
     Tp2_IFT3205_2-4.c
        programme reprenant le programme précédent et utilisant la valeur de l'angle de rotation 
        estimée permettant de recaler en rotation l'image g (UdM_2.pgm) par interpolation
        bilinéaire (si vous n'y arriver pas utiliser l'interpolation au plus proche voisin pour 5 pts de moins)
        et affichant à l'écran l'image g et l'image g recalé en rotation.
         >image-TpIFT3205-2-4.pgm  

    
     [20 pts] 
     Tp2_IFT3205_2-5.c
       affichant à l'écran le vecteur de translation du style :
              Translation (ligne=-15::colonne=158) 
       et l'image de l'interspectre (cad l'image du dirac).
       >image-TpIFT3205-2-5.pgm  

     
     [15 pts] 
     Tp2_IFT3205_2-6.c
       affichant à l'écran l'image recalée en rotation et translation.
       >image-TpIFT3205-2-6.pgm  
     

Total: 100 points.
