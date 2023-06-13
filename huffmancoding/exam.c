#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exam.h"

/*
 * Private function prototypes.
 */

static void _print_huffman_tree(const huffman_tree_t *, int);
static void _print_huffman_tree_codes(const huffman_tree_t *, char *, char *);

/*
 * Prints the given Huffman tree.
 */
void print_huffman_tree(const huffman_tree_t *t) {
  printf("Huffman tree:\n");
  _print_huffman_tree(t, 0);
}

/*
 * Private helper function for print_huffman_tree.
 */
static void _print_huffman_tree(const huffman_tree_t *t, int level) {
  int i;
  for (i = 0; i <= level; i++) {
    printf("  ");
  }

  if (t->left == NULL && t->right == NULL) {
    printf("Leaf: '%c' with count %d\n", t->letter, t->count);
  } else {
    printf("Node: accumulated count %d\n", t->count);

    if (t->left != NULL) {
      _print_huffman_tree(t->left, level + 1);
    }

    if (t->right != NULL) {
      _print_huffman_tree(t->right, level + 1);
    }
  }
}

/*
 * Prints the codes contained in the given Huffman tree.
 */
void print_huffman_tree_codes(const huffman_tree_t *t) {
  printf("Huffman tree codes:\n");

  char *code = calloc(MAX_CODE_LENGTH, sizeof(char)), *code_position = code;
  if (code == NULL) {
    perror("calloc");
    exit(EXIT_FAILURE);
  }

  _print_huffman_tree_codes(t, code, code_position);
  free(code);
}

/*
 * Private helper function for print_huffman_tree_codes.
 */
static void _print_huffman_tree_codes(const huffman_tree_t *t,
                                      char *code, char *code_position) {

  if (t->left == NULL && t->right == NULL) {
    printf("'%c' has code \"%s\"\n", t->letter, code);
  } else if (t->left != NULL) {
    *code_position++ = 'L';
    *code_position = '\0';

    _print_huffman_tree_codes(t->left, code, code_position--);
  }

  if (t->right != NULL) {
    *code_position++ = 'R';
    *code_position = '\0';

    _print_huffman_tree_codes(t->right, code, code_position--);
  }
}

/*
 * Prints a list of Huffman trees.
 */
void print_huffman_tree_list(const huffman_tree_list_t *l) {
  printf("Huffman tree list:\n");

  for (; l != NULL; l = l->next) {
    print_huffman_tree(l->tree);
  }
}

/*
 * Frees a Huffman tree.
 */
void huffman_tree_free(huffman_tree_t *t) {
  if (t != NULL) {
    huffman_tree_free(t->left);
    huffman_tree_free(t->right);
    free(t);
  }
}

/*
 * Frees a list of Huffman trees.
 */
void huffman_tree_list_free(huffman_tree_list_t *l) {
  if (l != NULL) {
    huffman_tree_list_free(l->next);
    huffman_tree_free(l->tree);
    free(l);
  }
}

static void validate_pointer(void *pointer, char *message) {
  if (pointer == NULL) {
    perror(message);
    exit(EXIT_FAILURE);
  }
}

/*
 * Returns 1 if the string s contains the character c and 0 if it does not.
 */
int contains(char *s, char c) {
  return strchr(s, c) != NULL;
}

/*
 * Returns the number of occurrences of c in s.
 */
int frequency(char *s, char c) {
  int freq = 0;
  for (char *p = s; *p; p++) {
    freq += *p == c;
  }
  return freq;
}

/*
 * Takes a string s and returns a new heap-allocated string containing only the
 * unique characters of s.
 *
 * Pre: all strings will have fewer than or equal to MAX_STRING_LENGTH - 1
 *      characters.
 */
char *nub(char *s) {
  char *unique = calloc(MAX_STRING_LENGTH, sizeof(char));
  validate_pointer(unique, "nub");

  char *unique_iter = unique;
  for (char *p = s; *p; p++) {
    if (!contains(unique, *p)) {
      *unique_iter++ = *p;
    }
  }
  return unique;
}

/*
 * Adds the Huffman tree t to the list l, returning a pointer to the new list.
 *
 * Pre:   The list l is sorted according to the frequency counts of the trees
 *        it contains.
 *
 * Post:  The list l is sorted according to the frequency counts of the trees
 *        it contains.
 */
