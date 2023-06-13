#ifndef __TRIE_H__
#define __TRIE_H__

#include <stdbool.h>
#include <stdint.h>

typedef struct trie_node {
  int value;
  uint32_t bitfield;
  struct trie_node **children;
} trie_t;

int get_bit_pos(char symbol);

trie_t *trie_new();

int count_set_bits(uint32_t n);

void trie_free(trie_t *root);

bool trie_get(const trie_t *root, const char *key, int *value_out);

bool trie_insert(trie_t *root, const char *key, int value);

#endif // __TRIE_H__
