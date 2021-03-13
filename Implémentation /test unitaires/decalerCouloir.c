#include <stdio.h>
#include <stdlib.h>


//Testé avec des entiers au lieu des tuiles, qui ne sont pas encore initialisées dans le programme


Tuile decalerCouloir(Tuile plateau[7][7], cord choixCouloir, Tuile tuileEnMain){

    Tuile tmp,dec;
    unsigned int i = 0;
    if(choixCouloir.x == 0 || choixCouloir.x == 6){

        if(choixCouloir.x == 0){
            tmp = plateau[choixCouloir.x][choixCouloir.y];
            plateau[choixCouloir.x][choixCouloir.y] = tuileEnMain;
            dec = plateau[choixCouloir.x+1][choixCouloir.y];
            plateau[choixCouloir.x+1][choixCouloir.y] = tmp;
            tmp=dec;
            for(i=1; i<6; i++){
                dec =plateau[i+1][choixCouloir.y];
                plateau[i+1][choixCouloir.y] = tmp;
                tmp = dec;
            }
        }
          
        if(choixCouloir.x == 6){
            tmp = plateau[choixCouloir.x][choixCouloir.y];
            plateau[choixCouloir.x][choixCouloir.y] = tuileEnMain;
            for(i=6; i>0; i--){
                dec = plateau[i-1][choixCouloir.y];
                plateau[i-1][choixCouloir.y] = tmp;
                tmp = dec;
            }
        } 
    }
    
    else if(choixCouloir.y == 0 || choixCouloir.y == 6){

            if(choixCouloir.y == 0){
                tmp = plateau[choixCouloir.x][choixCouloir.y];
                plateau[choixCouloir.x][choixCouloir.y] = tuileEnMain;
                dec = plateau[choixCouloir.x][choixCouloir.y+1];
                plateau[choixCouloir.x][choixCouloir.y+1] = tmp;
                for(i=1; i<6; i++){
                    dec = plateau[choixCouloir.x][i+1];
                    plateau[choixCouloir.x][i+1] = tmp;
                    tmp = dec;
                }
            }
        
            if(choixCouloir.y == 6){
                tmp = plateau[choixCouloir.x][choixCouloir.y];
                plateau[choixCouloir.x][choixCouloir.y] = tuileEnMain;
                    for(i=6; i>0; i--){
                        dec = plateau[choixCouloir.x][i-1];
                        plateau[choixCouloir.x][i-1] = tmp;
                        tmp = dec;
                    }
            }
        }

    return tmp; // nouvelle tuileEnMain
}
