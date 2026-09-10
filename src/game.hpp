#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include "window.hpp"
#include "world.hpp"
#include "snake.hpp"
#include "view.hpp"

using namespace std;

// Stores all data required by the Snaketris game.
struct Game {
    World* world;
    Snake* snake;
    WorldView* world_view;
    SnakeView* snake_view;

    bool running;
    bool game_over;
    bool paused;
    bool mouth_open;

    int score;
    int bonus_star;
    Uint32 move_delay;
    Uint32 last_move;
};

// Initializes a complete game and its initial food.
bool init_game(Game* game, Window* window);

// Frees all dynamically allocated game data.
void free_game(Game* game);

// Handles SDL keyboard and window events.
void keyboard_event(Game* game, Window* window, string save_filename);

// Advances the game by one movement step.
void update_game(Game* game);

// Returns true when the snake head is outside the world.
bool snake_touches_border(Game* game);

// Adds a random food in an empty cell not occupied by the snake.
void add_random_food(Game* game);

// Saves the current game state in a text file.
bool save_game(Game* game, string filename);

#endif
