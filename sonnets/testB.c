#include "sonnets.h"
#include "trie.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int asserts_ran = 0, asserts_failed = 0, tests_ran = 0, tests_failed = 0;

#define assert_str_eq(a, b) do { asserts_ran++; if (a == NULL || strcmp((a), (b)) != 0) { printf("%s(%d): got: %s | expected: %s\n", __func__, __LINE__, a, b); asserts_failed++; } } while (0)

#define assert_eq(a, b) do { asserts_ran++; if ((a) != (b)) { printf("%s(line %d): got: %d | expected: %d\n", __func__, __LINE__, a, b); asserts_failed++; } } while (0)

#define assert_ptr_isnull(p) do { asserts_ran++; if (p != NULL) { printf("%s(line %d): got: %p | expected NULL\n", __func__, __LINE__, p); asserts_failed++; } } while (0)

#define assert_ptr_notnull(p) do { asserts_ran++; if (p == NULL) { printf("%s(line %d): pointer should not be NULL\n", __func__, __LINE__); asserts_failed++; return;} } while (0)

#define run_test(test) do { \
asserts_ran = asserts_failed = 0; test(); \
tests_ran++;\
if (asserts_failed > 0) { \
tests_failed++; \
 printf("****%s: %d asserts failed out of %d asserts\n\n", #test, asserts_failed, asserts_ran); \
 }\
} while (0)

void test_uppercase() {
  char a[] = "";
  assert_str_eq(uppercase(a), "");
  char b[] = "uyfgu";
  assert_str_eq(uppercase(b), "UYFGU");
  char c[] = "uy- - -fgu";
  assert_str_eq(uppercase(c), "UY- - -FGU");
  char d[] = "8937248923";
  assert_str_eq(uppercase(d), "8937248923");
  char e[] = "   3dfsdf 3 3 3";
  assert_str_eq(uppercase(e), "   3DFSDF 3 3 3");
}

void test_strrhyme() {
  assert_str_eq(strrhyme("EY B IH D"), "IH D");
  assert_str_eq(strrhyme("AH K AA M P L IH SH M AH N T S"), "AH N T S");
  assert_str_eq(strrhyme("AE K"), "AE K");
  assert_str_eq(strrhyme("TH S"), "TH S");
  assert_str_eq(strrhyme("AE FH S"), "AE FH S");
}

void test_load_rhyme_mappings_from_file() {
  dict_t *d = load_rhyme_mappings_from_file("dictionary.txt");
  int a, b;
  assert_ptr_notnull(d);

  assert_eq(dict_get(d, "SPACIOUS", &a), true); // can get value

  assert_eq(dict_get(d, "DY'D", &a), true);
  assert_eq(dict_get(d, "STRUMPETED", &b), true);
  assert_eq(a, b); // returns the same value for rhyming words

  // cannot get missing values
  assert_eq(dict_get(d, "", &a), false);
  assert_eq(dict_get(d, "SPACIOU", &a), false);
  assert_eq(dict_get(d, "3DO", &a), false);
  assert_eq(dict_get(d, "invalid", &a), false);
  dict_free(d);
}

void test_next_rhyme_scheme() {
  dict_t *d = load_rhyme_mappings_from_file("dictionary.txt");
  FILE *f = fopen("spenser.txt", "r");
  char rs[20];
  assert_eq(next_rhyme_scheme(f, d, rs), true);
  assert_str_eq(rs, "ABABBCBCCDCDEE");
  assert_eq(next_rhyme_scheme(f, d, rs), true);
  assert_str_eq(rs, "ABABBCBCCDCEFG");
  assert_eq(next_rhyme_scheme(f, d, rs), true);
  assert_str_eq(rs, "ABABBCBDDECFGG");

  // 2 empty lines in spenser.txt
  assert_eq(next_rhyme_scheme(f, d, rs), true);
  assert_str_eq(rs, "ABCBBDBDDEDEFF");

  // 2 empty lines and one with symbols in spenser.txt
  assert_eq(next_rhyme_scheme(f, d, rs), true);
  assert_str_eq(rs, "ABABBCBCCDCDEE");

  // no more lines
  assert_eq(next_rhyme_scheme(f, d, rs), false);

  assert_eq(next_rhyme_scheme(f, d, rs), false);

  dict_free(d);

  fclose(f);
}

void test_most_common_rhyme_scheme() {
  dict_t *d = load_rhyme_mappings_from_file("dictionary.txt");
  FILE *f = fopen("petrarch.txt", "r");
  char rs[20];
  most_common_rhyme_scheme(f, d, rs);
  assert_str_eq(rs, "ABBAABBACDECDE");

  fclose(f);

  f = fopen("empty.txt", "r");
  most_common_rhyme_scheme(f, d, rs);
  assert_str_eq(rs, "N/A");

  dict_free(d);

  fclose(f);
}


void run_part_b() {
  tests_ran = 0;
  tests_failed = 0;
  run_test(test_uppercase);
  run_test(test_strrhyme);
  run_test(test_load_rhyme_mappings_from_file);
  run_test(test_next_rhyme_scheme);
  run_test(test_most_common_rhyme_scheme);
  if (tests_failed == 0) {
    printf("********************\n"
           "Part B -- WELL DONE!\n"
           "********************\n");
  } else {
    printf("****************************************************\n"
           "Part B has %d incorrect functions out of %d tested\n"
           "****************************************************\n\n",
           tests_failed, tests_ran);
  }
}

#ifdef TESTING

int main(int argc, char **argv) {
  run_part_b();
	return EXIT_SUCCESS;
}

#endif
