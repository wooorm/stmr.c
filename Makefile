PREFIX ?= /usr/local
SRC = stmr.c
OBJ = $(SRC:.c=.o)
CFLAGS = -D_GNU_SOURCE -std=c99 -Wall -Wno-format-y2k -W -Wstrict-prototypes -Wmissing-prototypes \
    -Wpointer-arith -Wreturn-type -Wcast-qual -Wwrite-strings -Wswitch \
    -Wshadow -Wcast-align -Wbad-function-cast -Wchar-subscripts -Winline \
    -Wnested-externs -Wredundant-decls

stmr: $(OBJ)
	$(CC) $(OBJ) -o $@

.SUFFIXES: .c .o
.c.o:
	$(CC) $< $(CFLAGS) -c -o $@

install: stmr
	cp -f stmr $(PREFIX)/bin/stmr

uninstall:
	rm -f $(PREFIX)/bin/stmr

clean:
	rm -f stmr $(OBJ)

.PHONY: clean install uninstall
