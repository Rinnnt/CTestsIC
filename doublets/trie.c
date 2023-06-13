#include "trie.h"
#include <ctype.h>
#include <assert.h>

#define ALPHABET_SIZE 26
#define ASCII_UPPERCASE_A 65

dictionary_t *create_dict(void) {
  return create_node();
}

void free_dict(dictionary_t *root) {
  free_node(root);
}

/* ------------ YOUR CODE BELOW -------------- */

bool find(dictionary_t *root, const char *word) {
  if (word == NULL) {
    return false;
  }

  dictionary_t *trie = root;
  for (int i = 0; i < strlen(word); i++) {
    if (!isalpha(word[i])) {
      return false;
    }

    int index = word[i] - ASCII_UPPERCASE_A;

    if (trie->children[index] == NULL) {
      return false;
    }
    trie = trie->children[index];
  }
  return trie->end_of_word;
}

bool insert(dictionary_t *root, const char *word) {
  assert(word != NULL);
  assert(strlen(word) > 0);

  dictionary_t *trie = root;
  for (int i = 0; i < strlen(word); i++) {
    if (!isalpha(word[i])) {
      return false;
    }

    int index = word[i] - ASCII_UPPERCASE_A;

    if (trie->children[index] == NULL) {
      dictionary_t *new_node = create_node();
      trie->children[index] = new_node;
    }
    trie = trie->children[index];
  }

  trie->end_of_word = true;
  return true;
}

dictionary_t *create_node(void) {
  dictionary_t *node = malloc(sizeof(dictionary_t));
  if (node == NULL) {
    perror("create_node");
    exit(EXIT_FAILURE);
  }

  node->children = malloc(ALPHABET_SIZE * sizeof(dictionary_t *));
  if (node->children == NULL) {
    free(node);
    perror("create_node");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    node->children[i] = NULL;
  }
  node->end_of_word = false;
}

void free_node(dictionary_t *root) {
  if (root == NULL) {
    return;
  }

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    free_node(root->children[i]);
  }

  free(root->children);
  free(root);
}

bool load_from_file(dictionary_t *root, const char *filename) {
  char buffer[MAX_WORD_SIZE + 1];
  FILE * fp;
  fp = fopen(filename, "r");
  if (fp == NULL) {
    return false;
  }

  while (fgets(buffer, MAX_WORD_SIZE + 1, fp) != NULL) {
    if (buffer[strlen(buffer) - 1] == '\n') {
      buffer[strlen(buffer) - 1] = '\0';
    }
    insert(root, buffer);
  }

  return true;
}


