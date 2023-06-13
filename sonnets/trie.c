#include "trie.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

// Returns the position of the bit that represents the existence of this symbol
// in the bitfield, or -1 if the symbol is not in the alphabet we support.
int get_bit_pos(char symbol) {
  if ('A' <= symbol && symbol <= 'Z')
    return 'Z' - symbol + 1;
  else switch (symbol) {
      case '_'  : return 'Z' - 'A' + 2;
      case '.'  : return 'Z' - 'A' + 3;
      case '-'  : return 'Z' - 'A' + 4;
      case '\'' : return 'Z' - 'A' + 5;
      case ' '  : return 'Z' - 'A' + 6;
      default   : return -1;
    }
}

trie_t *trie_new() {
  trie_t *trie = malloc(sizeof(trie_t));
  assert(trie != NULL);
  trie->value = 0;
  trie->bitfield = 0;
  trie->children = NULL;
  return trie;
}

int count_set_bits(uint32_t n) {
  int set = 0;
  for (int i = 0; i < 32; i++) {
    set += n & 1;
    n >>= 1;
  }
  return set;
}

static int count_children(trie_t *root) {
  return count_set_bits(root->bitfield & ~1);
}

void trie_free(trie_t *root) {
  if (root == NULL) {
    return;
  }

  for (int i = 0; i < count_children(root); i++) {
    trie_free(root->children[i]);
  }

  free(root->children);
  free(root);
}

static int get_children_pos(trie_t *root, int pos) {
  return count_set_bits(root->bitfield >> pos) - 1;
}

bool trie_get(const trie_t *root, const char *key, int *value_out) {
  trie_t *trie = (trie_t *)root;
  for (int i = 0; i < strlen(key); i++) {
    int pos = get_bit_pos(key[i]);
    if (pos == -1 || !((trie->bitfield >> pos) & 1)) {
      return false;
    }
    trie = trie->children[get_children_pos(trie, pos)];
  }

  if (!(trie->bitfield & 1)) {
    return false;
  }

  *value_out = trie->value;
  return true;
}

bool trie_insert(trie_t *root, const char *key, int value) {
  assert(root != NULL);
  
  trie_t *trie = root;
  for (int i = 0; i < strlen(key); i++) {
    int pos = get_bit_pos(key[i]);
    if (pos == -1) {
      return false;
    }

    if (!((trie->bitfield >> pos) & 1)) {
      trie_t *new_trie = trie_new();
      if (count_children(trie) == 0) {
	trie->bitfield |= 1 << pos;
	trie->children = malloc(sizeof(trie_t *));
	assert(trie->children != NULL);
	trie->children[0] = new_trie;
      } else {
	trie->bitfield |= 1 << pos;
	trie->children = realloc(trie->children, count_children(trie) * sizeof(trie_t *));
	assert(trie->children != NULL);
	int cpos = get_children_pos(trie, pos);
	memmove(&trie->children[cpos + 1], &trie->children[cpos], (count_children(trie) - cpos - 1) * sizeof(trie_t *));
	trie->children[cpos] = new_trie;
      }
    }
    trie = trie->children[get_children_pos(trie, pos)];
  }

  trie->bitfield |= 1;
  trie->value = value;
  return true;
}

#ifdef TRIE_MAIN

// TODO: DO NOT MODIFY TIHS FUNCTION!!! Remember to run:
//  valgrind --leak-check=full --show-leak-kinds=all ./trie

int main(void) {
  #define SIZE (8)
  char ks[SIZE][10] = { "GOOD", "",   "W",  "-_ _-", "123", "*",   "()",  "+}{" };
  bool bs[SIZE] =     { true,   true, true, true,    false, false, false, false };
  int vs[SIZE] =      { 12,     0,    -1,   2342,    999,   0,     2,     4 };

  printf("Mapping strings to ints.\n");
  trie_t *root = trie_new();
  for (int i = 0; i < SIZE; ++i) {
    char *status = bs[i] ? "(insert should succeed)" : "(insert should fail)";
    if (trie_insert(root, ks[i], vs[i])) {
      printf("Was able to insert %s with value %d %s\n", ks[i], vs[i], status);
    } else {
      printf("Unable to insert %s with value %d %s\n", ks[i], vs[i], status);
    }
  }
  for (int i = SIZE - 1; i >= 0; --i) {
    char *status = bs[i] ? "(get should succeed)" : "(get should fail)";
    int v;
    if (trie_get(root, ks[i], &v)) {
      printf("Was able to get %s -> %d %s\n", ks[i], v, status);
    } else {
      printf("Unable to get %s %s\n", ks[i], status);
    }
  }
  trie_free(root);
}

#endif

