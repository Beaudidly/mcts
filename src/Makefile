CC= gcc
VPATH= src:./
CFLAGS= -std=c11 -g -Werror -Wall

test: test.o node_queue.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
	
clean:
	rm -f *.o test vgcore.*
