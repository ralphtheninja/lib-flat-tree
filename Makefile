CFLAGS=-Wall -g -fsanitize=address

test: test.c libflattree.c libflattree.h
	$(CC) test.c libflattree.c -o test

clean:
	rm -rf test
