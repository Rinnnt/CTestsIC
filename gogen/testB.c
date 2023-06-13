#include "letter_mask.h"
#include "gogen.h"

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

void test_letter_position() {
    board_t board = { "G...W", "..B..", "..B..", "....A", "K...C" };
    int row, col;

    assert_eq(get_letter_position(board, 'G', &row, &col), true);
    assert_eq(row, 0);
    assert_eq(col, 0);

    assert_eq(get_letter_position(board, 'W', &row, &col), true);
    assert_eq(row, 0);
    assert_eq(col, 4);

    assert_eq(get_letter_position(board, 'B', &row, &col), true);
    assert_eq(row, 1);
    assert_eq(col, 2);

    assert_eq(get_letter_position(board, 'A', &row, &col), true);
    assert_eq(row, 3);
    assert_eq(col, 4);

    assert_eq(get_letter_position(board, 'K', &row, &col), true);
    assert_eq(row, 4);
    assert_eq(col, 0);

    assert_eq(get_letter_position(board, 'C', &row, &col), true);
    assert_eq(row, 4);
    assert_eq(col, 4);

    assert_eq(get_letter_position(board, 'E', &row, &col), false);
    assert_eq(get_letter_position(board, 'Z', &row, &col), false);
    assert_eq(get_letter_position(board, 'X', &row, &col), false);
    assert_eq(get_letter_position(board, 'F', &row, &col), false);
    assert_eq(get_letter_position(board, 'H', &row, &col), false);
    assert_eq(get_letter_position(board, 'J', &row, &col), false);
}

void test_valid_solution() {
    board_t solution_correct = { "NGWKR", "TICED", "SYXVB", "HUAOF", "QJMLP" };
    board_t solution_wrong1 = { "NGWKR", "TICED", "SVXYB", "HUAOF", "QJMLP" };
    board_t solution_wrong2 = { "NGWKR", "TICED", "SYXVB", "HUAOF", "QJMZP" };
    char *words[8] = { "BOXED", "FOAM", "JUSTICE", "MUSHY", "PLAYING", "QUAVER", "WICKED", NULL };

    assert_eq(valid_solution(solution_correct, words), true);

    assert_eq(valid_solution(solution_wrong1, words), false);

    assert_eq(valid_solution(solution_wrong2, words), false);
}

void test_update() {
    board_t board = { "G...W", ".....", ".....", ".....", "K...C" };
    letter_mask_t masks[NUM_LETTERS];

    for (int i = 0; i < NUM_LETTERS; i++) {
        set_all_bits(&masks[i], true);
    }

    set_all_bits(&masks['X' - 'A'], false);
    masks['X' - 'A'] |= FIRST_CELL_SET >> 6;

    update(board, masks);

    assert_eq(masks['G' - 'A'], FIRST_CELL_SET);
    assert_eq(masks['W' - 'A'], FIRST_ROW_SET & LAST_COL_SET);
    assert_eq(masks['K' - 'A'], LAST_ROW_SET & FIRST_COL_SET);
    assert_eq(masks['C' - 'A'], LAST_ROW_SET & LAST_COL_SET);
    assert_eq(board[1][1], 'X');
}

void test_solve_easy() {
    board_t board = { "N.W.R", ".....", "S.X.B", ".....", "Q.M.P" };

    char *words[14] = { "BOXED",
                        "FOAM",
                        "JUSTICE",
                        "MUSHY",
                        "PLAYING",
                        "QUAVER",
                        "WICKED", NULL };

    board_t solution = { "NGWKR", "TICED", "SYXVB", "HUAOF", "QJMLP" };

    assert_eq(solve_board(board, words), true);

    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            assert_eq(board[r][c], solution[r][c]);
        }
    }
}

void test_solve_medium() {
    board_t board = {
            "W.V.Y",
            ".....",
            "L.N.D",
            ".....",
            "F.X.S"
    };
    char *words[14] = {
            "AMPLE",
            "BIJOUX",
            "CLEF",
            "GRAIN",
            "HAT",
            "KELP",
            "NEXUS",
            "RAGE",
            "SQUID",
            "VANITY",
            "WRANGLE", NULL
    };

    board_t solution = {
            "WMVHY",
            "PRATB",
            "LGNID",
            "CEJUQ",
            "FKXOS"
    };

    assert_eq(solve_board(board, words), true);

    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            assert_eq(board[r][c], solution[r][c]);
        }
    }
}

void test_solve_hard() {
    board_t board = {
            "G...W",
            ".....",
            ".E.H.",
            ".....",
            "P...B"
    };
    char *words[14] = {
            "BALKERS",
            "CAHOW",
            "COLE",
            "FOCAL",
            "GRIM",
            "HADJ",
            "HALTERS",
            "LACY",
            "LAXER",
            "PUTS",
            "QUERIST",
            "TERM",
            "VALETS", NULL
    };

    board_t solution = {
            "GMFNW",
            "IRKOY",
            "SELHC",
            "UTXAD",
            "PQVJB"
    };

    assert_eq(solve_board(board, words), true);

    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            assert_eq(board[r][c], solution[r][c]);
        }
    }
}

void test_solve_challenge() {
    board_t board = { "G...W", ".....", ".....", ".....", "K...C" };
    char *words[14] = { "BYTE", "CLEF", "DEYS", "GONAD", "HADJ", "KHAT",
                        "MIRS","MOATED","MOTIVE","QUOTE","SIXTH","SWIVET",
                        "TOP", NULL };

    board_t solution = {"GPMRW", "NOXIS", "UATYV", "QHDEB", "KJFLC"};

    assert_eq(solve_board(board, words), true);

    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            assert_eq(board[r][c], solution[r][c]);
        }
    }
}

void run_part_b() {
  tests_ran = 0;
  tests_failed = 0;

  run_test(test_letter_position);
  run_test(test_valid_solution);
  run_test(test_update);
  run_test(test_solve_easy);
  run_test(test_solve_medium);
  run_test(test_solve_hard);
  run_test(test_solve_challenge);

  if (tests_failed == 0) {
    printf("********************\n"
           "Part B -- WELL DONE!\n"
           "********************\n");
  } else {
    printf("****************************************************\n"
           "Part B has %d incorrect functions out of %d tested\n"
           "****************************************************\n\n",
           tests_failed, tests_ran);
  }
}

int main(void) {
  run_part_b();
	return EXIT_SUCCESS;
}
