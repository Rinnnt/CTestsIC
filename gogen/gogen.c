#include "gogen.h"
#include "letter_mask.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

// ################################## PART B ##################################

#define PTR_CHECK(ptr, msg) if (!(ptr)) perror(msg), exit(EXIT_FAILURE)
#define MAX_LINE_LENGTH (512)

void parse_gogen_file(const char *filename, board_t board, char ***words_ptr) {
    FILE *file = fopen(filename, "r");
    PTR_CHECK(file, "File could not be opened!");

    // Parse board
    for (int r = 0; r < HEIGHT; ++r) {
        for (int c = 0; c < WIDTH; ++c) {
            assert(fscanf(file, " %c", &board[r][c]) == 1);
            if (board[r][c] != '.') {
                assert(board[r][c] >= 'A' && board[r][c] <= 'Y');
            }
        }
    }

    // Parse number of words
    int num_words;
    assert(fscanf(file, "%d\r\n", &(num_words)) == 1);

    // Parse words as a NULL terminated array of strings
    char **words = calloc(num_words + 1, sizeof(char*));
    PTR_CHECK(words, "Could not allocate memory for word pointers!");
    for (int i = 0; i < num_words; i++) {
        char buffer[MAX_LINE_LENGTH];
        assert(fscanf(file, "%s\r\n", buffer) == 1);
        words[i] = calloc(strlen(buffer) + 1, sizeof(char));
        PTR_CHECK(words[i], "Could not allocate memory for word!");
        strcpy(words[i], buffer);
    }
    *words_ptr = words;
}

void free_null_terminated_array(char **words) {
    for (int i = 0; words[i]; i++)
        free(words[i]);
    free(words);
}

void print_board(board_t board) {
    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            printf("%c ", board[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_words(char **words) {
    for (int i = 0; words[i]; i++)
        printf("%s\n", words[i]);
}

void copy_board(board_t dest, board_t src) {
    for (int r = 0; r < HEIGHT; r++)
        for (int c = 0; c < WIDTH; c++)
            dest[r][c] = src[r][c];
}

// ################################ QUESTION 1 ################################
bool get_letter_position(board_t board, char letter, int *row, int *col) {
    return false;
}

// ################################ QUESTION 2 ################################
bool valid_solution(board_t board, char **words) {
    return false;
}

// ################################ QUESTION 3 ################################
void update(board_t board, letter_mask_t masks[NUM_LETTERS]) {
}

// ################################ QUESTION 4 ################################
bool solve_board(board_t board, char **words) {
    return false;
}

// ################################ QUESTION 5 ################################
// Write the solution to gogen-challenge.txt on the next lines! You are allowed
// to compute this manually if you didn't manage to get the code working.





// Solution to gogen-challenge.txt should be above!

#ifdef MAIN_GOGEN
int main (void) {
    board_t board;
    char **words;
    parse_gogen_file("gogen-easy.txt", board, &words);
    printf("Here is the easy gogen puzzle from Figure 1:\n");
    print_board(board);
    if (solve_board(board, words)) {
        printf("\nSolved!\n");
        print_board(board);
    } else {
        printf("\nImpossible!\n");
    }
    free_null_terminated_array(words);

    parse_gogen_file("gogen-challenge.txt", board, &words);
    printf("Here is a more challenging gogen puzzle:\n");
    print_board(board);
    if (solve_board(board, words)) {
        printf("\nSolved!\n");
        print_board(board);
    } else {
        printf("\nImpossible!\n");
    }
    free_null_terminated_array(words);
    return 0;
}
#endif
