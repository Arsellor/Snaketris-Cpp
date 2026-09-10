#include "view.hpp"

// Returns true when all pointers in a WorldView were loaded.
bool init_world_view(WorldView* view, Window* window) {
    view->background = nullptr;
    view->red = nullptr;
    view->green = nullptr;
    view->blue = nullptr;
    view->star = nullptr;
    view->background = load_texture(window, "img/background.bmp");
    view->red = load_texture(window, "img/food_red.bmp");
    view->green = load_texture(window, "img/food_green.bmp");
    view->blue = load_texture(window, "img/food_blue.bmp");
    view->star = load_texture(window, "img/food_star.bmp");

    return view->background != nullptr &&
           view->red != nullptr &&
           view->green != nullptr &&
           view->blue != nullptr &&
           view->star != nullptr;
}

// Loads the textures used by the snake.
bool init_snake_view(SnakeView* view, Window* window) {
    view->body_red = nullptr;
    view->body_green = nullptr;
    view->body_blue = nullptr;
    view->head_north_closed = nullptr;
    view->head_south_closed = nullptr;
    view->head_west_closed = nullptr;
    view->head_east_closed = nullptr;
    view->head_north_open = nullptr;
    view->head_south_open = nullptr;
    view->head_west_open = nullptr;
    view->head_east_open = nullptr;
    view->body_red = load_texture(window, "img/body_red.bmp");
    view->body_green = load_texture(window, "img/body_green.bmp");
    view->body_blue = load_texture(window, "img/body_blue.bmp");

    view->head_north_closed = load_texture(window, "img/head_north_closed.bmp");
    view->head_south_closed = load_texture(window, "img/head_south_closed.bmp");
    view->head_west_closed = load_texture(window, "img/head_west_closed.bmp");
    view->head_east_closed = load_texture(window, "img/head_east_closed.bmp");

    view->head_north_open = load_texture(window, "img/head_north_open.bmp");
    view->head_south_open = load_texture(window, "img/head_south_open.bmp");
    view->head_west_open = load_texture(window, "img/head_west_open.bmp");
    view->head_east_open = load_texture(window, "img/head_east_open.bmp");

    return view->body_red != nullptr &&
           view->body_green != nullptr &&
           view->body_blue != nullptr &&
           view->head_north_closed != nullptr &&
           view->head_south_closed != nullptr &&
           view->head_west_closed != nullptr &&
           view->head_east_closed != nullptr &&
           view->head_north_open != nullptr &&
           view->head_south_open != nullptr &&
           view->head_west_open != nullptr &&
           view->head_east_open != nullptr;
}

// Destroys all textures stored in a WorldView.
void free_world_view(WorldView* view) {
    SDL_DestroyTexture(view->background);
    SDL_DestroyTexture(view->red);
    SDL_DestroyTexture(view->green);
    SDL_DestroyTexture(view->blue);
    SDL_DestroyTexture(view->star);

    view->background = nullptr;
    view->red = nullptr;
    view->green = nullptr;
    view->blue = nullptr;
    view->star = nullptr;
}

// Destroys all textures stored in a SnakeView.
void free_snake_view(SnakeView* view) {
    SDL_DestroyTexture(view->body_red);
    SDL_DestroyTexture(view->body_green);
    SDL_DestroyTexture(view->body_blue);

    SDL_DestroyTexture(view->head_north_closed);
    SDL_DestroyTexture(view->head_south_closed);
    SDL_DestroyTexture(view->head_west_closed);
    SDL_DestroyTexture(view->head_east_closed);

    SDL_DestroyTexture(view->head_north_open);
    SDL_DestroyTexture(view->head_south_open);
    SDL_DestroyTexture(view->head_west_open);
    SDL_DestroyTexture(view->head_east_open);
}

