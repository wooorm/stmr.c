PREFIX ?= /usr/local

SRC = stmr.c
CLI = stmr-cli.c $(SRC)
TEST = test.c $(SRC)

OBJ_SRC = $(SRC:.c=.o)
OBJ_CLI = $(CLI:.c=.o)
OBJ_TEST = $(TEST:.c=.o)

CFLAGS = -D_GNU_SOURCE -std=c99 \
    -Wall -Wno-format-y2k -W -Wstrict-prototypes -Wmissing-prototypes \
    -Wpointer-arith -Wreturn-type -Wcast-qual -Wwrite-strings -Wswitch \
    -Wshadow -Wcast-align -Wbad-function-cast -Wchar-subscripts -Winline \
    -Wnested-externs -Wredundant-decls

stmr: $(OBJ_CLI)
	$(CC) $(OBJ_CLI) -o $@

test: $(OBJ_TEST)
	$(CC) $(OBJ_TEST) -o $@

.SUFFIXES: .c .o
.c.o:
	$(CC) $< $(CFLAGS) -c -o $@

install: stmr
	cp -f stmr $(PREFIX)/bin/stmr

uninstall:
	rm -f $(PREFIX)/bin/stmr

clean:
	rm -f stmr $(OBJ_CLI) $(OBJ_TEST)

.PHONY: clean install uninstall
