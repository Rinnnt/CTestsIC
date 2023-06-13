#ifndef __LASER_H__
#define __LASER_H__

#include <stdbool.h>
#include <stdio.h>

// Board ASCII art:
#define START '>'
#define END '@'
#define EDGE '#'
#define FWD_MIRROR '/'
#define BWD_MIRROR '\\'
#define CHOICE '?'
#define HORIZ_LASER '-'
#define VERT_LASER '|'
#define CROSS_LASER '+'
#define EMPTY ' '

// Aggregate groups of ASCII art by meaning. You might find them useful.
#define MIRRORS "\\/"
#define CHOICES "\\/ "
#define PASSTHROUGHS "-|+ "
#define BLOCKERS "?@#>"

#define MAX_MSG_LEN 32

typedef struct {
    int height;
    int width;
    char **cells;
} board_t;

typedef enum { EAST, SOUTH, WEST, NORTH } direction_t;

typedef struct {
    int row;
    int col;
    direction_t direction;
    char msg[MAX_MSG_LEN];
} laser_state_t;

#define print_board(board) for (int i = 0; i < (board).height; i++) printf("%s\n", (board).cells[i])

// Part A
// Question 1
// Return true only if (row, col) is within the board's bounds.
bool is_on_board(board_t board, int row, int col);

// Question 2
// Return the row index of '>' (aka. START) from the first column of the board.
// If not found, return -1.
int find_start(board_t board);

// Question 3
// Return the letter adjacent to the mirror at (row, col).
// If the cell is not one of MIRRORS or there is no letter you must return '\0'
char get_mirror_label(board_t board, int row, int col);

// Question 4
// Return board loaded from file. Read height & width dimensions first, then the board.
board_t load_board(const char *filename);

// Question 5
// Free the memory allocated to the board's cells.
void free_cells(board_t board);

// Part B
// Question 1
// If cell is one of MIRRORS, return changed direction, otherwise return direction unchanged.
direction_t change_direction(direction_t direction, char cell);

// Question 2
// Update the laser properties in the following order: direction, message, (row, col).
// Return the new cell the laser just entered.
char step_laser(board_t board, laser_state_t *laser);

// Question 3
// Step the laser as far as possible, before hitting one of BLOCKERS.
// Don't change the board unless trace parameter is true, in which case,
// update the cells of the board to draw the laser ray (take care with ray crossings).
// Return true if laser ends up in an ABSORBER, otherwise false.
bool shoot(board_t board, laser_state_t *laser, bool trace);

// Question 4
// Fill in the CHOICE cells with one of CHOICES s.t. shooting the laser from
// beginning spells out the target message. Return true if this is possible, otherwise false.
bool solve(board_t board, laser_state_t laser, const char target[MAX_MSG_LEN]);

#endif // __LASER_H__