// Draws the complete world grid.
void draw_world(Window* window, World* world, WorldView* view,
                int offset_x, int offset_y, int cell_size) {
    for (int y = 0; y < world->height; y++) {
        for (int x = 0; x < world->width; x++) {
            int px = offset_x + x * cell_size;
            int py = offset_y + y * cell_size;

            draw_texture(window, view->background, px, py, cell_size, cell_size);

            Food food = read_world(world, x, y);

            if (food == FOOD_RED) {
                draw_texture(window, view->red, px, py, cell_size, cell_size);
            } else if (food == FOOD_GREEN) {
                draw_texture(window, view->green, px, py, cell_size, cell_size);
            } else if (food == FOOD_BLUE) {
                draw_texture(window, view->blue, px, py, cell_size, cell_size);
            } else if (food == FOOD_STAR) {
                draw_texture(window, view->star, px, py, cell_size, cell_size);
            }
        }
    }
}

// Selects a body texture according to the ring color.
static SDL_Texture* body_texture(SnakeView* view, Food food) {
    if (food == FOOD_RED) return view->body_red;
    if (food == FOOD_GREEN) return view->body_green;
    return view->body_blue;
}

// Selects a head texture according to direction and mouth state.
static SDL_Texture* head_texture(SnakeView* view, Direction direction, bool mouth_open) {
    if (!mouth_open) {
        if (direction == NORTH) return view->head_north_closed;
        if (direction == SOUTH) return view->head_south_closed;
        if (direction == WEST) return view->head_west_closed;
        return view->head_east_closed;
    }

    if (direction == NORTH) return view->head_north_open;
    if (direction == SOUTH) return view->head_south_open;
    if (direction == WEST) return view->head_west_open;
    return view->head_east_open;
}

// Draws the snake with textures and its current direction.
void draw_snake(Window* window, Snake* snake, SnakeView* view,
                int offset_x, int offset_y, int cell_size, bool mouth_open) {
    Ring* current = snake->first;

    while (current != nullptr) {
        int px = offset_x + current->x * cell_size;
        int py = offset_y + current->y * cell_size;

        draw_texture(
            window,
            body_texture(view, current->food),
            px, py, cell_size, cell_size
        );

        current = current->next;
    }

    int head_px = offset_x + snake->head_x * cell_size;
    int head_py = offset_y + snake->head_y * cell_size;

    draw_texture(
        window,
        head_texture(view, snake->direction, mouth_open),
        head_px, head_py, cell_size, cell_size
    );
}

// Draws one seven-segment digit.
static void draw_digit(Window* window, int digit, int x, int y, int scale) {
    static const int segments[10][7] = {
        {1,1,1,1,1,1,0}, {0,1,1,0,0,0,0},
        {1,1,0,1,1,0,1}, {1,1,1,1,0,0,1},
        {0,1,1,0,0,1,1}, {1,0,1,1,0,1,1},
        {1,0,1,1,1,1,1}, {1,1,1,0,0,0,0},
        {1,1,1,1,1,1,1}, {1,1,1,1,0,1,1}
    };

    int t = scale;
    int l = scale * 3;

    if (digit < 0 || digit > 9) return;

    if (segments[digit][0]) draw_fill_rectangle(window, x+t, y, l, t);
    if (segments[digit][1]) draw_fill_rectangle(window, x+l+t, y+t, t, l);
    if (segments[digit][2]) draw_fill_rectangle(window, x+l+t, y+l+2*t, t, l);
    if (segments[digit][3]) draw_fill_rectangle(window, x+t, y+2*l+2*t, l, t);
    if (segments[digit][4]) draw_fill_rectangle(window, x, y+l+2*t, t, l);
    if (segments[digit][5]) draw_fill_rectangle(window, x, y+t, t, l);
    if (segments[digit][6]) draw_fill_rectangle(window, x+t, y+l+t, l, t);
}

// Draws a non-negative integer with seven-segment digits.
void draw_number(Window* window, int value, int x, int y, int scale) {
    if (value < 0) value = 0;

    int digits[10];
    int count = 0;

    if (value == 0) {
        digits[count++] = 0;
    }

    while (value > 0 && count < 10) {
        digits[count++] = value % 10;
        value /= 10;
    }

    for (int i = count - 1; i >= 0; i--) {
        draw_digit(window, digits[i], x + (count - 1 - i) * scale * 6, y, scale);
    }
}
