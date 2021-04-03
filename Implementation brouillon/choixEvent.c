#include <stdio.h>
#include <stdlib.h>
#include "structures"



void choixEvent(SDL_Event event, SDL_Rect *tuileEnMain, CORD *choix){
    //NORD
                        if(event.button.x > positionX+70 &&  event.button.x < positionX+140 && event.button.y > positionY-70 && event.button.y < positionY){
                            (tuileEnMain->x) = positionX+70;
                            (tuileEnMain->y) = positionY-70;
                            (choix->y) = 1;
                           (choix->x) = 0;
                        }
                        if(event.button.x > positionX+(70*3) &&  event.button.x < positionX+(70*4) && event.button.y > positionY-70 && event.button.y < positionY){
                            (tuileEnMain->x) = positionX+(70*3);
                           (tuileEnMain->y) = positionY-70;
                           (choix->y) = 3;
                            (choix->x) = 0;
                        }
                        if(event.button.x >  positionX+(70*5) &&  event.button.x < positionX+(70*6) && event.button.y > positionY-70 && event.button.y < positionY){
                            (tuileEnMain->x) = positionX+(70*5);
                            (tuileEnMain->y) = positionY-70;;
                            (choix->y) = 5;
                            (choix->x) = 0;
                        }

                       //EST

                        if(event.button.x > positionX+(70*7) &&  event.button.x < positionX+(70*8) && event.button.y > positionY+70 && event.button.y < positionY+(2*70)){
                            (tuileEnMain->x) = positionX+(70*7);
                            (tuileEnMain->y) = positionY+70;
                            (choix->y) = 6;
                            (choix->x) = 1;
                        }
                        if(event.button.x > positionX+(70*7) &&  event.button.x < positionX+(70*8) && event.button.y > positionY+(3*70) && event.button.y < positionY+(4*70)){
                            (tuileEnMain->x) = positionX+(70*7);;
                            (tuileEnMain->y) = positionY+(3*70);
                            (choix->y)= 6;
                            (choix->x) = 3;
                        }

                          if(event.button.x > positionX+(70*7) &&  event.button.x < positionX+(70*8) && event.button.y > positionY+(5*70) && event.button.y < positionY+(6*70)){
                            (tuileEnMain->x) = positionX+(70*7);;
                            (tuileEnMain->y) = positionY+(5*70);
                            (choix->y)= 6;
                            (choix->x) = 5;
                        }

                        //SUD
                        if(event.button.x > positionX+70 &&  event.button.x < positionX+(2*70) && event.button.y > positionY+(7*70) && event.button.y < positionY+(8*70)){
                            (tuileEnMain->x) = positionX+70;
                            (tuileEnMain->y) = positionY+(7*70);
                            (choix->y) = 1;
                            (choix->x) = 6;
                        }
                        if(event.button.x > positionX+(3*70) &&  event.button.x < positionX+(4*70) && event.button.y > positionY+(7*70) && event.button.y < positionY+(8*70)){
                            (tuileEnMain->x) = positionX+(3*70);
                            (tuileEnMain->y) = positionY+(7*70);
                            (choix->y) = 3;
                            (choix->x)= 6;
                        }
                        if(event.button.x > positionX+(5*70) &&  event.button.x < positionX+(6*70) && event.button.y > positionY+(7*70) && event.button.y < positionY+(8*70)){
                            (tuileEnMain->x) = positionX+(5*70);
                            (tuileEnMain->y) = positionY+(7*70);
                            (choix->y) = 5;
                            (choix->x) = 6;
                        }

                        //OUEST
                        if(event.button.x > positionX-70 &&  event.button.x < positionX && event.button.y > positionY+70 && event.button.y < positionY+140){
                            (tuileEnMain->x) = positionX-70;
                            (tuileEnMain->y) = positionY+70;
                            (choix->y) = 0;
                            (choix->x) = 1;
                        }
                        if(event.button.x > positionX-70 &&  event.button.x < positionX && event.button.y > positionY+(3*70) && event.button.y < positionY+(4*70)){
                            (tuileEnMain->x) = positionX-70;
                            (tuileEnMain->y) = positionY+(3*70);
                            (choix->y) = 0;
                            (choix->x) = 3;
                        }

                          if(event.button.x > positionX-70 &&  event.button.x < positionX && event.button.y > positionY+(5*70) && event.button.y < positionY+(6*70)){
                            (tuileEnMain->x) = positionX-70;
                            (tuileEnMain->y) = positionY+(5*70);
                            (choix->y) = 0;
                            (choix->x) = 5;
                        }
}
