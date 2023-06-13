#include "region.h"
#include "image.h"
#include "typedefs.h"
#include "list.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/////ALL THESE FUNCTIONS ARE PROVIDED FOR YOU/////////////////////
/////DO NOT MODIFY THEM///////////////////////////////////////////

// Our colour function of choice
uint8_t region_colour(const region_t *region)
{
  const unsigned depth = region->depth;
  return (depth * 1879u) % 255;
}

// Resets a point to (x,y)
void init_point(point_t *point, int x, int y)
{
  point->x = x;
  point->y = y;
}

// Resets an extent to (width, height)
void init_extent(extent_t *extent, int width, int height)
{
  extent->width = width;
  extent->height = height;
}


// Allocates a region. You may assume that the return value is non-NULL.
region_t *region_allocate(void)
{
  region_t *new_region = malloc(sizeof(region_t));

  if (new_region == NULL)
  {
    perror("region_allocate");
    exit(EXIT_FAILURE);
  }

  return new_region;
}

// Prints a textual description of a region to the supplied FILE*.
void print_region(FILE *out, const region_t *region)
{
  assert(out != NULL);
  assert(region != NULL);

  fprintf(out, "Region of depth %i at (%i, %i) of extent (%i, %i)\n",
      region->depth, region->position.x, region->position.y,
      region->extent.width, region->extent.height);
}

// Finds all regions located in "image" and adds them to "regions".
// Regions are added so that ordering according to the
// comparison function region_compare() is preserved.
void find_regions(list_t *regions, image_t* image)
{
  region_t *image_region = region_allocate();

  image_region->depth = 0;
  init_point(&image_region->position, 0, 0);
  init_extent(&image_region->extent, image->width, image->height);

  list_insert_ascending(regions, image_region);
  find_sub_regions(regions, image, image_region);
}

///////////////////////////////////////////////////////////////////

/////////////////////////USEFUL FUNCTIONS///////////////////////////
///////////////////////////////////////////////////////////////////

// Compares two points lexicographically.
// Returns 1 if first is less than second, otherwise 0.
// Ordering of comparison is [y, x].
//
// You are NOT required to implement this function. However you may find
// it helpful to do so for Part I, Q1.
int point_compare_less(const point_t *first, const point_t *second)
{
  //TODO (optional)
  return 0;
}

// Deallocates a region.
//
// You are NOT required to implement this function. However, you may
// find it helpful to do so for Part I, Q3.
void region_destroy(region_t *region)
{
  free(region);
}
///////////////////////////////////////////////////////////////////

////////////////TO BE IMPLEMENTED///////////////////////////////////
////////////////////////////////////////////////////////////////////

// Compares two regions.
// Returns 1 if position of first is lexicographically less than that
// of the second, otherwise returns 0.
// Ordering of the position comparison is [y, x].
int region_compare(const region_t *r1, const region_t *r2)
{
  return r1->position.y < r2->position.y
      || (r1->position.y == r2->position.y && r1->position.x < r2->position.x);
}

// Prints all regions in "regions" to "out".
// print_region (above) prints a textual description of a region
// to the supplied FILE*
void print_regions(FILE *out, list_t *regions)
{
  list_iter iter = list_begin(regions);
  while (iter != list_end(regions)) {
    print_region(out, list_iter_value(iter));
    iter = list_iter_next(iter);
  }
}

//
// Sets the specified region of image "image" to the intensity value "value".
//
void image_fill_region(image_t *image, const region_t *region, uint8_t value)
{
  for (int x = region->position.x; x < region->position.x + region->extent.width; x++) {
    for (int y = region->position.y; y < region->position.y + region->extent.height; y++) {
      set_pixel(image, x, y, value);
    }
  }
}

// Determines the extent of a region.
// position: the location of the top-left-hand corner of the region.
// image: the image to be searched.
// extent: this will be populated with the width and height of a region.
void find_extent(extent_t *extent, image_t *image, const point_t *position)
{
  uint8_t col = get_pixel(image, position->x, position->y);
  int x = position->x;
  while (get_pixel(image, x, position->y) == col) {
    x++;
  }
  int y = position->y;
  while (get_pixel(image, position->x, y) == col) {
    y++;
  }
  init_extent(extent, x - position->x, y - position->y);
}

// Finds all regions located in the region "current" of "image" and adds them
// to "regions".  Regions are added so that ordering according to the
// comparison function region_compare() is preserved.
void find_sub_regions(list_t* regions, image_t *image, const region_t *current)
{
  uint8_t col = get_pixel(image, current->position.x, current->position.y);
  for (int x = current->position.x; x < current->position.x + current->extent.width; x++) {
    for (int y = current->position.y; y < current->position.y + current->extent.height; y++) {
      if (get_pixel(image, x, y) != col) {
	region_t *region = region_allocate();
	region->depth = current->depth + 1;
	init_point(&region->position, x, y);
	find_extent(&region->extent, image, &region->position);
	list_insert_ascending(regions, region);
	find_sub_regions(regions, image, region);
	image_fill_region(image, region, col);
      }
    }
  }
}

// Renders all regions to an image using the supplied colour_function_t
// (declared in typedefs.h) to select pixel intensity.
void render_regions(image_t *image, list_t *regions,
                    colour_function_t get_colour)
{
  list_iter iter = list_begin(regions);
  while (iter != list_end(regions)) {
    struct region *region = list_iter_value(iter);
    image_fill_region(image, region, get_colour(region));
    iter = list_iter_next(iter);
  }
}
///////////////////////////////////////////////////////////////////////////////
