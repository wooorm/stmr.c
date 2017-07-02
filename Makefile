TEST = test.c stmr.c
OBJ_TEST = $(TEST:.c=.o)

CFLAGS = -D_GNU_SOURCE -std=c99

LFLAGS = -Wall -Wno-format-y2k -W -Wstrict-prototypes -Wmissing-prototypes \
	-Wpointer-arith -Wreturn-type -Wcast-qual -Wwrite-strings -Wswitch \
	-Wshadow -Wcast-align -Wbad-function-cast -Wchar-subscripts -Winline \
	-Wnested-externs -Wredundant-decls

COVFLAGS = -Wall -fprofile-arcs -ftest-coverage

test: $(OBJ_TEST)
	$(CC) $(OBJ_TEST) -o $@

coverage: $(OBJ_TEST)
	gcc $(COVFLAGS) $(TEST) -o $@

.SUFFIXES: .c .o
.c.o:
	$(CC) $< $(CFLAGS) $(LFLAGS) -c -o $@

run-coverage: coverage
	./coverage && gcov stmr

run-test: test
	./test

clean:
	rm -f coverage test $(OBJ_TEST) *.gc{ov,da,no}

.PHONY: clean run-coverage run-test
