#include "doublets.h"
#include <assert.h>

#define ALPHABET_SIZE 26

/* ------------------ YOUR CODE HERE ------------------- */

bool valid_step(dictionary_t *dict, const char *curr_word, const char *next_word) {
  if (!find(dict, curr_word) || !find(dict, next_word)) {
    return false;
  }
  
  if (strlen(curr_word) != strlen(next_word)) {
    return false;
  }

  bool diff = false;
  for (int i = 0; i < strlen(curr_word); i++) {
    if (curr_word[i] != next_word[i]) {
      if (diff) {
	return false;
      } else {
	diff = true;
      }
    }
  } 
  return diff;
}

void print_chain(const char **chain) {
  for (const char **cs = chain; *cs; cs++) {
    if (cs == chain || *(cs + 1) == NULL) {
      for (const char *c = *cs; *c; c++) {
	printf("%c", toupper(*c));
      }
    } else {
      for (const char *c = *cs; *c; c++) {
	printf("%c", tolower(*c));
      }
    }
    printf("\n");
  }
}

bool valid_chain(dictionary_t *dict, const char **chain) {
  for (int i = 0; chain[i] != NULL; i++) {
    for (int j = i + 1; chain[j] != NULL; j++) {
      if (strcmp(chain[i], chain[j]) == 0) {
	return false;
      }
    }
  }

  for (int i = 1; chain[i] != NULL; i++) {
    if (!valid_step(dict, chain[i - 1], chain[i])) {
      return false;
    }
  }

  return true;
}

bool find_chain(dictionary_t *dict, const char *start_word, 
                const char *target_word, const char **chain, int max_words) {
  assert(dict != NULL);
  assert(start_word != NULL);
  assert(target_word != NULL);

  if (max_words < 2) {
    return false;
  }

  char *buf = malloc((MAX_WORD_SIZE + 1) * sizeof(char));
  strcpy(buf, start_word);

  if (max_words == 2) {
    if (!valid_step(dict, start_word, target_word)) {
      return false;
    } else {
      char *buf2 = malloc((MAX_WORD_SIZE + 1) * sizeof(char));
      strcpy(buf2, target_word);
      chain[0] = buf;
      chain[1] = buf2;
      return true;
    }
  }

  for (int i = 0; i < strlen(start_word); i++) {
    char c = buf[i];
    for (int j = 0; j < ALPHABET_SIZE; j++) {
      buf[i] = 'A' + j;
      if (find(dict, buf)) {
	if (find_chain(dict, buf, target_word, chain + 1, max_words - 1)) {
	  buf[i] = c;
	  *chain = buf;
	  if (valid_chain(dict, chain)) {
	    return true;
	  }
	}
      }
    }
    buf[i] = c;
  }

  free(buf);
  return false;
}

