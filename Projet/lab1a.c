/*
 * lab1a.c
 *
 *  Created on:
 *      Author:
 */

/* include helper functions for game */
#include "lifegame.h"
#include <unistd.h>

/* add whatever other includes here */

/* number of generations to evolve the world */
#define NUM_GENERATIONS 50

/* functions to implement */

/* this function should set the state of all
   the cells in the next generation and call
   finalize_evolution() to update the current
   state of the world to the next generation */
void next_generation(void);

/* this function should return the state of the cell
   at (x,y) in the next generation, according to the
   rules of Conway's Game of Life (see handout) */
int get_next_state(int x, int y);

/* this function should calculate the number of alive
   neighbors of the cell at (x,y) */
int num_neighbors(int x, int y);

int main() {
    int n;

    initialize_world();  /* Initialiser le monde */

    for (n = 0; n < NUM_GENERATIONS; n++) {
        next_generation(); /* Évolution d'une génération à l'autre */
        output_world(); /* Afficher le monde */
        usleep(500000);
    }

    output_world(); /* Afficher l'état final du monde */

    return 0;
}


void next_generation(void) {
    int x, y;
    for (x = 0; x < get_world_width(); x++) {
        for (y = 0; y < get_world_height(); y++) {
            int next_state = get_next_state(x, y);
            set_cell_state(x, y, next_state);
        }
    }
    finalize_evolution();
}

int get_next_state(int x, int y) {
    int current_state = get_cell_state(x, y);
    int alive_neighbors = num_neighbors(x, y);

    if (current_state == ALIVE) {
        if (alive_neighbors < 2 || alive_neighbors > 3) {
            return DEAD;
        } else {
            return ALIVE;
        }
    } else {
        if (alive_neighbors == 3) {
            return ALIVE;
        } else {
            return DEAD;
        }
    }
}

int num_neighbors(int x, int y) {
    int alive_count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int neighbor_x = x + i;
            int neighbor_y = y + j;
            if (neighbor_x >= 0 && neighbor_x < get_world_width() && neighbor_y >= 0 && neighbor_y < get_world_height()) {
                if (get_cell_state(neighbor_x, neighbor_y) == ALIVE) {
                    alive_count++;
                }
            }
        }
    }
    return alive_count;
}
