#ifndef VIEW_HPP
#define VIEW_HPP

#include "window.hpp"
#include "world.hpp"
#include "snake.hpp"

// Stores the textures used to draw world cells.
struct WorldView {
    SDL_Texture* background;
    SDL_Texture* red;
    SDL_Texture* green;
    SDL_Texture* blue;
    SDL_Texture* star;
};

// Stores the textures used to draw the snake body and head states.
struct SnakeView {
    SDL_Texture* body_red;
    SDL_Texture* body_green;
    SDL_Texture* body_blue;

    SDL_Texture* head_north_closed;
    SDL_Texture* head_south_closed;
    SDL_Texture* head_west_closed;
    SDL_Texture* head_east_closed;

    SDL_Texture* head_north_open;
    SDL_Texture* head_south_open;
    SDL_Texture* head_west_open;
    SDL_Texture* head_east_open;
};

// Loads the textures used by the world.
bool init_world_view(WorldView* view, Window* window);

// Loads the textures used by the snake.
bool init_snake_view(SnakeView* view, Window* window);

// Destroys all textures stored in a WorldView.
void free_world_view(WorldView* view);

// Destroys all textures stored in a SnakeView.
void free_snake_view(SnakeView* view);

// Draws the complete world grid.
void draw_world(Window* window, World* world, WorldView* view,
                int offset_x, int offset_y, int cell_size);

// Draws the snake with textures and its current direction.
void draw_snake(Window* window, Snake* snake, SnakeView* view,
                int offset_x, int offset_y, int cell_size, bool mouth_open);

// Draws a simple numeric score without requiring SDL_ttf.
void draw_number(Window* window, int value, int x, int y, int scale);

#endif
