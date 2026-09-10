#include "game.hpp"

#include <cstdlib>
#include <ctime>
#include <fstream>

// Initializes a complete game and its initial food.
bool init_game(Game* game, Window* window) {
    game->world = new World;
    init_world(game->world, 20, 20);

    game->snake = new Snake;
    init_snake(
        game->snake,
        game->world->width / 2,
        game->world->height / 2
    );

    game->world_view = new WorldView;
    game->snake_view = new SnakeView;

    if (!init_world_view(game->world_view, window) ||
        !init_snake_view(game->snake_view, window)) {
        return false;
    }

    game->running = true;
    game->game_over = false;
    game->paused = false;
    game->mouth_open = false;
    game->score = 0;
    game->bonus_star = 5;
    game->move_delay = 170;
    game->last_move = SDL_GetTicks();

    srand((unsigned int)time(nullptr));

    add_random_food(game);
    add_random_food(game);

    return true;
}

// Frees all dynamically allocated game data.
void free_game(Game* game) {
    if (game->world_view != nullptr) {
        free_world_view(game->world_view);
        delete game->world_view;
        game->world_view = nullptr;
    }

    if (game->snake_view != nullptr) {
        free_snake_view(game->snake_view);
        delete game->snake_view;
        game->snake_view = nullptr;
    }

    if (game->world != nullptr) {
        free_world(game->world);
        delete game->world;
        game->world = nullptr;
    }

    if (game->snake != nullptr) {
        free_snake(game->snake);
        delete game->snake;
        game->snake = nullptr;
    }
}

// Handles SDL keyboard and window events.
void keyboard_event(Game* game, Window* window, string save_filename) {
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            game->running = false;
        }

        if (event.type == SDL_KEYDOWN) {
            SDL_Keycode key = event.key.keysym.sym;

            if (key == SDLK_q || key == SDLK_ESCAPE) {
                game->running = false;
            } else if (key == SDLK_SPACE && !game->game_over) {
                game->paused = !game->paused;
            } else if (key == SDLK_UP && !game->paused) {
                change_direction(game->snake, NORTH);
            } else if (key == SDLK_DOWN && !game->paused) {
                change_direction(game->snake, SOUTH);
            } else if (key == SDLK_LEFT && !game->paused) {
                change_direction(game->snake, WEST);
            } else if (key == SDLK_RIGHT && !game->paused) {
                change_direction(game->snake, EAST);
            } else if (key == SDLK_s) {
                if (save_game(game, save_filename)) {
                    SDL_SetWindowTitle(window->sdl_window, "Snaketris - Sauvegarde effectuee");
                }
            }
        }
    }
}

// Returns true when the snake head is outside the world.
bool snake_touches_border(Game* game) {
    return !in_world(
        game->world,
        game->snake->head_x,
        game->snake->head_y
    );
}

// Adds a random food in an empty cell not occupied by the snake.
void add_random_food(Game* game) {
    int max_attempts = game->world->width * game->world->height * 2;

    for (int attempt = 0; attempt < max_attempts; attempt++) {
        int x = rand() % game->world->width;
        int y = rand() % game->world->height;

        if (read_world(game->world, x, y) == EMPTY &&
            !snake_contains(game->snake, x, y)) {

            int value = rand() % 12;
            Food food;

            if (value < 4) food = FOOD_RED;
            else if (value < 8) food = FOOD_GREEN;
            else if (value < 11) food = FOOD_BLUE;
            else food = FOOD_STAR;

            write_world(game->world, x, y, food);
            return;
        }
    }
}

// Advances the game by one movement step.
void update_game(Game* game) {
    if (game->game_over || game->paused) {
        return;
    }

    move_snake(game->snake);

    if (snake_touches_border(game) ||
        snake_touches_body(game->snake)) {
        game->game_over = true;
        return;
    }

    Food food = read_world(
        game->world,
        game->snake->head_x,
        game->snake->head_y
    );

    game->mouth_open = (food != EMPTY);

    if (food == FOOD_RED ||
        food == FOOD_GREEN ||
        food == FOOD_BLUE) {

        add_ring(game->snake, food);
        game->score++;

        write_world(
            game->world,
            game->snake->head_x,
            game->snake->head_y,
            EMPTY
        );

        add_random_food(game);
    }

    if (food == FOOD_STAR) {
        bool removed = remove_tetris_ring(game->snake);

        if (removed) {
            game->score--;
            if (game->score < 0) game->score = 0;
        }

        game->score += game->bonus_star;

        write_world(
            game->world,
            game->snake->head_x,
            game->snake->head_y,
            EMPTY
        );

        add_random_food(game);
    }

    // Basic Tetris rule: a triple of equal consecutive rings removes its middle ring.
    if (remove_tetris_ring(game->snake)) {
        game->score--;
        if (game->score < 0) game->score = 0;
    }
}

// Saves the current game state in a text file.
bool save_game(Game* game, string filename) {
    ofstream file(filename);

    if (!file) {
        return false;
    }

    file << "SNAKETRIS_SAVE_V1" << endl;
    file << game->world->width << " " << game->world->height << endl;
    file << game->score << endl;
    file << game->snake->head_x << " "
         << game->snake->head_y << " "
         << (int)game->snake->direction << endl;
    file << snake_length(game->snake) << endl;

    Ring* current = game->snake->first;
    while (current != nullptr) {
        file << current->x << " "
             << current->y << " "
             << (int)current->food << endl;
        current = current->next;
    }

    int food_count = 0;
    for (int y = 0; y < game->world->height; y++) {
        for (int x = 0; x < game->world->width; x++) {
            if (read_world(game->world, x, y) != EMPTY) {
                food_count++;
            }
        }
    }

    file << food_count << endl;

    for (int y = 0; y < game->world->height; y++) {
        for (int x = 0; x < game->world->width; x++) {
            Food food = read_world(game->world, x, y);
            if (food != EMPTY) {
                file << x << " " << y << " " << (int)food << endl;
            }
        }
    }

    file.close();
    return true;
}
