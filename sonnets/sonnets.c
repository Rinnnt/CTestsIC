#include "sonnets.h"
#include "maps.h"

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Checks that files were opened correctly.
#define FILECHECK(ptr, msg) if (!(ptr)) perror(msg), exit(EXIT_FAILURE)
#define ASSERT_PTR_NOT_NULL(ptr, msg) if (!(ptr)) perror(msg), exit(EXIT_FAILURE)

// Returns a pointer to the last word in line, or NULL if there are no words.
// This function adds a sentinel '\0' after the word.
char *lastwordtok(char *line) {
  assert(line);
  int pos = -1;
  for (int i = 0; line[i];  ++i) if (isalpha(line[i])) pos = i;
  if (pos == -1) return NULL;
  line[pos + 1] = '\0';
  while(pos >= 0 && line[--pos] != ' ');
  while(!isalpha(line[++pos]));
  return line + pos;
}

char *uppercase(char *str) {
  for (char *c = str; *c; c++) {
    *c = toupper(*c);
  }
  return str;
}

#define VOWELS "AEIOU"

static bool contains(char *str, char c) {
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == c) {
      return true;
    }
  }
  return false;
}

const char *strrhyme(const char *phonemes) {
  const char *rhyme = NULL;
  const char *phoneme = phonemes;

  while (*phoneme) {
    if (contains(VOWELS, *phoneme)) {
      rhyme = phoneme;
    }

    while (*++phoneme && *(phoneme - 1) != ' ');
  }

  return (rhyme == NULL) ? phonemes : rhyme;
}

#define MAX_DICT_LINE_LENGTH 120

static char * firstwordtok(char *str, char **rest) {
  for (char *c = str; *c; c++) {
    if (*c == ' ') {
      *c = '\0';
      *rest = c + 1;
      return str;
    }
  }
  return str;
}

// Assume the given file is formatted correctly and formed only of characters
// that are supported by the alphabet from PART A.
dict_t *load_rhyme_mappings_from_file(const char *phonetic_dict_filename) {
  dict_t *dict = dict_new();
  dict_t *rhyme_dict = dict_new();
  FILE *fp = fopen(phonetic_dict_filename, "r");
  FILECHECK(fp, "load_rhyme_mappings_from_file");

  int unique_id = 0;
  char buf[MAX_DICT_LINE_LENGTH + 1];
  while (fgets(buf, MAX_DICT_LINE_LENGTH + 1, fp) != NULL) {
    buf[strlen(buf) - 1] = '\0';
    char *phonemes;
    char *word = firstwordtok(buf, &phonemes);
    int id;
    const char *rhyme = strrhyme(phonemes);
    if (dict_get(rhyme_dict, rhyme, &id)) {
      dict_insert(dict, word, id);
    } else {
      id = unique_id++;
      dict_insert(rhyme_dict, rhyme, id);
      dict_insert(dict, word, id);
    }
  }
  dict_free(rhyme_dict);
  fclose(fp);
  return dict;
}

static bool hasword(char *buf) {
  for (int i = 0; i < strlen(buf); i++) {
    if (isalpha(buf[i])) {
      return true;
    }
  }
  return false;
}

#define MAX_SONNET_LINE_LENGTH 80

bool next_rhyme_scheme(FILE *sonnets_file,
                       const dict_t *rhyme_mappings, char *out) {
  FILECHECK(sonnets_file, "next_rhyme_scheme");
  char buf[MAX_SONNET_LINE_LENGTH + 1] = "";
  while (!hasword(buf)) {
    if (fgets(buf, MAX_SONNET_LINE_LENGTH + 1, sonnets_file) == NULL) {
      return false;
    }
  }

  int unique_id = 0;
  intcharmap_t *dict = intcharmap_new();
  while (hasword(buf)) {
    int id;
    char *last = uppercase(lastwordtok(buf));
    if (!dict_get(rhyme_mappings, last, &id)) {
      fprintf(stderr, "word not found: %s", last);
      exit(EXIT_FAILURE);
    }

    char c;
    if (!intcharmap_get(dict, id, &c)) {
      c = 'A' + unique_id++;
      intcharmap_insert(dict, id, c);
    }
    *out++ = c;
    *out = '\0';

    if (fgets(buf, MAX_SONNET_LINE_LENGTH + 1, sonnets_file) == NULL) {
      intcharmap_free(dict);
      return true;
    }
  }

  intcharmap_free(dict);
  return true;
}

#define MAX_NUM_SONNET_LINES 20

void most_common_rhyme_scheme(FILE *sonnets_file,
                              const dict_t *rhyme_mappings, char *out) {
  FILECHECK(sonnets_file, "most_common_rhyme_scheme");
  dict_t *dict = dict_new();
  char rhyme_scheme[MAX_NUM_SONNET_LINES + 1];
  int max = 0;
  while (next_rhyme_scheme(sonnets_file, rhyme_mappings, rhyme_scheme)) {
    int n;
    if (dict_get(dict, rhyme_scheme, &n)) {
      n++;
    } else {
      n = 1;
    }
    dict_insert(dict, rhyme_scheme, n);
    if (n >= max) {
      max = n;
      strcpy(out, rhyme_scheme);
    }
  }
  if (max == 0) {
    strcpy(out, "N/A");
  }

  dict_free(dict);
}


#ifdef SONNETS_MAIN

#define PHONETIC_DICT_FILE "dictionary.txt"

/* TODO: DO NOT MODIFY THIS FUNCTION!!! Remember to run:
 *  valgrind --leak-check=full --show-leak-kinds=all ./sonnets_map or
 *  valgrind --leak-check=full --show-leak-kinds=all ./sonnets_trie if your
 *  PART A is correct and want to see how much faster it is
 */
int main (void) {
  dict_t *rhyme_mappings = load_rhyme_mappings_from_file(PHONETIC_DICT_FILE);

  char *sonnets_files[3] = {"shakespeare.txt", "spenser.txt", "petrarch.txt"};
  for (int i = 0; i < 3; ++i) {
    FILE *f = fopen(sonnets_files[i], "r");
    FILECHECK(f, sonnets_files[i]);

    char rhyme_scheme[MAX_NUM_SONNET_LINES];
    most_common_rhyme_scheme(f, rhyme_mappings, rhyme_scheme);
    printf("The most common rhyme scheme of sonnets from %s is: %s\n",
           sonnets_files[i], rhyme_scheme);
    fclose(f);
  }

  dict_free(rhyme_mappings);
  return EXIT_SUCCESS;
}

#endif
