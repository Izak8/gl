.POSIX:
.SUFFIXES:

CC=clang
CFLAGS=-Wall -std=c99

# Include and Library paths
LDFLAGS=-L/usr/local/lib

BIN=xclient

# Link with libX11.so
LIB=-lX11
INC=-I/usr/local/include

OBJ=xclient.o
SRC=$(OBJ:%.o=%.c)
DEP=$(OBJ:%.o=%.d)

all: $(BIN) compile_flags.txt

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(LDFLAGS) $(LIB) $(OBJ) -o $@ 

# clangd compile_flags.txt
compile_flags.txt:
	echo "$(LDFLAGS) $(CFLAGS) $(INC)" | tr ' ' '\n' > $@

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
