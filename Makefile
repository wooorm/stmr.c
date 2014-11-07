PREFIX ?= /usr/local
SRC = stmr.c
OBJ = $(SRC:.c=.o)
CFLAGS = -D_GNU_SOURCE -std=c99

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
