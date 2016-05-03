# Makefile
#
# Define the C compiler

CC      = gcc

CFLAGS  = -Wall -Wextra -g -O0

# Define any libraries to be linked
LIB		=

# Define the source, header and object files
HDR		= my_malloc.h disjoint_set.h graph.h graphio.h kruskal.h
SRC		= my_malloc.c disjoint_set.c graph.c graphio.c kruskal.c main.c
OBJ     = $(SRC:.c=.o)

# The executable name
TARGET	= kruskal

.PHONY: all
all: $(TARGET) graphgen

$(TARGET): $(OBJ) Makefile
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIB)

graphgen: ./graphgen.c
	$(CC) $(CFLAGS) -o graphgen ./graphgen.c

.PHONY: clean
clean:
	rm -f $(OBJ) test/tmp.*


.PHONY: test
test: $(TARGET) graphgen
	./graphgen 2 > test/tmp.txt
	./$(TARGET) < test/tmp.txt > test/tmp.out.txt


$(OBJ): $(HDR)
