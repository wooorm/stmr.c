PREFIX ?= /usr/local

SRC = stmr.c
CLI = stmr-cli.c $(SRC)
TEST = test.c $(SRC)

OBJ_SRC = $(SRC:.c=.o)
OBJ_CLI = $(CLI:.c=.o)
OBJ_TEST = $(TEST:.c=.o)

CFLAGS = -D_GNU_SOURCE -std=c99

LFLAGS = -Wall -Wno-format-y2k -W -Wstrict-prototypes -Wmissing-prototypes \
    -Wpointer-arith -Wreturn-type -Wcast-qual -Wwrite-strings -Wswitch \
    -Wshadow -Wcast-align -Wbad-function-cast -Wchar-subscripts -Winline \
    -Wnested-externs -Wredundant-decls

COVFLAGS = -Wall -fprofile-arcs -ftest-coverage

stmr: $(OBJ_CLI)
	$(CC) $(OBJ_CLI) -o $@

test: $(OBJ_TEST)
	$(CC) $(OBJ_TEST) -o $@

coverage: $(OBJ_TEST)
	gcc $(COVFLAGS) $(TEST) -o $@ && \
	./$@ && \
	gcov stmr && \
	rm -rf *.{gcda,gcno}

.SUFFIXES: .c .o
.c.o:
	$(CC) $< $(CFLAGS) $(LFLAGS) -c -o $@

install: stmr
	cp -f stmr $(PREFIX)/bin/stmr

uninstall:
	rm -f $(PREFIX)/bin/stmr

run-test: stmr test
	./test && ./test-cli.sh

clean:
	rm -f stmr coverage test $(OBJ_CLI) $(OBJ_TEST) *.gcov

.PHONY: clean install uninstall
