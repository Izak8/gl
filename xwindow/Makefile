.POSIX:
.SUFFIXES:

CC		= cc
CFLAGS	= -Wall -std=c99

PC		= pkg-config

# Project Files
BIN=xwindow
OBJ=xwindow.o
SRC=$(OBJ:%.o=%.c)
DEP=$(OBJ:%.o=%.d)

# Libraries
LIB=x11

CFLAGS	+= `$(PC) --cflags $(LIB)`
LDFLAGS	 = `$(PC) --libs $(LIB)`

all: $(BIN)

# Build binary from objects
$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

# clangd compile_flags.txt
compile_flags:
	echo "$(LDFLAGS) $(CFLAGS)" | tr ' ' '\n' > $@.txt

# Suffix rules to create .o and .d files from sources
.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) $(INC) -c $<

.SUFFIXES: .c .d
.c.d:
	$(CC) -MM $< -o $@

clean:
	rm -fr $(BIN)
	rm -fr $(OBJ)
	rm -fr $(DEP)
	
# For FreeBSD make use -include
-include $(DEP)
