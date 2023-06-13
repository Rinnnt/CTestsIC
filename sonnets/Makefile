CC = gcc
CFLAGS = -std=c99 -g -Wall -Wno-unused-value -Wno-char-subscripts
SRCS = sonnets.c trie.c maps.c

all: testA testB trie sonnets_trie sonnets_map

trie:  clean
	$(CC) $(CFLAGS) -DTRIE_MAIN -o trie trie.c

sonnets_trie:  clean
	$(CC) $(CFLAGS) -DSONNETS_MAIN -DMY_TRIE -o sonnets_trie $(SRCS)

sonnets_map:  clean
	$(CC) $(CFLAGS) -DSONNETS_MAIN -o sonnets_map $(SRCS)

testA:  clean
	$(CC) $(CFLAGS) -DTESTING -o testA testA.c trie.c

testB:  clean
	$(CC) $(CFLAGS) -DTESTING -o testB testB.c $(SRCS)

clean:
	$(RM) -rf testA testB trie sonnets_map sonnets_trie *.o *~ *.dSYM
