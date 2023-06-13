#include "laser.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int asserts_ran = 0, asserts_failed = 0, tests_ran = 0, tests_failed = 0;

#define assert_true(a) do { asserts_ran++; if (!a) { printf("%s(line %d): boolean assert failed\n", __func__, __LINE__); asserts_failed++;} } while (0)

#define assert_eq(a, b) do { asserts_ran++; if ((a) != (b)) { printf("%s(line %d): got: %d | expected: %d\n", __func__, __LINE__, a, b); asserts_failed++;} } while (0)

#define run_test(test) do { \
asserts_ran = asserts_failed = 0; printf("Running %s...\n", #test); test();\
tests_ran++;\
if (asserts_failed > 0) { \
tests_failed++; \
 printf("----%s: %d asserts failed out of %d asserts\n", #test, asserts_failed, asserts_ran); \
} else printf("++++%s passed \n\n", #test); \
} while (0)

bool board_equals(board_t board, board_t reference) {
    bool same = (board.height == reference.height) && (board.width == reference.width);
    if (!same) return false;

    for (int i = 0; i < board.height; i++) {
        for (int j = 0; j < board.width; j++) {
            if (board.cells[i][j] != reference.cells[i][j]) {
                printf("----cell %d, %d expected: \"%c\" got: \"%c\"\n",
                       i, j, reference.cells[i][j], board.cells[i][j]);
                same = false;
            }
        }
    }
    return same;
}
enum {HEIGHT = 12, WIDTH = 32};

board_t get_biscuit_board() {
    char **cells = calloc(HEIGHT, sizeof(char*));
    for (int i = 0; i < HEIGHT; i++)
        cells[i] = calloc(WIDTH + 1, sizeof(char));

    sprintf(cells[0] , "###############@########@#######");
    sprintf(cells[1] , "#             B                #");
    sprintf(cells[2] , ">              ?               @");
    sprintf(cells[3] , "#       C                      #");
    sprintf(cells[4] , "#      /                ?      #");
    sprintf(cells[5] , "#                              #");
    sprintf(cells[6] , "#     U       I                #");
    sprintf(cells[7] , "#      ?       ?        ?      @");
    sprintf(cells[8] , "#                      S       #");
    sprintf(cells[9] , "@              \\               @");
    sprintf(cells[10], "#               T              #");
    sprintf(cells[11], "################################");

    board_t b = {HEIGHT, WIDTH, cells};
    return b;
}

board_t get_other_board() {
    char **cells = calloc(HEIGHT, sizeof(char*));
    for (int i = 0; i < HEIGHT; i++)
        cells[i] = calloc(WIDTH + 1, sizeof(char));

    sprintf(cells[0] , "#######@#######@########@#######");
    sprintf(cells[1] , "#             B                #");
    sprintf(cells[2] , "#              \\               @");
    sprintf(cells[3] , "#       C                      #");
    sprintf(cells[4] , "#      /                \\      #");
    sprintf(cells[5] , "#                              #");
    sprintf(cells[6] , "#     U       I                #");
    sprintf(cells[7] , "#      \\       \\        /      @");
    sprintf(cells[8] , "#                      S       #");
    sprintf(cells[9] , "@              \\               @");
    sprintf(cells[10], "#               T              #");
    sprintf(cells[11], "################################");

    board_t b = {HEIGHT, WIDTH, cells};
    return b;
}

void test_is_on_board() {
    board_t board = get_biscuit_board();

    // Positive test cases
    assert_true(is_on_board(board, 0, 0));
    assert_true(is_on_board(board, 0, 1));
    assert_true(is_on_board(board, 1, 0));
    assert_true(is_on_board(board, 11, 31));
    assert_true(is_on_board(board, 11, 5));
    assert_true(is_on_board(board, 4, 31));
    assert_true(is_on_board(board, 6, 18));

    // Negative test cases
    assert_true(!is_on_board(board, 0, -1));
    assert_true(!is_on_board(board, 0, -5));
    assert_true(!is_on_board(board, 0, 32));
    assert_true(!is_on_board(board, 0, 35));
    assert_true(!is_on_board(board, 10, -1));
    assert_true(!is_on_board(board, 10, -5));
    assert_true(!is_on_board(board, 10, 32));
    assert_true(!is_on_board(board, 10, 35));
    assert_true(!is_on_board(board, -1, -1));
    assert_true(!is_on_board(board, 12, 32));
    assert_true(!is_on_board(board, 15, 15));
    assert_true(!is_on_board(board, 8, 40));

    // Check board is unchanged
    assert_true(board_equals(board, get_biscuit_board()));
}

void test_find_start() {
    board_t board = get_biscuit_board();

    // Positive test case
    int start_row = find_start(board);
    assert_eq(start_row, 2);
    // Check board is unchanged
    assert_true(board_equals(board, get_biscuit_board()));

    // Negative test case
    board = get_other_board();
    start_row = find_start(board);
    assert_eq(start_row, -1);
    // Check board is unchanged
    assert_true(board_equals(board, get_other_board()));
}

void test_get_mirror_label() {
    board_t board = get_other_board();
    // Positive test cases
    assert_eq(get_mirror_label(board, 2, 15), 'B');
    assert_eq(get_mirror_label(board, 4, 7), 'C');
    assert_eq(get_mirror_label(board, 7, 24), 'S');
    assert_eq(get_mirror_label(board, 9, 15), 'T');
    assert_eq(get_mirror_label(board, 7, 7), 'U');
    // Negative test cases
    assert_eq(get_mirror_label(board, 4, 12), '\0');
    assert_eq(get_mirror_label(board, 11, 31), '\0');
    // Check board is unchanged
    assert_true(board_equals(board, get_other_board()));
}

void test_load_board() {
	board_t board = load_board("biscuit.txt");
	board_t reference = get_biscuit_board();
    // Check board is the same as the reference hardcoded biscuit board
    assert_true(board_equals(board, reference));
}

void test_free_cells() {
    board_t b = get_other_board();
    free_cells(b);
    printf("!!! The \"free_cells\" function will be checked manually !!!\n");
}

void test_change_direction() {
    // Hit '/'
	assert_eq(change_direction(EAST,  FWD_MIRROR), NORTH);
	assert_eq(change_direction(NORTH, FWD_MIRROR), EAST);
    assert_eq(change_direction(SOUTH,  FWD_MIRROR), WEST);
    assert_eq(change_direction(WEST, FWD_MIRROR), SOUTH);

    // Hit '\'
	assert_eq(change_direction(WEST,  BWD_MIRROR), NORTH);
	assert_eq(change_direction(NORTH, BWD_MIRROR), WEST);
    assert_eq(change_direction(EAST,  BWD_MIRROR), SOUTH);
    assert_eq(change_direction(SOUTH, BWD_MIRROR), EAST);

    // Hit any other character
    assert_eq(change_direction(NORTH, ' '), NORTH);
    assert_eq(change_direction(NORTH, '?'), NORTH);
    assert_eq(change_direction(NORTH, 'A'), NORTH);
    assert_eq(change_direction(NORTH, '#'), NORTH);
    assert_eq(change_direction(NORTH, '>'), NORTH);
    assert_eq(change_direction(NORTH, '@'), NORTH);
}

void test_step_laser() {
	board_t board = get_biscuit_board();

	laser_state_t laser = {4, 15, WEST, ""};
    char cur_char;

	for (int i = 14; i > 7; i--) {
	    cur_char = step_laser(board, &laser);
        assert_eq(cur_char, ' ');
        assert_true(!strcmp(laser.msg, ""));
        assert_eq(laser.row, 4);
        assert_eq(laser.col,  i);
        assert_eq(laser.direction, WEST);
	}
    // Hit C mirror from EAST.
    cur_char = step_laser(board, &laser);
    assert_eq(cur_char, '/');
    assert_eq(laser.row, 4);
    assert_eq(laser.col, 7);

    for (int i = 5; i < 7; i++) {
        cur_char = step_laser(board, &laser);
        assert_eq(cur_char, ' ');
        assert_true(!strcmp(laser.msg, "C"));
        assert_eq(laser.row, i);
        assert_eq(laser.col, 7);
        assert_eq(laser.direction, SOUTH);
    }
    // Hit U mirror from NORTH.
    cur_char = step_laser(board, &laser);
    assert_eq(cur_char, '?');
    assert_eq(laser.row, 7);
    assert_eq(laser.col, 7);

    // Check board is unchanged
    assert_true(board_equals(board, get_biscuit_board()));
}

void test_shoot() {
	board_t board;
    // Shoot directly at absorber with no trace
    {
        board = get_biscuit_board();
        laser_state_t laser = {7, 25, EAST, ""};
        assert_true(shoot(board, &laser, false));

        // Check laser was updated
        assert_eq(laser.direction, EAST);
        assert_eq(laser.row, 7);
        assert_eq(laser.col, 31);
        assert_true(!strcmp(laser.msg, ""));

        // Check board was unchanged
        assert_true(board_equals(board, get_biscuit_board()));
    }
    // Shoot directly at absorber with trace
    {
        board = get_biscuit_board();
        laser_state_t laser = {7, 25, EAST, ""};
        assert_true(shoot(board, &laser, true));

        // Check laser was updated
        assert_eq(laser.direction, EAST);
        assert_eq(laser.row, 7);
        assert_eq(laser.col, 31);
        assert_true(!strcmp(laser.msg, ""));

        // Check board was traced
        assert_eq(board.cells[7][25], '-');
        assert_eq(board.cells[7][26], '-');
        assert_eq(board.cells[7][27], '-');
        assert_eq(board.cells[7][28], '-');
        assert_eq(board.cells[7][29], '-');
        assert_eq(board.cells[7][30], '-');
        assert_eq(board.cells[7][31], '@');
    }
    // Hit mirror and then absorber with no trace
    {
        board = get_biscuit_board();
        laser_state_t laser = {8, 15, SOUTH, ""};
        assert_true(shoot(board, &laser, false));

        // Check laser was updated
        assert_eq(laser.direction, EAST);
        assert_eq(laser.row, 9);
        assert_eq(laser.col, 31);
        assert_true(!strcmp(laser.msg, "T"));

        // Check board was unchanged
        assert_true(board_equals(board, get_biscuit_board()));
    }
    // Hit mirror and then absorber with trace
    {
        board = get_biscuit_board();
        laser_state_t laser = {8, 15, SOUTH, ""};
        assert_true(shoot(board, &laser, true));

        // Check laser was updated
        assert_eq(laser.direction, EAST);
        assert_eq(laser.row, 9);
        assert_eq(laser.col, 31);
        assert_true(!strcmp(laser.msg, "T"));

        // Check board was traced
        assert_eq(board.cells[8][15], '|');
        assert_eq(board.cells[9][15], '\\');
        assert_eq(board.cells[9][16], '-');
        assert_eq(board.cells[9][20], '-');
        assert_eq(board.cells[9][24], '-');
        assert_eq(board.cells[9][28], '-');
        assert_eq(board.cells[9][31], '@');
    }
    // Hit mirror and then '?' with no trace (hit C mirror from EAST )
    {
        board = get_biscuit_board();
        laser_state_t laser = {4, 15, WEST, "PRE_"};
        assert_true(!shoot(board, &laser, false));

        // Check laser was updated
        assert_eq(laser.direction, SOUTH);
        assert_eq(laser.row, 7);
        assert_eq(laser.col, 7);
        assert_true(!strcmp(laser.msg, "PRE_C"));

        // Check board was unchanged
        assert_true(board_equals(board, get_biscuit_board()));
    }
    // Hit mirror and then absorber with trace
    {
        board = get_biscuit_board();
        laser_state_t laser = {4, 15, WEST, ""};
        assert_true(!shoot(board, &laser, true));

        // Check laser was updated
        assert_eq(laser.direction, SOUTH);
        assert_eq(laser.row, 7);
        assert_eq(laser.col, 7);
        assert_true(!strcmp(laser.msg, "C"));

        // Check board was traced
        assert_eq(board.cells[4][15], '-');
        assert_eq(board.cells[4][10], '-');
        assert_eq(board.cells[4][7], '/');
        assert_eq(board.cells[5][7], '|');
        assert_eq(board.cells[6][7], '|');
        assert_eq(board.cells[7][7], '?');
    }
    // Make laser cross by writting BISCUIT
    {
        board = get_other_board();
        laser_state_t laser = {2, 0, EAST, ""};
        assert_true(shoot(board, &laser, true));

        // Check laser was updated
        assert_eq(laser.direction, EAST);
        assert_eq(laser.row, 9);
        assert_eq(laser.col, 31);
        assert_true(!strcmp(laser.msg, "BISCUIT"));

        // Check board was traced
        assert_eq(board.cells[2][2], '-');
        assert_eq(board.cells[4][15], '+');
    }
}

void test_solve() {
    board_t board;
    laser_state_t laser = {2, 0, EAST, ""};
    // Positive test cases
    board = get_biscuit_board(); assert_true(solve(board, laser, "BISCUIT"));
	board = get_biscuit_board(); assert_true(solve(board, laser, "BIUCS"));
	board = get_biscuit_board(); assert_true(solve(board, laser, "BIUCSIT"));
	board = get_biscuit_board(); assert_true(solve(board, laser, "B"));
	board = get_biscuit_board(); assert_true(solve(board, laser, "BT"));
	// Negative test cases
	board = get_biscuit_board(); assert_true(!solve(board, laser, "CUT"));
	board = get_biscuit_board(); assert_true(!solve(board, laser, "BISCUITS"));
	board = get_biscuit_board(); assert_true(!solve(board, laser, "BIC"));
}

void test_solve_advanced() {
    printf("!!! This test relies on shoot to work correctly !!!\n");
    board_t board;
    // Positive test cases
    {
        laser_state_t laser = {2, 0, EAST, ""};
        board = get_biscuit_board();
        assert_true(solve(board, laser, "BISCUIT"));
        assert_true(shoot(board, &laser, false));
    }
    {
        laser_state_t laser = {2, 0, EAST, ""};
        board = get_biscuit_board();
        assert_true(solve(board, laser, "BIUCS"));
        assert_true(shoot(board, &laser, false));
    }
    {
        laser_state_t laser = {2, 0, EAST, ""};
        board = get_biscuit_board();
        assert_true(solve(board, laser, "BIUCSIT"));
        assert_true(shoot(board, &laser, false));
    }
    {
        laser_state_t laser = {2, 0, EAST, ""};
        board = get_biscuit_board();
        assert_true(solve(board, laser, "B"));
        assert_true(shoot(board, &laser, false));
    }
    {
        laser_state_t laser = {2, 0, EAST, ""};
        board = get_biscuit_board();
        assert_true(solve(board, laser, "BT"));
        assert_true(shoot(board, &laser, false));

    }
    // Negative test cases
    {
        laser_state_t laser = {2, 0, EAST, ""};
        board = get_biscuit_board();
        assert_true(!solve(board, laser, "CUT"));
        assert_true(!shoot(board, &laser, false));
    }
    {
        laser_state_t laser = {2, 0, EAST, ""};
        board = get_biscuit_board();
        assert_true(!solve(board, laser, "BISCUITS"));
        assert_true(!shoot(board, &laser, false));
    }
    {
        laser_state_t laser = {2, 0, EAST, ""};
        board = get_biscuit_board();
        assert_true(!solve(board, laser, "BIC"));
        assert_true(!shoot(board, &laser, false));
    }
}

void run_part_a() {
    tests_ran = 0;
    tests_failed = 0;

    run_test(test_is_on_board);
    run_test(test_find_start);
    run_test(test_get_mirror_label);
    run_test(test_load_board);
    run_test(test_free_cells);

    if (tests_failed == 0) {
        printf("***************************************\n"
               "*       Part A: ALL TESTS PASS!       *\n"
               "***************************************\n\n");
    } else {
        printf("****************************************************\n"
               "Part A has %d incorrect functions out of %d tested\n"
               "****************************************************\n\n",
               tests_failed, tests_ran);
    }
}

void run_part_b() {
    tests_ran = 0;
    tests_failed = 0;

    run_test(test_change_direction);
    run_test(test_step_laser);
    run_test(test_shoot);
    run_test(test_solve);
    run_test(test_solve_advanced);

    if (tests_failed == 0) {
        printf("***************************************\n"
               "*       Part B: ALL TESTS PASS!       *\n"
               "***************************************\n");
    } else {
        printf("****************************************************\n"
               "Part B has %d incorrect functions out of %d tested\n"
               "****************************************************\n\n",
               tests_failed, tests_ran);
    }
}

#ifdef TEST
int main(void) {
    run_part_a();
    run_part_b();
    return EXIT_SUCCESS;
}

#endif
