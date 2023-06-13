#ifndef __GOGEN_H__
#define __GOGEN_H__

#include "letter_mask.h"

typedef char board_t[HEIGHT][WIDTH];

void parse_gogen_file(const char *filename, board_t board, char ***words_ptr);
void print_board(board_t board);

// ################################ QUESTION 1 ################################
bool get_letter_position(board_t board, char letter, int *row, int *col);

// ################################ QUESTION 2 ################################
bool valid_solution(board_t board, char **words);

// ################################ QUESTION 3 ################################
void update(board_t board, letter_mask_t masks[NUM_LETTERS]);

// ################################ QUESTION 4 ################################
bool solve_board(board_t board, char **words);

// ################################ QUESTION 5 ################################
// Solve the gogen board from gogen-challenger.txt
#endif  // __GOGEN_H__
