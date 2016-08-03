CFLAGS= -Wall -Wextra -std=c11 $(OPTFLAGS)

# Main source files for the program
SOURCES=$(wildcard  src/*.c)
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))

# Test sources
TEST_SOURCES=$(wildcard ./tests/*.c)
TEST_OBJECTS=$(patsubst %.c, %.o, $(TEST_SOURCES))
