# Labyrinthe Yu-Gi-Oh [![UPVD Logo](https://upload.wikimedia.org/wikipedia/fr/e/e6/UPVD_logo.svg)](https://www.univ-perp.fr)

Labyrinthe Ravensburger sous le thème du manga Yu-Gi-Oh, exéctuable sous linux et Windows.
## Environnement Linux
### bibliothèque requise (SDL2)
Bibliothèque SDL2 requise pour le fonctionnement du programme, voici quelques ligne de commande pour l'installer.
```shell
sudo apt-get install libsdl2-image-dev
```
#### SDL_Image:
```shell
sudo apt install libsdl2-dev libsdl2-2.0-0 -y
```
#### Update & upgrade:
```shell
sudo apt-get update && sudo apt-get upgrade
```
Pour mettre à jour vos bibliothèques.
## Execution
Se déplacer dans le répertoire `versionLinux` ou `versionWindows` selon votre OS.
#### Building
```shell
make
```
#### Run
```shell
./bin/prog
```
Pour jouer choisir une des douzes insertion possible de la tuile en main avec le `clique gauche`, changez l'orientation de la tuile avec le `clique droit` et pour insérerer la tuile en main appuyez sur la `flèche du haut`, et choisir la tuile du plateau dans laquel vous souhaitez déplacer le pion.
### Tests unitaires
```shell
./bin/test_game
``` 

