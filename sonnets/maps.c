#include "maps.h"

#include <string.h>
#include <stdlib.h>
#include "trie.h"

// --------------------------
// INTCHARMAP_T IMPLEMENTATION
// --------------------------

intcharmap_t *intcharmap_new() {
  return calloc(1, sizeof(intcharmap_t));
}

void intcharmap_free(intcharmap_t *m) {
  if (!m) return;
  for (int i = 0; i < m->counter; ++i) {
    free(m->contents[i]);
  }
  free(m->contents);
  free(m);
}

int intcharcomparator(const void *p1, const void *p2) {
  return (*(intcharpair_t **) p1)->key - (*(intcharpair_t **) p2)->key;
}

intcharpair_t *intcharnew_pair(int key, char value) {
  intcharpair_t *ret = calloc(1, sizeof(intcharpair_t));
  ret->key = key;
  ret->value = value;
  return ret;
}

intcharpair_t *intcharfind_pair(const intcharmap_t *m, int key) {
  intcharpair_t tmp = {key, 0};
  intcharpair_t *addrtmp = &tmp;
  intcharpair_t **p = bsearch((const void *) &addrtmp, m->contents, m->counter,
                              sizeof(intcharpair_t *), intcharcomparator);
  if (p)return *p;
  return ((void *) 0);
}

bool intcharmap_insert(intcharmap_t *m, int key, char value) {
  if (m->counter == m->size) {
    m->size += (1024);
    m->contents = realloc(m->contents, m->size * sizeof(intcharpair_t *));
  }
  int comp = 0;
  if (m->counter > 0) {
    comp = m->contents[m->counter - 1]->key - key;
    if (comp < 0) {
      m->contents[m->counter++] = intcharnew_pair(key, value);
      return 1;
    }
  }
  intcharpair_t *pair = intcharfind_pair(m, key);
  if (pair) {
    pair->value = value;
    return 1;
  }
  m->contents[m->counter++] = intcharnew_pair(key, value);
  if (m->counter > 1 && comp > 0)
    qsort(m->contents, m->counter, sizeof(intcharpair_t *), intcharcomparator);
  return 1;
}

bool intcharmap_get(const intcharmap_t *m, int key, char *value) {
  intcharpair_t *pair = intcharfind_pair(m, key);
  if (pair) *value = pair->value;
  return pair;
}

// --------------------------
// STRINTMAP_T IMPLEMENTATION
// --------------------------

strintmap_t *strintmap_new() {
  return calloc(1, sizeof(strintmap_t));
}

void strintmap_free(strintmap_t *m) {
  if (!m) return;
  for (int i = 0; i < m->counter; ++i) {
    free(m->contents[i]->key);
    free(m->contents[i]);
  }
  free(m->contents);
  free(m);
}

int strintcomparator(const void *p1, const void *p2) {
  return strcmp((*(strintpair_t **) p1)->key, (*(strintpair_t **) p2)->key);
}

strintpair_t *strintnew_pair(const char *key, int value) {
  strintpair_t *ret = calloc(1, sizeof(strintpair_t));
  ret->key = realloc(ret->key, strlen(key) + 1);
  strcpy(ret->key, key);
  ret->value = value;
  return ret;
}

strintpair_t *strintfind_pair(const strintmap_t *m, const char *key) {
  strintpair_t tmp = {(char *) key, 0};
  strintpair_t *addrtmp = &tmp;
  strintpair_t **p = bsearch((const void *) &addrtmp, m->contents, m->counter,
                             sizeof(strintpair_t *), strintcomparator);
  if (p) return *p;
  return ((void *) 0);
}


bool valid_key(const char *key) {
  for (; *key; key++) if (get_bit_pos(*key) == -1) return 0;
  return 1;
}

bool strintmap_insert(strintmap_t *m, const char *key, int value) {
  if (!valid_key(key)) return 0;
  if (m->counter == m->size) {
    m->size += (1024);
    m->contents = realloc(m->contents, m->size * sizeof(strintpair_t *));
  }
  int comp = 0;
  if (m->counter > 0) {
    comp = strcmp(m->contents[m->counter - 1]->key, key);
    if (comp < 0) {
      m->contents[m->counter++] = strintnew_pair(key, value);
      return 1;
    }
  }
  strintpair_t *pair = strintfind_pair(m, key);
  if (pair) {
    pair->value = value;
    return 1;
  }
  m->contents[m->counter++] = strintnew_pair(key, value);
  if (m->counter > 1 && comp > 0)
    qsort(m->contents, m->counter, sizeof(strintpair_t *), strintcomparator);
  return 1;
}

bool strintmap_get(const strintmap_t *m, const char *key, int *value) {
  strintpair_t *pair = strintfind_pair(m, key);
  if (pair) *value = pair->value;
  return pair;
}
