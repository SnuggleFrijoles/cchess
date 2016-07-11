# Use gcc compiler
CC = gcc

# -g : Include debugging information
# -Wall, -Werror : Show all errors and warnings
# -O2 : Do 2nd level optimization
CFLAGS = -g -Wall -Werror -O2

# Object files to build to prevent unnecessary compilation
OBJECTS = board.o piece.o valid.o cchess.o 

# Linker flags
LDFLAGS = 

# Default target that gets called by make
default : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o cchess 

# Make object files
%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean object files and binaries
clean:
	rm *.o
	rm cchess
