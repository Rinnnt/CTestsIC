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

#define assert_eq(a, b) do { asserts_ran++; if ((a) != (b)) { printf("%s(line %d): got: %d | expected: %d\n", __func__, __LINE__, a, b); asserts_failed++;} } while (0)

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

void test_trie_new() {
  trie_t *p = trie_new();
  assert_ptr_notnull(p);
  assert_ptr_isnull(p->children);
  assert_eq(p->bitfield, 0);
  trie_free(p);
}

void test_count_set_bits() {
  assert_eq(count_set_bits(3), 2);
  assert_eq(count_set_bits(0), 0);
  assert_eq(count_set_bits(-1), 32);
  assert_eq(count_set_bits(3423423), 14);
  assert_eq(count_set_bits(64), 1);
  assert_eq(count_set_bits(8321), 3);
  assert_eq(count_set_bits(7), 3);
}

// This is the trie gave as example in the spec.
trie_t l1 = {134, 1, NULL};
trie_t l2 = {265, 1, NULL};
trie_t l3 = {28, 1, NULL};
trie_t l4 = {72, 1, NULL};
trie_t l5 = {520, 1, NULL};
trie_t *t1[] = { &l1, &l2 };
trie_t n1 = {47, 8321, t1};
trie_t *t2[] = { &l4 };
trie_t n2 = {0, 256, t2};
trie_t *t3[] = { &l5 };
trie_t n3 = {144, 2097153, t3};
trie_t *t4[] = {&n2, &n3};
trie_t n4 = {30, 1075838977, t4};
trie_t *t5[] = { &n1, &l3, &n4 };
trie_t r = {0, 67375104, t5};

void test_trie_get() {
  int n = 0;
  assert_eq(trie_get(&r, "A", &n), true);
  assert_eq(n, 47);
  assert_eq(trie_get(&r, "AN", &n), true);
  assert_eq(n, 134);
  assert_eq(trie_get(&r, "AT", &n), true);
  assert_eq(n, 265);
  assert_eq(trie_get(&r, "I", &n), true);
  assert_eq(n, 28);
  assert_eq(trie_get(&r, "OF", &n), true);
  assert_eq(n, 144);

  assert_eq(trie_get(&r, "", &n), false);
  assert_eq(trie_get(&r, "   ", &n), false);
  assert_eq(trie_get(&r, "%", &n), false);
  assert_eq(trie_get(&r, "O'", &n), false);
  assert_eq(trie_get(&r, "OFFF", &n), false);
}

