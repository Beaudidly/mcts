CC= gcc
VPATH= src:../src ../tests
CFLAGS= -std=c11 -g -Werror -Wall -pedantic
TARGETS= mctsNodeTest queue_test takeawayTest stateTest

all: $(TARGETS)

queue_test: queue_test.o munit.o node_queue.o
	$(CC) $(CFLAGS) -o $@ $^ 

mctsNodeTest: mctsNodeTest.o munit.o node_queue.o mcts_node.o
	$(CC) $(CFLAGS) -o $@ $^

takeawayTest: takeawayTest.o munit.o node_queue.o takeaway_state.o
	$(CC) $(CFLAGS) -o $@ $^

mctsTest: takeaway_state.o  mcts.o mctsTest.o mcts_node.o node_queue.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

stateTest: takeaway_state.o munit.o stateTest.o node_queue.o 
	$(CC) $(CFLAGS) -o $@ $^

tmpTest: takeaway_state.o tmpTest.o node_queue.o mcts_node.o mcts.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

tests:
	./queue_test
	./mctsNodeTest
	./takeawayTest
	./stateTest


.PHONY: clean
clean:
	rm -f *.o $(TARGETS) vgcore.*

.PHONY: check

check:
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all \
		--track-origins=yes ./takeawayTest

