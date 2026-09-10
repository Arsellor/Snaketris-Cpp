#ifndef WORLD_HPP
#define WORLD_HPP

#include <iostream>
#include <string>
#include "enum.hpp"

using namespace std;

// Represents the rectangular world and its dynamically allocated food grid.
struct World {
    int width;
    int height;
    Food* grid;
};

// Allocates and initializes a world filled with EMPTY cells.
void init_world(World* world, int width, int height);

// Frees the dynamically allocated world grid.
void free_world(World* world);

// Returns true when coordinates are inside the world.
bool in_world(World* world, int x, int y);

// Reads the food stored at coordinates (x, y).
Food read_world(World* world, int x, int y);

// Writes a food value at coordinates (x, y).
void write_world(World* world, int x, int y, Food food);

#endif
