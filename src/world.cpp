#include "world.hpp"

// Allocates and initializes a world filled with EMPTY cells.
void init_world(World* world, int width, int height) {
    world->width = width;
    world->height = height;
    world->grid = new Food[width * height];

    for (int i = 0; i < width * height; i++) {
        world->grid[i] = EMPTY;
    }
}

// Frees the dynamically allocated world grid.
void free_world(World* world) {
    delete[] world->grid;
    world->grid = nullptr;
    world->width = 0;
    world->height = 0;
}

// Returns true when coordinates are inside the world.
bool in_world(World* world, int x, int y) {
    return x >= 0 && x < world->width &&
           y >= 0 && y < world->height;
}

// Reads the food stored at coordinates (x, y).
Food read_world(World* world, int x, int y) {
    if (!in_world(world, x, y)) {
        return EMPTY;
    }

    return world->grid[y * world->width + x];
}

// Writes a food value at coordinates (x, y).
void write_world(World* world, int x, int y, Food food) {
    if (!in_world(world, x, y)) {
        return;
    }

    world->grid[y * world->width + x] = food;
}
