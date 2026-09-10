# Snaketris – Projet C++ / SDL2

Projet pédagogique construit selon le cadre du document de SAE :
- programmation C++ modulaire ;
## Dépendances (Linux / Ubuntu / Debian)

```bash
sudo apt update
sudo apt install build-essential libsdl2-dev
```

## Compiler

À la racine du projet :

```bash
make
```

## Lancer

```bash
./snaketris
```

ou :

```bash
make run
```

Pour choisir le nom du fichier de sauvegarde :

```bash
./snaketris save/ma_partie.txt
```

## Commandes

- Flèche haut : aller vers le Nord
- Flèche haut : aller vers le Nord
- Flèche bas : aller vers le Sud
- Flèche gauche : aller vers l’Ouest
- Flèche droite : aller vers l’Est
- Espace : mettre en pause / reprendre la partie
- Q ou Échap : quitter le jeu
- S : sauvegarder la partie
  
## Règles

- Le Snake avance automatiquement.
## Structure

```text
src/
  enum.hpp
  window.hpp / window.cpp
  world.hpp / world.cpp
  snake.hpp / snake.cpp
  view.hpp / view.cpp
  game.hpp / game.cpp
  main.cpp
img/
  textures BMP
save/
  fichiers de sauvegarde
Makefile
glossaire.txt
```
