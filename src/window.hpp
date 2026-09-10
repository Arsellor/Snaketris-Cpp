#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

using namespace std;

// Stores the SDL window, renderer, dimensions and drawing colors.
struct Window {
    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;
    int width;
    int height;
    SDL_Color background;
    SDL_Color foreground;
};

// Initializes SDL and creates a window and renderer.
bool init_window(Window* window, int width, int height, string title);

// Releases the SDL resources owned by the window.
void close_window(Window* window);

// Sets an SDL color from RGBA integer components.
void set_color(SDL_Color* color, int r, int g, int b, int a);

// Clears the renderer with the window background color.
void clear_window(Window* window);

// Draws a filled rectangle using the foreground color.
void draw_fill_rectangle(Window* window, int x, int y, int w, int h);

// Draws the outline of a rectangle using the foreground color.
void draw_rectangle(Window* window, int x, int y, int w, int h);

// Draws an SDL texture in a destination rectangle.
void draw_texture(Window* window, SDL_Texture* texture, int x, int y, int w, int h);

// Loads a BMP file and converts it to an SDL texture.
SDL_Texture* load_texture(Window* window, string filename);

// Presents the renderer.
void refresh_window(Window* window);

#endif
