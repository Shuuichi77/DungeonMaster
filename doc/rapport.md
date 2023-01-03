# Projet de Synthèse d'Images avancées

## 1. Introduction

Les règles du jeu et les librairies nécessaires au lancement du jeu sont présentes dans le README.md à la racine du
projet.

## 2. Architecture du projet

L'intégralité des fichiers du projet se trouvent dans le dossier dungeonMaster.

dungeonMaster   
│  
├───assets  
│&emsp;&emsp;├───fonts  
│&emsp;&emsp;├───models  
│&emsp;&emsp;├───musics  
│&emsp;&emsp;└─────textures  
├── maps  
├── shaders  
├── src  
├── include  
├── CMakeLists.txt  
└── main.cpp

## 3. Fonctionnalités implémentées

- Le projet peut lire les images .ppm pour charger un niveau. Cependant, seules les formats ASCII (P3) sont supportés.
  Les formats binaire (P6) ne sont pas supportés.
- Le projet peut lire les fichiers .txt pour charger les trésors et ennemis. Ils se présentes sous la forme suivante :
    - "#" Dungeon Zilda &emsp;(nom du projet)
    - fichier.ppm &emsp;&emsp;&emsp;&emsp;(nom du fichier .ppm à charger)
    - nombre de trésors
    - ID:col:lig:TRESOR:DIRECTION &emsp;&emsp; ID:col:lig:TRESOR:DIRECTION:quantite
    - nombre de monstres
    - ID:col:lig:MONSTRE:DIRECTION &emsp;&emsp; ID:col:lig:MONSTRE:DIRECTION:pv:attaque:defense:argent
    - nombre de rubis nécessaires pour gagner
    - nombre d'ennemis à tuer pour gagner


- Les trésors disponibles sont :
    - MILK (rend 2 coeurs)
    - POTION (rend 5 coeurs)
    - FAIRY (rend 10 coeurs ou ressucite le joueur en cas de mort)
    - MONEY
    - WOODENSWORD
    - ROYALSWORD
    - MASTERSWORD


- Les monstres disponibles sont :
    - DARKBEAST
    - DARKNUT
    - KINGBOO
    - HYDREIGON
    - ARMOGOHMA
    - DARKRAI


- DIRECTION représente l'orientation de l'objet peut être :
    - NORTH
    - SOUTH
    - EAST
    - WEST

- 2 niveaux sont disponibles dans le dossier maps (manque de temps d'en faire plus malheureusement)


- Le joueur et les monstres possèdent pv, attaque et défense


- Les monstres se déplacent en ligne dès qu'ils ont le joueur en ligne de mire. Cependant s'il y a de l'eau, ils
  s'arrêteront devant. Lorsque le joueur est à portée, ils attaqueront à intervalle régulier.


- Tous les modèles des monstres se trouvent dans le dossier /assets/models. Il n'est pas nécessaire de fournir le modèle
  3D dans le fichier .txt. Pour en rajouter, il faudra rajouter un enum dans la classe ModelType.hpp et ajouter sa
  translation/rotation/scale dans la classe ModelTransformations.


- Les murs/sols sont des quads représentés par 2 triangles.


- La carte n'est pas affichée en temps réel durant la partie.

- Les portes bloquent toutes les orientations lorsqu'elles sont présentes sur la carte. Il n'y a donc pas ce problème d'
  orientation des portes (et ceux des monstres/trésors sont à spécifier dans le fichier .txt)

## 4. Fonctionnalités supplémentaires

- Une musique et des bruitages sont ajoutées (d'où la nécessité de la librairie SDL_mixer)

- Les monstres et le joueur ont des animations lorsqu'ils attaquent