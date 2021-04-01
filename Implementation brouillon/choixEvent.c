#include <stdio.h>
#include <stdlib.h>
#include "structures"



void choixEvent(SDL_Event event, SDL_Rect *tuileEnMain, CORD *choix){
    //NORD
                        if(event.button.x > 219 &&  event.button.x < 290 && event.button.y > 79 && event.button.y < 150){
                            (tuileEnMain->x) = 220;
                            (tuileEnMain->y) = 80;
                            (choix->x) = 1;
                           (choix->y) = 0;
                        }
                        if(event.button.x > 359 &&  event.button.x < 430 && event.button.y > 79 && event.button.y < 150){
                            (tuileEnMain->x) = 360;
                           (tuileEnMain->y) = 80;
                           (choix->x) = 3;
                            (choix->y) = 0;
                        }
                        if(event.button.x > 499 &&  event.button.x < 570 && event.button.y > 79 && event.button.y < 150){
                            (tuileEnMain->x) = 500;
                            (tuileEnMain->y) = 80;
                            (choix->x) = 5;
                            (choix->y) = 0;
                        }

                       //EST

                        if(event.button.x > 639 &&  event.button.x < 710 && event.button.y > 219 && event.button.y < 290){
                            (tuileEnMain->x) = 640;
                            (tuileEnMain->y) = 220;
                            (choix->x) = 6;
                            (choix->y) = 1;
                        }
                        if(event.button.x > 639 &&  event.button.x < 710 && event.button.y > 359 && event.button.y < 430){
                            (tuileEnMain->x) = 640;
                            (tuileEnMain->y) = 360;
                            (choix->x)= 6;
                            (choix->y) = 3;
                        }

                          if(event.button.x > 639 &&  event.button.x < 710 && event.button.y > 499 && event.button.y < 570){
                            (tuileEnMain->x) = 640;
                            (tuileEnMain->y) = 500;
                            (choix->x)= 6;
                            (choix->y) = 5;
                        }

                        //SUD
                        if(event.button.x > 219 &&  event.button.x < 290 && event.button.y > 640 && event.button.y < 710){
                            (tuileEnMain->x) = 220;
                            (tuileEnMain->y) = 640;
                            (choix->x) = 1;
                            (choix->y) = 6;
                        }
                        if(event.button.x > 359 &&  event.button.x < 430 && event.button.y > 640 && event.button.y < 710){
                            (tuileEnMain->x) = 360;
                            (tuileEnMain->y) = 640;
                            (choix->x) = 3;
                            (choix->y )= 6;
                        }
                        if(event.button.x > 499 &&  event.button.x < 570 && event.button.y > 640 && event.button.y < 710){
                            (tuileEnMain->x) = 500;
                            (tuileEnMain->y) = 640;
                            (choix->x) = 5;
                            (choix->y) = 6;
                        }

                        //OUEST
                        if(event.button.x > 79 &&  event.button.x < 150 && event.button.y > 219 && event.button.y < 290){
                            (tuileEnMain->x) = 79;
                            (tuileEnMain->y) = 220;
                            (choix->x) = 0;
                            (choix->y) = 1;
                        }
                        if(event.button.x > 79 &&  event.button.x < 150 && event.button.y > 359 && event.button.y < 430){
                            (tuileEnMain->x) = 79;
                            (tuileEnMain->y) = 360;
                            (choix->x) = 0;
                            (choix->y) = 3;
                        }

                          if(event.button.x > 79 &&  event.button.x < 150 && event.button.y > 499 && event.button.y < 570){
                            (tuileEnMain->x) = 79;
                            (tuileEnMain->y) = 500;
                            (choix->x) = 0;
                            (choix->y) = 5;
                        }
}