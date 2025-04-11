.POSIX:
.SUFFIXES:
.PHONY: clean all

CC=clang
CFLAGS=-Wall -std=c99 -I/usr/local/include

# Include and Library paths
LDFLAGS=-L/usr/local/lib

BIN=xclient

# Link with libX11.so
LIB=-lX11

OBJ=xclient.o
SRC=$(OBJ: %.o = %.c)
DEP=$(OBJ: %.o = %.d)

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@ $^

.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -c $<

.SUFFIXES: .c .d

.c.d:
	$(CC) -MM $< -o $@

clean:
	rm -fr $(DEP)
	rm -fr $(OBJ)
	rm -fr $(BIN)

# For FreeBSD make use -include
-include $(DEP)
