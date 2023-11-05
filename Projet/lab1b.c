/*
 * lab1b.c
 *
 *  Created on:
 *      Author:
 */
#include <stdio.h>
#include <unistd.h>

/* include helper functions for game */
#include "lifegame.h"

/* add whatever other includes here */

/* number of generations to evolve the world */
#define NUM_GENERATIONS 50

/* functions to implement -- can copy from Part A */

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

int main(int argc, char ** argv)
{
    char filename[256];  // We suppose that the filename is under 256 character

    int file_exists = 0;
    while (!file_exists) {
        // We add only the filename, without the extension
        printf("Enter the file name (without extension) : ");
        scanf("%s", filename);
        strcat(filename, ".txt");

        // We check if the file exist
        if (access(filename, F_OK) != -1) {
            file_exists = 1;
        } else {
            printf("Le fichier n'existe pas. Veuillez réessayer.\n");
        }
    }

    // Load the initial state of the world with the file
    initialize_world_from_file(filename);

    // Here, we select the number of generation enter by the user
    int num_generations = NUM_GENERATIONS;

    printf("Entrez le nombre de générations (appuyez sur Entrée pour utiliser la valeur par défaut) : ");
    int input_generations;
    if (scanf("%d", &input_generations) == 1) {
        num_generations = input_generations;
    }

    for (int n = 0; n < num_generations; n++) {
        next_generation();
        // Optional : in the console we can see the world
        output_world();
    }

    // We save the final state of the world in this file : "world.txt"
    save_world_to_file("world.txt");

    return 0;
}

// This method allow us to update the world when we change generation
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

// This method allow us to see which cell is alive or dead
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

// This method give us the number of neighbors around a cell
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