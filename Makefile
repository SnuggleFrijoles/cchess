TARGET = cchess

CC = gcc
# Use gcc compiler

CFLAGS = -Wall -Werror -Isrc/include
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
INCLUDEDIR = src/include
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCLUDEDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

all: release
	echo Compiling $(CLION_EXE_DIR)/$@ ...

debug: CFLAGS += $(DEBUGFLAGS) 
debug: $(BINDIR)/$(TARGET)

release: CFLAGS += $(RELEASEFLAGS) 
release: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p bin
	$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	#$(LINKER) $(CLION_EXE_DIR)/cchess $(LFLAGS) $(OBJECTS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

.PHONEY: clean
clean:
	$(rm) $(OBJECTS)

.PHONEY: remove
remove: clean
	$(rm) $(BINDIR)/$(TARGET)
