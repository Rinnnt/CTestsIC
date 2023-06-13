#include "binaryheap.h"
#include <assert.h>
#include <string.h>



/*allocate memory in the heap for a node_heap type element and returns a pointer to the new node_heap*/

node_heap *allocate_node_heap(void)
{
  node_heap *node = malloc(sizeof(node_heap));
  if (node == NULL) {
    perror("allocate_node_heap");
    exit(EXIT_FAILURE);
  }
  return node;
}

/*initialise the heap array elements*/

void initial_heap(node_heap **heap,char* sequence)
{
  for (char *p = sequence; *p; p++) {
    node_heap *node = allocate_node_heap();
    node->key = p;
    node->position = p - sequence + 1;
    *++heap = node;
  }
}


/*print every element of the heap array*/
void print_elem_heap(node_heap **heap, int length)
{
  for (node_heap **h = heap + 1; h - heap <= length; h++) {
    printf("%c ", *((*h)->key));
  }
  printf("\n");
  for (node_heap **h = heap + 1; h - heap <= length; h++) {
    printf("%d ", (*h)->position);
  }
  printf("\n");
}

/* returns the index in the heap array where the parent is allocated for the index passed as argument*/

int parent(int index)
{
  return index / 2;
}

/* returns the index in the heap array where the left child is allocated for the index passed as argument*/

int left_child(int index)
{
  return 2 * index;
}

/* returns the index in the heap array where the right child is allocated for the index passed as argument*/

int right_child(int index)
{
  return 2 * index + 1;
}

/* exchange node_heap node1 to node_heap node2*/ 

void swap(node_heap *node1, node_heap *node2)
{
  char *tempc = node1->key;
  int temp = node1->position;
  node1->key = node2->key;
  node1->position = node2->position;
  node2->key = tempc;
  node2->position = temp;
}

/*Moves down the value of the heap[current] so the subtree rooted at index "current" satisfies with the max-heap property*/ 

void max_heapify(node_heap **heap, int current, int heap_size)
{
  int lc = left_child(current);
  if (lc > heap_size) {
    return;
  }

  int rc = right_child(current);
  int bc = (rc > heap_size || *(heap[lc]->key) > *(heap[rc]->key)) ? lc : rc;
  if (*(heap[current]->key) < *(heap[bc]->key)) {
    swap(heap[current], heap[bc]);
    max_heapify(heap, bc, heap_size);
  }
}

/*it orders the heap so the ordered heap complies the max-heap property*/

void build_max_heap(node_heap **heap, int heap_size)
{
  for (int i = heap_size / 2; i > 0; i--) {
    max_heapify(heap, i, heap_size);
  }
}

/*starting from a max-heap ordered array, it moves the largest item from the heap and it into the array position left as the heap shrinks*/

void heapsort(node_heap **heap, int length)
{
  build_max_heap(heap, length);
  while (length > 0) {
    swap(heap[1], heap[length--]);
    max_heapify(heap, 1, length);
  }
}

/*free the memory allocated by a node_heap type element in the heap*/

void free_node(node_heap *node)
{
  free(node);
}

/*free the memory allocated in the heap array*/

void free_heap(node_heap **heap, int length)
{
  for (int i = 1; i <= length; i++) {
    free_node(heap[i]);
  }
}
