#include "binaryheap.h"
#include <string.h>

#define MAX_LENGTH 20

int main(int argc, char **argv){
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <string>", argv[0]);
    return -1;
  }

  int len = strlen(argv[1]);
  node_heap *heap[MAX_LENGTH];
  initial_heap(heap, argv[1]);

  print_elem_heap(heap, len);
  
  build_max_heap(heap, len);

  print_elem_heap(heap, len);

  heapsort(heap, len);

  print_elem_heap(heap, len);

  free_heap(heap, len);
  return 0;
}
