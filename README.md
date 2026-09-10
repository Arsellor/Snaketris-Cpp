# Snaketris – Projet C++ / SDL2

Projet pédagogique construit selon le cadre du document de SAE :
- programmation C++ modulaire ;
- fichiers `.hpp` et `.cpp` ;
- pas de classes ;
- pas de `vector` / `array` ;
- grille dynamique pour le monde ;
- Snake représenté par une liste doublement chaînée ;
- affichage SDL2 avec textures ;
- score ;
- sauvegarde avec la touche `S`.

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
- Flèche bas : aller vers le Sud
- Flèche gauche : aller vers l'Ouest
- Flèche droite : aller vers l'Est
- Espace : pause / reprise
- S : sauvegarder
- Q ou Échap : quitter

## Règles

- Le Snake avance automatiquement.
- Il ne peut pas faire demi-tour.
- Une nourriture rouge ajoute un anneau rouge.
- Une nourriture verte ajoute un anneau vert.
- Une nourriture bleue ajoute un anneau bleu.
- Une étoile applique la règle Tetris et donne un bonus.
- Trois anneaux consécutifs de même couleur déclenchent la suppression de l'anneau central.
- Le jeu s'arrête lorsque le Snake touche un bord ou son propre corps.

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
