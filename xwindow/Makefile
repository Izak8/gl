.POSIX:
.SUFFIXES:

CC=cc
CFLAGS	= -I/usr/local/include -D_THREAD_SAFE -pthread -Wall -std=c99
LDFLAGS	= -L/usr/local/lib -lX11

BIN=xwindow
OBJ=xwindow.o
SRC=$(OBJ:%.o=%.c)
DEP=$(OBJ:%.o=%.d)

all: $(BIN) compile_flags

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
	$(CC) $(INC) -MM $< -o $@


clean:
	rm -fr $(BIN)
	rm -fr $(OBJ)
	rm -fr $(DEP)
	
# For FreeBSD make use -include
-include $(DEP)
