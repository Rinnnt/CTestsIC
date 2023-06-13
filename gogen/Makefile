CC = gcc
CFLAGS = -std=c99 -g -Wall -Wno-unused-value -Wno-char-subscripts -lm
SRCS = gogen.c letter_mask.c

all: letter_mask gogen testA testB

letter_mask: letter_mask.c letter_mask.h
	$(CC) $(CFLAGS) -DMAIN_LETTER_MASK -o letter_mask letter_mask.c

gogen: letter_mask.c letter_mask.h gogen.c gogen.h
	$(CC) $(CFLAGS) -DMAIN_GOGEN -o gogen gogen.c letter_mask.c

testA: letter_mask.c letter_mask.h testA.c
	$(CC) $(CFLAGS) -o testA testA.c letter_mask.c

testB: letter_mask.c letter_mask.h gogen.c gogen.h testB.c
	$(CC) $(CFLAGS) -o testB testB.c gogen.c letter_mask.c

clean:
	$(RM) -rf testA testB gogen letter_mask *.o *~ *.dSYM
