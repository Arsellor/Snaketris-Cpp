# Snaketris – Projet C++ / SDL2

Projet pédagogique et universitaire:
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

### Conditions de défaite
Le serpent perd si sa tête touche :
- Le bord du plateau
- Son propre corps

### Les fruits
Des fruits de trois couleurs différentes peuvent apparaître sur le plateau : **rouge**, **vert** et **bleu**.

Chaque fruit consommé déclenche les actions suivantes :
1. **Grandissement :** Ajoute un anneau au corps du serpent.
2. **Score :** Augmente le score de 1 point.
3. **Apparition :** Fait apparaître un nouveau fruit à un autre endroit.

### Règle « Tetris »
- Lorsque **trois anneaux consécutifs** ont la même couleur, celui du milieu disparaît automatiquement.

### L’étoile
Lorsqu'un serpent mange une étoile :
- **Suppression :** Le jeu cherche et supprime un triplet d'anneaux identiques consécutifs.
- **Pénalité :** Si un triplet est supprimé, le score diminue légèrement.
- **Bonus :** La valeur bonus de l'étoile est ensuite ajoutée, ce qui peut faire augmenter le score global selon les règles définies.

---

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
