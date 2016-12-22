TARGET = cchess

CC = gcc
# Use gcc compiler

CFLAGS = -Wall -Werror
# -Wall : Show all errors
# -Werror : Make warnings errors

DEBUGFLAGS = -g -DDEBUG
# -g : Include debugging information
# -DDEBUG : #define DEBUG

RELEASEFLAGS = -O3
# -O3 : Highest level optimization

LINKER   = gcc -o 
LFLAGS   = -Wall -I. -lm 

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

all: release

debug: CFLAGS += $(DEBUGFLAGS) 
debug: $(BINDIR)/$(TARGET)

release: CFLAGS += $(RELEASEFLAGS) 
release: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS)
	$(LINKER) $@ $(LFLAGS) $(OBJECTS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONEY: clean
clean:
	$(rm) $(OBJECTS)

.PHONEY: remove
remove: clean
	$(rm) $(BINDIR)/$(TARGET)
