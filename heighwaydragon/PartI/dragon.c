#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "image.h"
#include "dragon.h"

#define NUM_ELEMENTS(x) (sizeof(x) / sizeof(x[0]))

/* x, y: coordinates of turtle */
static long x, y;

/* When drawing a pixel to the image, x and y must be divided by this value.
 * This enables both the dragon curve and twin dragon to rendered without
 * clipping.
 */
static long scale;

/* drawn_pixels: the length of the path travelled. */
static long drawn_pixels;

/* direction: the current direction of the turtle. */
static vector_t direction;

static vector_t directions[] = {
  {1, 0}, {1, 1}, {0, 1}, {-1, 1},
  {-1, 0}, {-1, -1}, {0, -1}, {1, -1}
};

/* Returns a vector that describes the initial direction of the turtle. Each
 * iteration corresponds to a 45 degree rotation of the turtle anti-clockwise.  */
vector_t starting_direction(int total_iterations)
{
  int idx = total_iterations % 8;
  vector_t dir = { directions[idx].dx, directions[idx].dy };
  return dir;
}

static uint8_t grey_values[] = {
  100, 120, 150, 180, 200
};

/* Draws a pixel to dst at location (x, y). The pixel intensity is chosen as a
 * function of image size and the number of pixels drawn.
 *
 * The gray level changes over entire size of path; the pixel value oscillates
 * along the path to give some contrast between segments close to each other
 * spatially.
 */
void draw_greyscale(image_t *dst, long x, long y)
{
  int level = LEVEL * drawn_pixels / (dst->height * dst->height);
  if (level < NUM_ELEMENTS(grey_values)) {
    set_pixel(dst, x, y, grey_values[level]);
  } else {
    set_pixel(dst, x, y, 255);
  }
}

static int direction_index(vector_t d) {
  for (int i = 0; i < NUM_ELEMENTS(directions); i++) {
    if (d.dx == directions[i].dx && d.dy == directions[i].dy) {
      return i;
    }
  }
  return -1;
}

static const char *apply_rule(char p) {
  if (p == 'X') {
    return "X+YF+";
  } else if (p == 'Y') {
    return "-FX-Y";
  }
  return "";
}

/* Iterates though the characters of str, recusively calling string_iteration()
 * until rules have been applied iterations times, or no rule is applicable.
 * and update the image.
 */
void string_iteration(image_t *dst, const char *str, int iterations)
{
  int idx;
  for (const char *p = str; *p; p++) {
    switch (*p) {
      case '-':
        idx = direction_index(direction);
	direction.dx = directions[(idx + 2) % 8].dx;
	direction.dy = directions[(idx + 2) % 8].dy;
	break;

      case '+':
        idx = direction_index(direction);
	direction.dx = directions[(idx - 2 + 8) % 8].dx;
	direction.dy = directions[(idx - 2 + 8) % 8].dy;
	break;

      case 'F':
        drawn_pixels++;
	draw_greyscale(dst, x / scale, y / scale);
	x += direction.dx;
	y += direction.dy;
	break;

      default:
        if (iterations > 0) {
	  string_iteration(dst, apply_rule(*p), iterations - 1);
	}
	break;
    }
  }
}

/* Creates an image of requested size, calls starting_direction() to compute
 * initial turtle direction then calls string_iteration() to construct the
 * image. The constructed image is saved to a file in the output directory.
 */
void dragon(long size, int total_iterations)
{
  image_t *dst;
  init_image(&dst, 1.5 * size, size, 1, 255);
  x = size / 3;
  y = size / 3;
  scale = 1;
  direction = starting_direction(total_iterations);
  string_iteration(dst, "FX", total_iterations);
  image_write("jurassic.pgm", dst, PGM_FORMAT);
  image_free(dst);
}

/* The main function. When called with an argument, this should be considered
 * the number of iterations to execute. Otherwise, it is assumed to be 9. Image
 * size is computed from the number of iterations then dragon() is used to
 * generate the dragon image. */
int main(int argc, char **argv)
{
  if (argc > 2) {
    fprintf(stderr, "Usage: %s <num_iter>", argv[0]);
    exit(EXIT_FAILURE);
  }
  int num_iter = 9;
  if (argc == 2) {
    num_iter = atoi(argv[1]);
  }
  dragon(pow(2, num_iter), 2 * num_iter);

  return EXIT_SUCCESS;
}

