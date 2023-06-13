#ifndef __LETTER_MASK_H__
#define __LETTER_MASK_H__

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t letter_mask_t;

#define HEIGHT (5)
#define WIDTH (5)
#define NUM_LETTERS (HEIGHT * WIDTH)

#define NUM_BITS (32)
#define MSB(x) (x >> 31)

//                                      row 1 row2  row3  row4  row5  unused
#define BOARD_ZEROS (0x00000000)     // 00000 00000 00000 00000 00000 0000000
#define BOARD_ONES (0XFFFFFF80)      // 11111 11111 11111 11111 11111 0000000
#define FIRST_ROW_SET (0xF8000000)   // 11111 00000 00000 00000 00000 0000000
#define LAST_ROW_SET (0x00000F80)    // 00000 00000 00000 00000 11111 0000000
#define FIRST_COL_SET (0x84210800)   // 10000 10000 10000 10000 10000 0000000
#define LAST_COL_SET (0x08421080)    // 00001 00001 00001 00001 00001 0000000
#define FIRST_CELL_SET (FIRST_COL_SET & FIRST_ROW_SET)

void print_bitmask(letter_mask_t mask);

// ################################ QUESTION 1 ################################
bool get_bit_value(letter_mask_t mask, int row, int col);

// ################################ QUESTION 2 ################################
void set_bit_value(letter_mask_t *mask, int row, int col, bool value);

// ################################ QUESTION 3 ################################
void set_all_bits(letter_mask_t *mask, bool value);

// ################################ QUESTION 4 ################################
bool is_free_letter(letter_mask_t mask);

// ################################ QUESTION 5 ################################
bool get_fixed_letter_pos(letter_mask_t mask, int *row, int *col);

// ################################ QUESTION 6 ################################
void intersect_neighbourhoods(letter_mask_t *fst, letter_mask_t *snd);

#endif  // __LETTER_MASK_H__
