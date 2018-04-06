CFLAGS=-Wall -g -fsanitize=address

test: test.c libflattree.c libflattree.h
	$(CC) $(CFLAGS) test.c libflattree.c -o test

clean:
	rm -fv test
