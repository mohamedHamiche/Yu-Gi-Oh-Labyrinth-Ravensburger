

int validationCoup(TUILE tab[7][7],TUILE caseP,CORD a,CORD choix,int compt){
    // Tuile case : adresse de la case précedente appelé dans l'appel précedent
    // coordonnees a : position de actuel de l'appel de la fonction
    // coordonnees choix : La case à atteindre
    // entier compt : nombre actuel des appels récursif de la fonction

    if(a.x == choix.x && a.y == choix.y)
        return 1;
    
    if(compt == 300) // Le plus long chemin possible pour être certain que la fonction parcours tous les chemins possible à partir de la coordonnees et  pour que ça s'arrête.
        return 0;
    

    if((taba.x][a.y].d == 1 && tab[a.x][a.y = a.y+1].g == 1) && tab[a.x][a.y = a.y + 1] != caseP){ // Si c'est "ouvert" à droite et si à droite c'est "ouvert" à 
                                                                                                     //..gauche et que ce n'est pas la case précedente alors déplacer a (a.y incrémenté -> vers la droite)
        a.y = a.y+1                                                                                     // On déplace la coordonnees vers la "droite" ...
        res =validationCoup(tab[a.x][a.y = a.y-1],a,choix,compt = compt +1) // Appel récursif 
        }

    if((tab[a.x][a.y].h == 1 && tab[a.x = a.x-1][a.y].b == 1) && tab[a.x = a.x-1][a.y] != caseP){ //...
        a.x = a.x-1                                                                     //... 
        res= validationCoup(tab[a.x = a.x+1][a.y],a,choix,comp = compt+1)                         //...
        }

    if((tab[a.x][a.y].g == 1 && tab[a.x][a.y = a.y-1].d == 1) && tab[a.x][a.y = a.y-1] != caseP){
        a.y = a.y-1
        res= validationCoup(tab[a.x][a.y = a.y+1],a,choix,compt = compt+1)
        }

    if((tab[a.x][a.y].b == 1 && tab[a.x = a.x+1][a.y].h == 1) && tab[a.x = a.x+1][a.y] != caseP){
        a.x = a.x-1
        res = validationCoup(tab[a.x = a.x-1][a.y],a,choix,compt = compt+1)
        }

    return res;
}