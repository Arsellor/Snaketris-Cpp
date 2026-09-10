#include <iostream>
#include <string>

#include "window.hpp"
#include "game.hpp"
#include "view.hpp"

using namespace std;

// Draws a small information bar above the game board.
void draw_hud(Window* window, Game* game) {
    set_color(&window->foreground, 25, 28, 38, 255);
    draw_fill_rectangle(window, 0, 0, window->width, 80);

    set_color(&window->foreground, 80, 220, 255, 255);
    draw_number(window, game->score, 28, 20, 5);

    set_color(&window->foreground, 70, 70, 85, 255);
    draw_rectangle(window, 20, 10, 100, 55);

    if (game->paused) {
        set_color(&window->foreground, 255, 210, 60, 255);
        draw_fill_rectangle(window, window->width - 110, 20, 12, 40);
        draw_fill_rectangle(window, window->width - 85, 20, 12, 40);
    }

    if (game->game_over) {
        set_color(&window->foreground, 180, 20, 40, 210);
        draw_fill_rectangle(window, 0, 80, window->width, window->height - 80);

        set_color(&window->foreground, 255, 255, 255, 255);
        draw_rectangle(window, 170, 300, 460, 170);
    }
}

// Updates the window title with useful game information.
void update_title(Window* window, Game* game) {
    string title = "Snaketris | Score: " + to_string(game->score)
                 + " | Fleches: direction | Espace: pause | S: sauvegarder | Q: quitter";

    if (game->game_over) {
        title = "GAME OVER - Snaketris | Q pour quitter";
    }

    SDL_SetWindowTitle(window->sdl_window, title.c_str());
}

// Starts the complete Snaketris game.
int main(int argc, char** argv) {
    string save_filename = "save/snaketris_save.txt";

    if (argc >= 2) {
        save_filename = argv[1];
    }

    Window window;

    if (!init_window(
        &window,
        800,
        880,
        "Snaketris"
    )) {
        return 1;
    }

    set_color(
        &window.background,
        12, 14, 20, 255
    );

    Game game;
    game.world = nullptr;
    game.snake = nullptr;
    game.world_view = nullptr;
    game.snake_view = nullptr;

    if (!init_game(&game, &window)) {
        cerr << "Erreur : impossible d'initialiser les textures." << endl;
        free_game(&game);
        close_window(&window);
        return 1;
    }

    const int cell_size = 36;
    const int board_size = 20 * cell_size;
    const int offset_x = (window.width - board_size) / 2;
    const int offset_y = 120;

    while (game.running) {
        keyboard_event(&game, &window, save_filename);

        Uint32 now = SDL_GetTicks();

        if (!game.game_over &&
            !game.paused &&
            now - game.last_move >= game.move_delay) {

            update_game(&game);
            game.last_move = now;
        }

        clear_window(&window);

        draw_hud(&window, &game);

        draw_world(
            &window,
            game.world,
            game.world_view,
            offset_x,
            offset_y,
            cell_size
        );

        draw_snake(
            &window,
            game.snake,
            game.snake_view,
            offset_x,
            offset_y,
            cell_size,
            game.mouth_open
        );

        update_title(&window, &game);

        refresh_window(&window);

        // The open mouth only lasts one rendered frame after food detection.
        game.mouth_open = false;

        SDL_Delay(10);
    }

    free_game(&game);
    close_window(&window);

    return 0;
}
