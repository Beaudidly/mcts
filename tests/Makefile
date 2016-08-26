CC= gcc
VPATH= src:../src  ./obj
INC= -I../src -I../src/games/takeaway
CFLAGS= -std=c11 -g3 -Werror -Wall -pedantic -D _TEST_
BINDIR= ./bin
OBJDIR= ./obj
TARGETS= mctsNodeTest queue_test takeawayTest stateTest mctsTest

all: $(TARGETS)

queue_test: queue_test.o munit.o node_queue.o
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(OBJDIR)/$^ 

mctsNodeTest: mctsNodeTest.o munit.o node_queue.o mcts_node.o takeaway_state.o
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^

takeawayTest: takeawayTest.o munit.o node_queue.o takeaway_state.o
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^

mctsTest: takeaway_state.o  mcts.o mctsTest.o mcts_node.o node_queue.o
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^ -lm

stateTest: takeaway_state.o munit.o stateTest.o node_queue.o 
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $^ -o $(OBJDIR)/$@


tests: $(TARGETS)
	./queue_test
	./mctsNodeTest
	./stateTest
	./takeawayTest

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/* vgcore.*

.PHONY: check

check:
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all \
		--track-origins=yes ./takeawayTest

