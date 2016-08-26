CC= gcc
VPATH= src:./ ../obj ./games/takeaway
INC= -I./
CFLAGS= -std=c11 -g -Wall -lm
GAMEOBJECTS= mcts.o mcts_node.o node_queue.o

BINDIR= ../bin
OBJDIR= ../obj

takeaway: takeaway.o takeaway_state.o $(GAMEOBJECTS)
	$(CC) $(CFLAGS) $(INC) -o $(BINDIR)/$@ $(OBJDIR)/$^

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $(OBJDIR)/$@

.PHONY: clean
	
clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/* vgcore.*
