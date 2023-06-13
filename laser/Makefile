CC = gcc
CFLAGS = -std=c99 -g -Wall

laser:  clean
	$(CC) $(CFLAGS) -DMAIN laser.c -o laser

test:  clean
	$(CC) $(CFLAGS) -DTEST laser.c test.c -o test

clean:
	$(RM) -rf test laser *.o *~ *.dSYM
