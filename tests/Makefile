CC= gcc
VPATH= src:../src ../tests
CFLAGS= -std=c11 -g -Werror -Wall -pedantic
TARGETS= mctsNodeTest queue_test

all: $(TARGETS)

queue_test: queue_test.o munit.o node_queue.o
	$(CC) $(CFLAGS) -o $@ $^ 

mctsNodeTest: mctsNodeTest.o munit.o node_queue.o mcts_node.o
	$(CC) $(CFLAGS) -o $@ $^

tests:
	./queue_test
	./mctsNodeTest


.PHONY: clean
clean:
	rm -f *.o $(TARGETS) vgcore.*

.PHONY: check

check:
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all \
		--track-origins=yes ./queue_test 