void test_trie_insert() {
  trie_t *p = trie_new();

  assert_ptr_notnull(p);

  // illegal inserts
  assert_eq(trie_insert(p, "&", 86), false);
  assert_eq(trie_insert(p, "$%", 86), false);
  assert_eq(trie_insert(p, "ibsdi", 86), false);

  assert_eq(p->bitfield, 0);

  // first insert
  assert_eq(trie_insert(p, "B", 66), true);
  assert_eq(p->bitfield, 33554432);
  assert_ptr_notnull(p->children);
  assert_ptr_notnull(p->children[0]);
  assert_eq(p->children[0]->bitfield, 1);
  assert_eq(p->children[0]->value, 66);

  //clean trie
  trie_free(p);
  p = trie_new();

  // insert a space (edge case first bit position)
  // if you fail this you are probably doing shifts with more than 31 positions.
  assert_eq(trie_insert(p, " ", 86), true);
  assert_eq(p->bitfield, (int) -2147483648);
  assert_ptr_notnull(p->children);
  assert_ptr_notnull(p->children[0]);
  assert_eq(p->children[0]->bitfield, 1);
  assert_eq(p->children[0]->value, 86);

  // insert same key
  assert_eq(trie_insert(p, " ", 99), true);
  assert_eq(p->bitfield, (int) -2147483648);
  assert_ptr_notnull(p->children);
  assert_ptr_notnull(p->children[0]);
  assert_eq(p->children[0]->bitfield, 1);
  assert_eq(p->children[0]->value, 99); // repeat inserted key

  // insert in order
  assert_eq(trie_insert(p, "Z", 15), true);
  assert_eq(p->bitfield, (int) -2147483646);
  assert_ptr_notnull(p->children);
  assert_ptr_notnull(p->children[1]);
  assert_eq(p->children[1]->bitfield, 1);
  assert_eq(p->children[1]->value, 15);

  // insert out of order 1
  assert_eq(trie_insert(p, "M", 420), true);
  assert_eq(p->bitfield, (int) -2147467262);
  assert_ptr_notnull(p->children);
  // check M is now first
  assert_ptr_notnull(p->children[1]);
  assert_eq(p->children[1]->bitfield, 1);
  assert_eq(p->children[1]->value, 420);
  // check Z is second
  assert_ptr_notnull(p->children[2]);
  assert_eq(p->children[2]->bitfield, 1);
  assert_eq(p->children[2]->value, 15);

  // insert out of order 2
  assert_eq(trie_insert(p, "A", 14), true);
  assert_eq(p->bitfield, (int) -2080358398);
  assert_ptr_notnull(p->children);
  // check A is now first
  assert_ptr_notnull(p->children[1]);
  assert_eq(p->children[1]->bitfield, 1);
  assert_eq(p->children[1]->value, 14);
  // check M is still before Z
  assert_ptr_notnull(p->children[2]);
  assert_eq(p->children[2]->bitfield, 1);
  assert_eq(p->children[2]->value, 420);
  // check Z is still here but last
  assert_ptr_notnull(p->children[3]);
  assert_eq(p->children[3]->bitfield, 1);
  assert_eq(p->children[3]->value, 15);

  // deep insert
  assert_eq(trie_insert(p, "A A", 7), true);
  assert_eq(p->bitfield, (int) -2080358398);
  assert_ptr_notnull(p->children);
  assert_ptr_notnull(p->children[1]);
  assert_eq(p->children[1]->bitfield, (int) -2147483647);
  assert_ptr_notnull(p->children[1]->children);
  assert_ptr_notnull(p->children[1]->children[0]);
  assert_eq(p->children[1]->children[0]->bitfield, (int) 67108864);
  assert_ptr_notnull(p->children[1]->children[0]->children);
  assert_ptr_notnull(p->children[1]->children[0]->children[0]);
  assert_eq(p->children[1]->children[0]->children[0]->bitfield, 1);
  assert_eq(p->children[1]->children[0]->children[0]->value, 7);

  // deep insert
  assert_eq(trie_insert(p, "ABA", 9), true);
  assert_eq(p->bitfield, (int) -2080358398);
  assert_ptr_notnull(p->children);
  assert_ptr_notnull(p->children[1]);
  assert_eq(p->children[1]->bitfield, (int) -2113929215);
  assert_ptr_notnull(p->children[1]->children);
  assert_ptr_notnull(p->children[1]->children[1]);
  assert_eq(p->children[1]->children[1]->bitfield, (int) 67108864);
  assert_ptr_notnull(p->children[1]->children[1]->children);
  assert_ptr_notnull(p->children[1]->children[1]->children[0]);
  assert_eq(p->children[1]->children[1]->children[0]->bitfield, 1);
  assert_eq(p->children[1]->children[1]->children[0]->value, 9);


  trie_free(p);
}

void run_part_a() {
  tests_ran = 0;
  tests_failed = 0;
  run_test(test_trie_new);
  run_test(test_count_set_bits);
  run_test(test_trie_get);
  run_test(test_trie_insert);
  if (tests_failed == 0) {
    printf("********************\n"
           "Part A -- WELL DONE!\n"
           "********************\n");
  } else {
    printf("****************************************************\n"
           "Part A has %d incorrect functions out of %d tested\n"
           "****************************************************\n\n",
           tests_failed, tests_ran);
  }
}

#ifdef TESTING

int main(int argc, char **argv) {
	run_part_a();
	return EXIT_SUCCESS;
}

#endif
