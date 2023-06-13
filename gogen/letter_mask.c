#include "letter_mask.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
// ################################## PART A ##################################

void print_bitmask(letter_mask_t mask) {
    for (int row = 0; row < HEIGHT; ++row) {
        printf("row %d: ", row);
        for (int col = 0; col < WIDTH; ++col) {
            printf("%d ", MSB(mask));
            mask = mask << 1;
        }
        printf("\n");
    }
    printf("unused: ");
    for (int i = HEIGHT * WIDTH; i < NUM_BITS; i++) {
        printf("%d", MSB(mask));
        mask = mask << 1;
    }
    printf("\n");
}

// ################################ QUESTION 1 ################################
bool get_bit_value(letter_mask_t mask, int row, int col) {
    return false;
}

// ################################ QUESTION 2 ################################
void set_bit_value(letter_mask_t *mask, int row, int col, bool value) {
}

// ################################ QUESTION 3 ################################
void set_all_bits(letter_mask_t *mask, bool value) {
}

// ################################ QUESTION 4 ################################
bool is_free_letter(letter_mask_t mask) {
    return false;
}

// ################################ QUESTION 5 ################################
bool get_fixed_letter_pos(letter_mask_t mask, int *row, int *col) {
    return false;
}

// ################################ QUESTION 6 ################################
void intersect_neighbourhoods(letter_mask_t *fst, letter_mask_t *snd) {
}

#ifdef MAIN_LETTER_MASK
int main(void) {
    print_bitmask(BOARD_ZEROS);
    print_bitmask(BOARD_ONES);
    print_bitmask(FIRST_ROW_SET);
    print_bitmask(LAST_ROW_SET);
    print_bitmask(FIRST_COL_SET);
    print_bitmask(LAST_COL_SET);
    print_bitmask(FIRST_CELL_SET);
    print_bitmask(0x8A88A8BA); // cross and 0111010 (0b10001010100010001010100010111010)
    print_bitmask(0x213E4257); // plus  and 1010111 (0b00100001001111100100001001010111)
    return 0;
}
#endif
