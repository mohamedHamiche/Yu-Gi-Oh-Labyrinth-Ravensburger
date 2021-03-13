Les structures :

- struct coordonnees
   - entier x
   - entier y

- struct Tuile
  -  booléen fixe // 1 fixe 0 couloir   
  -  entier trésor //0 si pas de trésor, n sinon avec  1<= n <=24  
  -  booléen gauche, droite, haut, bas  //0 si mur, 1 si ouverture
  -  booléen posée //si la tuile est posée ou pas sur le  plateau
    
- Tuile Plateau [7][7] // Matrice de tuiles    


- struct Joueur
  -  string pseudo
  -  coordonneés postion_actuelle
  -  struct pile pile_trésor
  -  entier nombre_de_points
  -  booleen machine
-----------------------------------------
Liste des fonctions:


- Joueur *initJoueurs(entier *nbTotal)

    - entier demanderNbJoueurMachine(CLAVIER)        

    - entier demanderNbJoueurHumain(CLAVIER)


        

- string lire_pseudo()


- distribuerCartes(Joueur *P1, Joueur *P2)

- Joueur quiCommence (Joueur *P1, Joueur *P2)

- booleen pileVide(struct pile)

- empiler(Joueur *P1, Entier n)

- depiler(Joueur *P1)

- initPlateau(Tuile Plateau[7][7], Tuile *tuile_en_main)
    - poserTuilesFixes(Tuile Plateau[7][7])
    - poserTuilesCouloir(Tuile Plateau[7][7],tuile *tuile_en_main)

- alterner(Joueur *p1, Joueur *p2,Joueur *joueurActuel)

- insererTuile (Tuile plateau[7][7],Tuile *tuile_en_main,coordonnées *choix_precedent)
    - coordonnées choixCouloir()
    - booléen validationCouloir(coordonnées choix_actuel,coordonnées *choix_precedent)
        - booléen opposé(coordonnées a, coordonnées choix_precedent)
    - choixOrientationTuile(Tuile *tuile_en_main)
        - tourner(Tuile *tuile_en_main, entier nombre_de_tours, char direction)
    - decalerCouloir(Tuile Plateau, coordonnees choixCouloir, Tuile *tuile_en_main)
    

- choixDeplacement(joueur *P1, Tuile plateau[7][7])
    - booléen validationCoup(Tuile *case,coordonnees a,coordonnees choix,entier compt) 

- tresorAtteint(Joueur *P1, Tuile Plateau[7][7])

- affichageJeu(Tuile Plateau[7][7])

- affichageGagnant(Joueur *gagnant)
