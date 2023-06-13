#include "letter_mask.h"

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


int asserts_ran = 0, asserts_failed = 0, tests_ran = 0, tests_failed = 0;

#define assert_str_eq(a, b) do { asserts_ran++; if (a == NULL || strcmp((a), (b)) != 0) { printf("%s(%d): got: %s | expected: %s\n", __func__, __LINE__, a, b); asserts_failed++; } } while (0)

#define assert_eq(a, b) do { asserts_ran++; if ((a) != (b)) { printf("%s(line %d): got: %d | expected: %d\n", __func__, __LINE__, a, b); asserts_failed++;} } while (0)

#define assert_ptr_isnull(p) do { asserts_ran++; if (p != NULL) { printf("%s(line %d): got: %p | expected NULL\n", __func__, __LINE__, p); asserts_failed++; } } while (0)

#define assert_ptr_notnull(p) do { asserts_ran++; if (p == NULL) { printf("%s(line %d): pointer should not be NULL\n", __func__, __LINE__); asserts_failed++; return;} } while (0)

#define PTR_CHECK(ptr, msg) if (!(ptr)) perror(msg), exit(EXIT_FAILURE)
#define MAX_LINE_LENGTH (512)

#define run_test(test) do { \
asserts_ran = asserts_failed = 0; test(); \
tests_ran++;\
if (asserts_failed > 0) { \
tests_failed++; \
 printf("****%s: %d asserts failed out of %d asserts\n\n", #test, asserts_failed, asserts_ran); \
 }\
} while (0)

void test_get_bit_value() {
    assert_eq(get_bit_value(FIRST_CELL_SET, 0, 0), true);
    assert_eq(get_bit_value(FIRST_CELL_SET >> 1, 0, 0), false);
    assert_eq(get_bit_value(FIRST_CELL_SET >> 4, 0, 4), true);
    assert_eq(get_bit_value(LAST_COL_SET & LAST_ROW_SET, 4, 4), true);
    assert_eq(get_bit_value(LAST_COL_SET, 3, 4), true);
    assert_eq(get_bit_value(LAST_COL_SET, 3, 2), false);
}

void test_set_bit_value() {
    letter_mask_t mask = 0;

    set_bit_value(&mask, 0, 0, true);
    assert_eq(mask, FIRST_CELL_SET);

    mask = FIRST_COL_SET;
    set_bit_value(&mask, 0, 0, false);
    assert_eq(mask, FIRST_COL_SET ^ FIRST_CELL_SET);

    mask = BOARD_ONES;
    set_bit_value(&mask, 2, 2, false);
    assert_eq(mask, BOARD_ONES ^ (FIRST_CELL_SET >> 12));

    mask = BOARD_ONES;
    set_bit_value(&mask, 2, 2, true);
    assert_eq(mask, BOARD_ONES);
}

void test_set_all_bits() {
    letter_mask_t mask = 0;

    set_all_bits(&mask, true);
    assert_eq(mask, BOARD_ONES);

    mask = 242342342;
    set_all_bits(&mask, false);
    assert_eq(mask, 0);

    mask = BOARD_ONES;
    set_all_bits(&mask, false);
    assert_eq(mask, 0);

    mask = BOARD_ONES;
    set_all_bits(&mask, true);
    assert_eq(mask, BOARD_ONES);
}

void test_is_free_letter() {
    assert_eq(is_free_letter(0), false);
    assert_eq(is_free_letter(BOARD_ONES), true);
    assert_eq(is_free_letter(FIRST_CELL_SET | (FIRST_CELL_SET >> 1)), true);
    assert_eq(is_free_letter(FIRST_CELL_SET >> 8), false);
}

void test_get_fixed_letter_pos() {
    int row, col = 0;

    assert_eq(get_fixed_letter_pos(FIRST_CELL_SET | (FIRST_CELL_SET >> 1), &row, &col), false);

    assert_eq(get_fixed_letter_pos(FIRST_CELL_SET, &row, &col), true);
    assert_eq(row, 0);
    assert_eq(col, 0);


    assert_eq(get_fixed_letter_pos(FIRST_CELL_SET >> 13, &row, &col), true);
    assert_eq(row, 2);
    assert_eq(col, 3);

    assert_eq(get_fixed_letter_pos(FIRST_CELL_SET | (FIRST_CELL_SET >> 13), &row, &col), false);
}

void test_intersect_neighbourhoods() {
    letter_mask_t fst, snd = 0;

    fst = FIRST_CELL_SET;
    snd = FIRST_CELL_SET >> 12;

    intersect_neighbourhoods(&fst, &snd);
    assert_eq(fst, 0);
    assert_eq(snd, 0);

    fst = FIRST_CELL_SET;
    snd = FIRST_CELL_SET >> 6;

    intersect_neighbourhoods(&fst, &snd);
    assert_eq(fst, FIRST_CELL_SET);
    assert_eq(snd, FIRST_CELL_SET >> 6);

    fst = FIRST_CELL_SET;
    snd = (FIRST_CELL_SET >> 6) | LAST_ROW_SET;

    intersect_neighbourhoods(&fst, &snd);
    assert_eq(fst, FIRST_CELL_SET);
    assert_eq(snd, FIRST_CELL_SET >> 6);

    fst = 0x10800;         // 00000 00000 00000 10000 10000 0000000
    snd = 0x8400 | 0x4200; //  00000 00000 00000 01100 01100 0000000
    intersect_neighbourhoods(&fst, &snd);
    assert_eq(fst, 0x10800); // 00000 00000 00000 01000 01000 0000000
    assert_eq(snd, 0x8400); // 00000 00000 00000 01000 01000 0000000
}

void run_part_a() {
    tests_ran = 0;
    tests_failed = 0;

    run_test(test_get_bit_value);
    run_test(test_set_bit_value);
    run_test(test_set_all_bits);
    run_test(test_is_free_letter);
    run_test(test_get_fixed_letter_pos);
    run_test(test_intersect_neighbourhoods);

    if (tests_failed == 0) {
        printf("********************\n"
               "Part A -- WELL DONE!\n"
               "********************\n");
    } else {
        printf("****************************************************\n"
               "Part A has %d incorrect functions out of %d tested\n"
               "****************************************************\n\n",
               tests_failed, tests_ran);
    }
}

int main(void) {
    run_part_a();
    return EXIT_SUCCESS;
}
