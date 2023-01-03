# Dungeon Zilda

Projet Master 2 utilisant OpenGL et C++

## Règles

Le but du jeu est de trouver la sortie du donjon en amassant un nombre de rubis nécessaire et en tuant un certain nombre
d'ennemis selon le niveau, à l'aide des différents trésors sur la route qui vous permettront de vous soigner ou de
récupérer de meilleures armes que l'épée en bois donnée au début du jeu.

## Libraries nécéssaires

**NB: L'installation sous machine unix et le lancement du jeu seront décrits sous machine Unix uniquement.**

- glew : sudo apt-get install libglew-dev
- assimp : sudo apt install assimp-utils libassimp-dev libassimp5 *(pemret de charger les modèles 3D)*
- SDL : sudo apt-get install libsdl1.2-dev *(permet de charger les textures)*
- SDL_ttf : sudo apt install libsdl-ttf2.0-dev *(permet d'afficher du texte à l'écran avec des polices différentes)*
- SDL_mixer : sudo apt-get install libsdl-mixer1.2 et sudo apt-get install libsdl-mixer1.2-dev *(permet de jouer des
  musiques et des sons)*

## Lancement du jeu

- Cloner/télécharger le projet
- Se placer dans la racine du projet et depuis un terminal :
    - mkdir build
    - cd build
    - cmake ../
    - make
    - ./dungeonMaster/main
        - Le jeu peut se lancer sans paramètres, ou bien avec le nom d'un fichier .txt dans le dossier
          ./dungeonMaster/maps/ pour charger un niveau, mais également avec la taille de la hauteur de la fenêtre  
          Exemple :
            - ./dungeonMaster/main dungeon_01.txt
            - ./dungeonMaster/main dungeon_01.txt 800

## Comment jouer

Le personnage se déplace avec z q s d, et peut effectuer une rotation sur la gauche ou la droite avec respectivement a
et e, ou bien en utilisant les flèches directionnelles présentes au milieu de son inventaire. Lorsque le personne trouve
des trésors il peut les utiliser en cliquant dessus dans son inventaire.  
Il peut trouver des trésors pouvant le soigner (lait, potion, fée pouvant même le ressuciter en cas de mort), ou bien 2
armes : l'épée royale et la master sword.  
Enfin, lorsque le joueur se trouve devant un ennemi, il peut l'attaqur avec le clic gauche.











