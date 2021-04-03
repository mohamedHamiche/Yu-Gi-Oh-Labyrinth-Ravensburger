#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>



void listTuilesCouloir(TUILE tuilesCouloir[34])
{    
    unsigned int temp = 0;
    for(int i=0; i<12; i++) //les 12 premieres sont des tuiles droites
    {           
        tuilesCouloir[i].angle= 0;
        temp = rand()%2; 
        tuilesCouloir[i].fixe =0;
        tuilesCouloir[i].posee =0;
        tuilesCouloir[i].tresor =0;
        tuilesCouloir[i].type ='I'; 
        tuilesCouloir[i].g = temp; //la gauche au hasard 

        if(temp == 0)
        {
            tuilesCouloir[i].id = 1; //a quoi ca sert ??
            tuilesCouloir[i].angle = 0;
            tuilesCouloir[i].d = 0;
            tuilesCouloir[i].g = 0;
            tuilesCouloir[i].h = 1;
            tuilesCouloir[i].b = 1;
        }
        else
        {
            tuilesCouloir[i].id = 1;
            tuilesCouloir[i].angle =90;
            tuilesCouloir[i].d = 1;
            tuilesCouloir[i].g = 1;
            tuilesCouloir[i].h = 0;
            tuilesCouloir[i].b = 0;
        }
        
    }

     //### TUILE : angle droit supposons que g h a un angle 0 
    int nbTresors=6; //de 6 à 1 tresors dans angle droit  --> de F à A  
    for (int i = 12; i < 16+12; ++i) // de 12 à 28 angle droit
    {
        tuilesCouloir[i].angle= 0;
        temp = rand()%4; // 4 cas possibles
        tuilesCouloir[i].fixe =0;
        tuilesCouloir[i].posee =0;
        tuilesCouloir[i].type ='L';     
        if(temp == 0)
        {
            tuilesCouloir[i].g=1;
            tuilesCouloir[i].d=0;
            tuilesCouloir[i].h=1;
            tuilesCouloir[i].b=0;
            tuilesCouloir[i].angle=0;
        }
        if(temp == 1)
        {
            tuilesCouloir[i].g=1;
            tuilesCouloir[i].d=0;
            tuilesCouloir[i].h=0;
            tuilesCouloir[i].b=1;
            tuilesCouloir[i].angle=90;
        }
        if(temp == 2)
        {
            tuilesCouloir[i].g=0;
            tuilesCouloir[i].d=1;
            tuilesCouloir[i].h=1;
            tuilesCouloir[i].b=0;
            tuilesCouloir[i].angle=180;
        }
        if(temp == 3)
        {
            tuilesCouloir[i].g=0;
            tuilesCouloir[i].d=1;
            tuilesCouloir[i].h=0;
            tuilesCouloir[i].b=1;
            tuilesCouloir[i].angle=270; 
        }
        tuilesCouloir[i].tresor=0;
        if(nbTresors>0) 
        {               
            tuilesCouloir[i].tresor=nbTresors;          
            nbTresors--;
        }
    }

    //les tresors restants: de 7 à 12 dans tuile en T
    nbTresors=7;
    for (int i = 16+12; i < 34; ++i)
     {
        temp = rand()%4; // 4 cas possibles
        tuilesCouloir[i].fixe =0;
        tuilesCouloir[i].posee =0; 
        tuilesCouloir[i].type ='T'; 
        tuilesCouloir[i].tresor =nbTresors;
        nbTresors++;   
        if(temp == 0)
        {
            tuilesCouloir[i].g=1;
            tuilesCouloir[i].d=1;
            tuilesCouloir[i].h=1;
            tuilesCouloir[i].b=0;
            tuilesCouloir[i].angle=0;
        }
        if(temp == 1)
        {
            tuilesCouloir[i].g=0;
            tuilesCouloir[i].d=1;
            tuilesCouloir[i].h=1;
            tuilesCouloir[i].b=1;
            tuilesCouloir[i].angle=90;
        }
        if(temp == 2)
        {
            tuilesCouloir[i].g=1;
            tuilesCouloir[i].d=1;
            tuilesCouloir[i].h=0;
            tuilesCouloir[i].b=1;
            tuilesCouloir[i].angle=180;
        }
        if(temp == 3)
        {
            tuilesCouloir[i].g=1;
            tuilesCouloir[i].d=0;
            tuilesCouloir[i].h=1;
            tuilesCouloir[i].b=1;
            tuilesCouloir[i].angle=270; 
        }

     }      
}