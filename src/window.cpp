#include "window.hpp"

// Initializes SDL and creates a window and renderer.
bool init_window(Window* window, int width, int height, string title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "Erreur SDL_Init : " << SDL_GetError() << endl;
        return false;
    }

    window->width = width;
    window->height = height;
    window->sdl_window = nullptr;
    window->sdl_renderer = nullptr;

    int result = SDL_CreateWindowAndRenderer(
        width, height, SDL_WINDOW_SHOWN,
        &window->sdl_window, &window->sdl_renderer
    );

    if (result < 0) {
        cerr << "Erreur creation fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        return false;
    }

    SDL_SetWindowTitle(window->sdl_window, title.c_str());
    SDL_SetRenderDrawBlendMode(window->sdl_renderer, SDL_BLENDMODE_BLEND);
    return true;
}

// Releases the SDL resources owned by the window.
void close_window(Window* window) {
    if (window->sdl_renderer != nullptr) {
        SDL_DestroyRenderer(window->sdl_renderer);
        window->sdl_renderer = nullptr;
    }

    if (window->sdl_window != nullptr) {
        SDL_DestroyWindow(window->sdl_window);
        window->sdl_window = nullptr;
    }

    SDL_Quit();
}

// Sets an SDL color from RGBA integer components.
void set_color(SDL_Color* color, int r, int g, int b, int a) {
    color->r = (Uint8)r;
    color->g = (Uint8)g;
    color->b = (Uint8)b;
    color->a = (Uint8)a;
}

// Clears the renderer with the window background color.
void clear_window(Window* window) {
    SDL_SetRenderDrawColor(
        window->sdl_renderer,
        window->background.r,
        window->background.g,
        window->background.b,
        window->background.a
    );
    SDL_RenderClear(window->sdl_renderer);
}

// Draws a filled rectangle using the foreground color.
void draw_fill_rectangle(Window* window, int x, int y, int w, int h) {
    SDL_SetRenderDrawColor(
        window->sdl_renderer,
        window->foreground.r,
        window->foreground.g,
        window->foreground.b,
        window->foreground.a
    );

    SDL_Rect rectangle = {x, y, w, h};
    SDL_RenderFillRect(window->sdl_renderer, &rectangle);
}

// Draws the outline of a rectangle using the foreground color.
void draw_rectangle(Window* window, int x, int y, int w, int h) {
    SDL_SetRenderDrawColor(
        window->sdl_renderer,
        window->foreground.r,
        window->foreground.g,
        window->foreground.b,
        window->foreground.a
    );

    SDL_Rect rectangle = {x, y, w, h};
    SDL_RenderDrawRect(window->sdl_renderer, &rectangle);
}

// Draws an SDL texture in a destination rectangle.
void draw_texture(Window* window, SDL_Texture* texture, int x, int y, int w, int h) {
    if (texture == nullptr) {
        return;
    }

    SDL_Rect destination = {x, y, w, h};
    SDL_RenderCopy(window->sdl_renderer, texture, nullptr, &destination);
}

// Loads a BMP file and converts it to an SDL texture.
SDL_Texture* load_texture(Window* window, string filename) {
    SDL_Surface* surface = SDL_LoadBMP(filename.c_str());

    if (surface == nullptr) {
        cerr << "Impossible de charger " << filename
             << " : " << SDL_GetError() << endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(
        window->sdl_renderer, surface
    );

    SDL_FreeSurface(surface);

    if (texture == nullptr) {
        cerr << "Impossible de creer la texture " << filename
             << " : " << SDL_GetError() << endl;
    }

    return texture;
}

// Presents the renderer.
void refresh_window(Window* window) {
    SDL_RenderPresent(window->sdl_renderer);
}
