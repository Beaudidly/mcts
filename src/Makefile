CC= gcc
VPATH= src:./
CFLAGS= -std=c11 -g -Wall

takeaway_state: takeaway_state.o node_queue.o 
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
	
clean:
	rm -f *.o takeaway_state vgcore.*
