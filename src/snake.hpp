#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "enum.hpp"

// Represents one colored ring of the doubly linked snake body.
struct Ring {
    int x;
    int y;
    Food food;
    Ring* previous;
    Ring* next;
};

// Represents the snake head and the doubly linked list of body rings.
struct Snake {
    int head_x;
    int head_y;
    Direction direction;
    Ring* first;
    Ring* last;
};

// Initializes a snake containing only its head.
void init_snake(Snake* snake, int x, int y);

// Frees every ring of the doubly linked list.
void free_snake(Snake* snake);

// Changes direction while preventing an immediate U-turn.
void change_direction(Snake* snake, Direction direction);

// Moves the body rings so each one follows its predecessor.
void move_rings(Snake* snake, int old_head_x, int old_head_y);

// Moves the snake head one cell and updates its body.
void move_snake(Snake* snake);

// Adds a colored ring at the end of the snake body.
void add_ring(Snake* snake, Food food);

// Returns true when a ring occupies coordinates (x, y).
bool snake_contains(Snake* snake, int x, int y);

// Returns true when the head touches its body.
bool snake_touches_body(Snake* snake);

// Counts the number of body rings.
int snake_length(Snake* snake);

// Removes the middle ring of the first triple of equal consecutive colors.
bool remove_tetris_ring(Snake* snake);

#endif
