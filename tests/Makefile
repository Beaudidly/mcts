CC= gcc
VPATH= src:../src ../tests
CFLAGS= -std=c11 -g -Werror -Wall

list_test: list_test.o munit.o ../src/node_queue.o
	$(CC) $(CFLAGS) -o $@ $^ 
	./list_test

.PHONY: clean
clean:
	rm -f *.o ./list_test vgcore.*

.PHONY: check

check:
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./list_test
