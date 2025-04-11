.POSIX:
.SUFFIXES:

CC=clang
CFLAGS=-Wall -std=c99 -I/usr/local/include

# Include and Library paths
LDFLAGS=-L/usr/local/lib

BIN=xclient

# Link with libX11.so
LIB=-lX11

OBJ=xclient.o
SRC=$(OBJ:%.o=%.c)
DEP=$(OBJ:%.o=%.d)

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIB) $(OBJ) -o $@ 

.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -c $<

.SUFFIXES: .c .d

.c.d:
	$(CC) -MM $< -o $@

clean:
	rm -fr $(BIN)
	rm -fr $(OBJ)
	rm -fr $(DEP)

# For FreeBSD make use -include
-include $(DEP)
