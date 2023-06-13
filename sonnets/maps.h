#ifndef __MAPS_H__
#define __MAPS_H__

#include <stdbool.h>

typedef struct intcharpair {
  int key;
  char value;
} intcharpair_t;

typedef struct intcharmap {
  int size;
  int counter;
  intcharpair_t **contents;
} intcharmap_t;

intcharmap_t *intcharmap_new();
void intcharmap_free(intcharmap_t *m);
bool intcharmap_insert(intcharmap_t *m, int key, char value);
bool intcharmap_get(const intcharmap_t *m, int key, char *value);

typedef struct strintpair {
  char *key;
  int value;
} strintpair_t;

typedef struct strintmap {
  int size;
  int counter;
  strintpair_t **contents;
} strintmap_t;

strintmap_t *strintmap_new();
void strintmap_free(strintmap_t *m);
bool strintmap_insert(strintmap_t *m, const char *key, int value);
bool strintmap_get(const strintmap_t *m, const char *key, int *value);

#endif // __MAPS_H__
