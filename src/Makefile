CC= gcc
VPATH= src:./
CFLAGS= -std=c11 -g -Wall

tmptest: tmptest.o node_queue.o mcts_node.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
	
clean:
	rm -f *.o test vgcore.*
