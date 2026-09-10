#include "snake.hpp"

// Initializes a snake containing only its head.
void init_snake(Snake* snake, int x, int y) {
    snake->head_x = x;
    snake->head_y = y;
    snake->direction = EAST;
    snake->first = nullptr;
    snake->last = nullptr;
}

// Frees every ring of the doubly linked list.
void free_snake(Snake* snake) {
    Ring* current = snake->first;

    while (current != nullptr) {
        Ring* next = current->next;
        delete current;
        current = next;
    }

    snake->first = nullptr;
    snake->last = nullptr;
}

// Changes direction while preventing an immediate U-turn.
void change_direction(Snake* snake, Direction direction) {
    if (snake->direction == NORTH && direction == SOUTH) return;
    if (snake->direction == SOUTH && direction == NORTH) return;
    if (snake->direction == EAST && direction == WEST) return;
    if (snake->direction == WEST && direction == EAST) return;

    snake->direction = direction;
}

// Moves the body rings so each one follows its predecessor.
void move_rings(Snake* snake, int old_head_x, int old_head_y) {
    int previous_x = old_head_x;
    int previous_y = old_head_y;

    Ring* current = snake->first;

    while (current != nullptr) {
        int old_x = current->x;
        int old_y = current->y;

        current->x = previous_x;
        current->y = previous_y;

        previous_x = old_x;
        previous_y = old_y;

        current = current->next;
    }
}

// Moves the snake head one cell and updates its body.
void move_snake(Snake* snake) {
    int old_head_x = snake->head_x;
    int old_head_y = snake->head_y;

    if (snake->direction == NORTH) snake->head_y--;
    if (snake->direction == SOUTH) snake->head_y++;
    if (snake->direction == WEST) snake->head_x--;
    if (snake->direction == EAST) snake->head_x++;

    move_rings(snake, old_head_x, old_head_y);
}

// Adds a colored ring at the end of the snake body.
void add_ring(Snake* snake, Food food) {
    Ring* ring = new Ring;
    ring->food = food;
    ring->next = nullptr;
    ring->previous = snake->last;

    if (snake->last == nullptr) {
        ring->x = snake->head_x;
        ring->y = snake->head_y;
        snake->first = ring;
        snake->last = ring;
    } else {
        ring->x = snake->last->x;
        ring->y = snake->last->y;
        snake->last->next = ring;
        snake->last = ring;
    }
}

// Returns true when a ring occupies coordinates (x, y).
bool snake_contains(Snake* snake, int x, int y) {
    if (snake->head_x == x && snake->head_y == y) {
        return true;
    }

    Ring* current = snake->first;

    while (current != nullptr) {
        if (current->x == x && current->y == y) {
            return true;
        }
        current = current->next;
    }

    return false;
}

// Returns true when the head touches its body.
bool snake_touches_body(Snake* snake) {
    Ring* current = snake->first;

    while (current != nullptr) {
        if (current->x == snake->head_x &&
            current->y == snake->head_y) {
            return true;
        }
        current = current->next;
    }

    return false;
}

// Counts the number of body rings.
int snake_length(Snake* snake) {
    int length = 0;
    Ring* current = snake->first;

    while (current != nullptr) {
        length++;
        current = current->next;
    }

    return length;
}

// Removes the middle ring of the first triple of equal consecutive colors.
bool remove_tetris_ring(Snake* snake) {
    Ring* left = snake->first;

    while (left != nullptr &&
           left->next != nullptr &&
           left->next->next != nullptr) {

        Ring* middle = left->next;
        Ring* right = middle->next;

        if (left->food == middle->food &&
            middle->food == right->food &&
            left->food != FOOD_STAR) {

            left->next = right;
            right->previous = left;

            if (snake->last == middle) {
                snake->last = left;
            }

            delete middle;
            return true;
        }

        left = left->next;
    }

    return false;
}
