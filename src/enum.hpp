#ifndef ENUM_HPP
#define ENUM_HPP

// Directions used by the snake head.
enum Direction {
    NORTH,
    SOUTH,
    WEST,
    EAST
};

// Food types stored in the world grid.
enum Food {
    EMPTY,
    FOOD_RED,
    FOOD_GREEN,
    FOOD_BLUE,
    FOOD_STAR
};

#endif
