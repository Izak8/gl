.POSIX:
.SUFFIXES:

# Use the system's default C compiler
CC		= cc
CFLAGS	= -Wall -std=c99

# Pathname of the pkg-config compatible utility
PC		= pkg-config

# Instructions to create an LSP db -- default is clangd with compile_flags.txt
# To use bear you can set DB="bear -- make" which will create compile_commands.json
DB		= echo $(LDFLAGS) $(CFLAGS) | tr ' ' '\n' > compile_flags.txt

# Project Files
BIN=xwindow
OBJ=xwindow.o
SRC=$(OBJ:%.o=%.c)
DEP=$(OBJ:%.o=%.d)

# Packages -- in this case x11.pc 
# Could be set to link with libGL.so by adding gl to this variable
PKG=x11
CFLAGS	+= `$(PC) --cflags $(PKG)`
LDFLAGS	 = `$(PC) --libs $(PKG)`

all: $(BIN)

# Build binary from objects
$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

# Suffix rules to create .o and .d files from sources
.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) $(INC) -c $<

.SUFFIXES: .c .d
.c.d:
	$(CC) -MM $< -o $@

# Generate LSP database on each clean
clean:
	$(DB)
	rm -fr $(BIN)
	rm -fr $(OBJ)
	rm -fr $(DEP)
	
# For FreeBSD make use -include
-include $(DEP)
