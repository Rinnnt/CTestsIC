#ifndef __SONNET_H__
#define __SONNET_H__

#include "maps.h"
#include "trie.h"

#include <stdio.h>
#include <stdbool.h>

#ifdef MY_TRIE
#define dict_t trie_t
  #define dict_new trie_new
  #define dict_free trie_free
  #define dict_insert trie_insert
  #define dict_get trie_get
#else
#define dict_t strintmap_t
#define dict_new strintmap_new
#define dict_free strintmap_free
#define dict_insert strintmap_insert
#define dict_get strintmap_get
#endif

char *uppercase(char *str);

char *lastwordtok(char *line);

const char *strrhyme(const char *str);

dict_t *load_rhyme_mappings_from_file(const char *phonetic_dict_filename);

bool next_rhyme_scheme(FILE *sonnets_file, const dict_t *rhyme_mappings, char *out);

void most_common_rhyme_scheme(FILE *sonnets_file, const dict_t *rhyme_mappings, char *out);

#endif // SONNET_H
