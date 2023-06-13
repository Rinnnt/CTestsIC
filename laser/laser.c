#include "laser.h"

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

bool is_on_board(board_t board, int row, int col) {
  return 0 <= row && row < board.height && 0 <= col && col < board.width;
}

int find_start(board_t board) {
  for (int i = 0; i < board.height; i++) {
    if (board.cells[i][0] == START) {
      return i;
    }
  }
  return -1;
}

char get_mirror_label(board_t board, int row, int col) {
  assert(is_on_board(board, row, col));

  if (board.cells[row][col] == FWD_MIRROR || board.cells[row][col] == BWD_MIRROR) {
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
	if (is_on_board(board, row + i, col + j) && isalpha(board.cells[row + i][col + j])) {
	  return board.cells[row + i][col + j];
	}
      }
    }
  }

  return '\0';
}

board_t load_board(const char *filename) {
  board_t board;

  FILE *fp = fopen(filename, "r");
  assert(fp != NULL);

  int rows;
  int cols;
  assert(fscanf(fp, "%d %d", &rows, &cols) == 2);
  board.height = rows;
  board.width = cols;

  board.cells = malloc(board.height * sizeof(char *));
  assert(board.cells != NULL);
  char *content = malloc(board.height * (board.width + 1) * sizeof(char));
  assert(content != NULL);
  char buf[board.width + 2];
  assert(fgets(buf, board.width + 2, fp) != NULL);
  for (int i = 0; i < board.height; i++) {
    board.cells[i] = content + i * (board.width + 1);
    assert(fgets(buf, board.width + 2, fp) != NULL);
    for (int j = 0; j < board.width; j++) {
      board.cells[i][j] = buf[j];
    }
    board.cells[i][board.width] = '\0';
  }
  
  return board;
}

void free_cells(board_t board) {
  if (board.height > 0) {
    free(board.cells[0]);
  }
  free(board.cells);
}

direction_t change_fwd[] = {
  NORTH, WEST, SOUTH, EAST
};

direction_t change_bwd[] = {
  SOUTH, EAST, NORTH, WEST
};

direction_t change_direction(direction_t direction, char cell) {
  if (cell == FWD_MIRROR) {
    return change_fwd[direction];
  }

  if (cell == BWD_MIRROR) {
    return change_bwd[direction];
  }

  return direction;
}

int dxdy[][2] = {
  {0, 1}, {1, 0}, {0, -1}, {-1, 0}
};

char step_laser(board_t board, laser_state_t *laser) {
  assert(is_on_board(board, laser->row, laser->col));
  laser->direction = change_direction(laser->direction, board.cells[laser->row][laser->col]);
  char c;
  if ((c = get_mirror_label(board, laser->row, laser->col)) != '\0') {
    int len = strlen(laser->msg);
    laser->msg[len] = c;
    laser->msg[len + 1] = '\0';
  }
  laser->row += dxdy[laser->direction][0];
  laser->col += dxdy[laser->direction][1];
  assert(is_on_board(board, laser->row, laser->col));
  return board.cells[laser->row][laser->col];
}

static bool contains(char *str, char c) {
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == c) {
      return true;
    }
  }
  return false;
}

bool shoot(board_t board, laser_state_t *laser, bool trace) {
  assert(is_on_board(board, laser->row, laser->col));
  char c = board.cells[laser->row][laser->col];
  do {
    if (trace) {
      if (contains(PASSTHROUGHS, c)) {
	if (laser->direction == NORTH || laser->direction == SOUTH) {
	  if (c == HORIZ_LASER || c == CROSS_LASER) {
	    board.cells[laser->row][laser->col] = CROSS_LASER;
	  } else {
	    board.cells[laser->row][laser->col] = VERT_LASER;
	  }
	} else {
	  if (c == VERT_LASER || c == CROSS_LASER) {
	    board.cells[laser->row][laser->col] = CROSS_LASER;
	  } else {
	    board.cells[laser->row][laser->col] = HORIZ_LASER;
	  }
	}
      }
    }
    c = step_laser(board, laser);
  } while (!contains(BLOCKERS, c));

  return c == END;
}

bool solve(board_t board, laser_state_t laser, const char target[MAX_MSG_LEN]) {
  assert(is_on_board(board, laser.row, laser.col));

  if (shoot(board, &laser, false) && !strcmp(laser.msg, target)) {
    return true;
  } else {
    if (board.cells[laser.row][laser.col] == CHOICE) {
      for (int i = 0; i < strlen(CHOICES); i++) {
	laser_state_t new_laser = {laser.row, laser.col, laser.direction};
	strcpy(new_laser.msg, laser.msg);
	board.cells[laser.row][laser.col] = CHOICES[i];
	step_laser(board, &new_laser);
	if (solve(board, new_laser, target)) {
	  return true;
	}
      }
      board.cells[laser.row][laser.col] = CHOICE;
    }
  }

  return false;
}

#ifdef MAIN
int main(void) {
  board_t board = load_board("biscuit.txt");
  assert(find_start(board) != -1);
  printf("Initial board:\n");
    print_board(board);

    const char target[MAX_MSG_LEN] = "BIUC";
    printf("Attempt to construct word: %s\n", target);

    laser_state_t laser = {find_start(board), 0, EAST, ""};
    // Solve board
    bool success = solve(board, laser, target);
    // Trace board
    shoot(board, &laser, true);
    // Print traced board
    printf(success ? "Solution found!\n" : "Word cannot be constructed!\n");
    print_board(board);
    free_cells(board);
    return EXIT_SUCCESS;
}
#endif
###############@########@#######
#             B         |      #
>--------------\        |      @
#       C      |        |      #
#      /-------+--------/      #
#      |       |               #
#     U|      I|               #
#      \-------/        ?      @
#                      S       #
@              \               @
#               T              #
################################

