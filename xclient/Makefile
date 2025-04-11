.POSIX:
.SUFFIXES:
.PHONY: clean all

CC=clang
CFLAGS=-Wall -std=c99

BIN=xclient

OBJ=xclient.o
SRC=$(OBJ: %.o = %.c)
DEP=$(OBJ: %.o = %.d)

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -c $<

.SUFFIXES: .c .d

.c.d:
	$(CC) -MM $< -o $@

clean:
	rm -fr $(DEP)
	rm -fr $(OBJ)
	rm -fr $(BIN)

# For FreeBSD make use -include
include $(DEP)
