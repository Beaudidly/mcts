CC= gcc
SOURCE= $(wildcard ../src/*.c ./*.c)
OBJECTS= $(patsubst %.c, %.o, $(SOURCE))
INCLUDE= -I. -I../src/
CFLAGS= -std=c11 -g $(INCLUDE) -Werror -Wall

list_test: list_test.o munit.o ../src/node_queue.o
	$(CC) $(CFLAGS) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