huffman_tree_list_t *huffman_tree_list_add(huffman_tree_list_t *l,
                                            huffman_tree_t *t) {
  huffman_tree_list_t *node = malloc(sizeof(huffman_tree_list_t));
  validate_pointer(node, "huffman_tree_list_add");
  node->tree = t;

  huffman_tree_list_t *iter = l;
  huffman_tree_list_t *prev;
  while (iter != NULL && iter->tree->count < t->count) {
    prev = iter;
    iter = iter->next;
  }

  if (iter == l) {
    node->next = l;
    return node;
  } else {
    prev->next = node;
    node->next = iter;
    return l;
  }
}

/*
 * Takes a string s and a lookup table and builds a list of Huffman trees
 * containing leaf nodes for the characters contained in the lookup table. The
 * leaf nodes' frequency counts are derived from the string s.
 *
 * Pre:   t is a duplicate-free version of s.
 *
 * Post:  The resulting list is sorted according to the frequency counts of the
 *        trees it contains.
 */
huffman_tree_list_t *huffman_tree_list_build(char *s, char *t) {
  huffman_tree_list_t *list = NULL;
  for (char *p = t; *p; p++) {
    huffman_tree_t *tree = malloc(sizeof(huffman_tree_t));
    validate_pointer(tree, "huffman_tree_list_build");
    tree->count = frequency(s, *p);
    tree->letter = *p;
    tree->left = NULL;
    tree->right = NULL;
    list = huffman_tree_list_add(list, tree);
  }
  return list;
}

/*
 * Reduces a sorted list of Huffman trees to a single element.
 *
 * Pre:   The list l is non-empty and sorted according to the frequency counts
 *        of the trees it contains.
 *
 * Post:  The resuling list contains a single, correctly-formed Huffman tree.
 */
huffman_tree_list_t *huffman_tree_list_reduce(huffman_tree_list_t *l) {
  huffman_tree_list_t *left = l;
  huffman_tree_list_t *right = left->next;
  if (right == NULL) {
    return l;
  }
  huffman_tree_list_t *list = right->next;

  huffman_tree_t *left_tree = left->tree;
  huffman_tree_t *right_tree = right->tree;
  free(left);
  free(right);
  huffman_tree_t *new_tree = malloc(sizeof(huffman_tree_t));
  validate_pointer(new_tree, "huffman_tree_list_reduce");

  new_tree->count = left_tree->count + right_tree->count;
  new_tree->letter = '\0';
  new_tree->left = left_tree;
  new_tree->right = right_tree;
  return huffman_tree_list_reduce(huffman_tree_list_add(list, new_tree));
}

static int huffman_tree_encode_char(huffman_tree_t *t, char c, char *buffer, char* encoding) {
  if (t == NULL) {
    return 0;
  }

  if (t->letter == c) {
    strcat(encoding, buffer);
    return 1;
  } else {
    strcat(buffer, "L");
    if (huffman_tree_encode_char(t->left, c, buffer, encoding)) {
      return 1;
    }
    buffer[strlen(buffer) - 1] = 'R';
    if (huffman_tree_encode_char(t->right, c, buffer, encoding)) {
      return 1;
    }
    buffer[strlen(buffer) - 1] = '\0';
    return 0;
  }
}

/*
 * Accepts a Huffman tree t and a string s and returns a new heap-allocated
 * string containing the encoding of s as per the tree t.
 *
 * Pre: s only contains characters present in the tree t.
 */
char *huffman_tree_encode(huffman_tree_t *t, char *s) {
  char *encoding = calloc(MAX_CODE_LENGTH, sizeof(char));
  validate_pointer(encoding, "huffman_tree_encode");

  char code_buffer[MAX_CODE_LENGTH];
  for (char *p = s; *p; p++) {
    *code_buffer = '\0';
    huffman_tree_encode_char(t, *p, code_buffer, encoding);
  }
  return encoding;
}

/*
 * Accepts a Huffman tree t and an encoded string and returns a new
 * heap-allocated string contained the decoding of the code as per the tree t.
 *
 * Pre: the code given is decodable using the supplied tree t.
 */
char *huffman_tree_decode(huffman_tree_t *t, char *code) {
  char *string = calloc(MAX_CODE_LENGTH, sizeof(char));
  validate_pointer(string, "huffman_tree_decode");

  char *sp = string;

  huffman_tree_t *tp = t;
  for (char *p = code; *p; p++) {
    if (*p == 'L') {
      tp = tp->left;
    } else {
      tp = tp->right;
    }
    
    if (tp->letter != '\0') {
      *sp++ = tp->letter;
      tp = t;
    }
  }
  return string;
}
