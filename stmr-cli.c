#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

/**
 * Utility to detect if `character` is a letter.
 */

#include "stmr.h"

/**
 * Utility to detect if `character` is a letter.
 */

#define IS_LETTER(character) (isupper(character) || islower(character))

/**
 * Static string pointer. Passed into `b` above.
 */

static char *value;

/**
 * Size in which `value` is increased.
 */

#define INC 50

/**
 * Maximum offset in `value`
 */

static int indexMax = INC;

/**
 * Increase memory.
 */

static void
increaseValue() {
    char *newValue;
    int index;

    indexMax += INC;

    newValue = (char *) malloc(indexMax + 1);

    index = -1;

    while (++index < indexMax) {
        newValue[index] = value[index];
    }

    free(value);

    value = newValue;
}

/**
 * Tokenise and stem a file
 *
 * @param f
 *
 */

static void
stemFile(FILE *file) {
    int character;
    int index;

    while (TRUE) {
        character = getc(file);

        if (character == EOF) {
            return;
        }

        if (IS_LETTER(character)) {
            index = 0;

            while (TRUE) {
                if (index == indexMax) {
                    increaseValue();
                }

                character = tolower(character);

                value[index] = character;

                index++;

                character = getc(file);

                if (!IS_LETTER(character)) {
                    ungetc(character, file);

                    break;
                }
            }

            value[stem(value, 0, index - 1) + 1] = 0;

            /**
             * The previous line calls the stemmer and
             * uses its result to zero-terminate the
             * string in `value`.
             */

            printf("%s", value);
        } else {
            putchar(character);
        }
    }
}

/**
 *  Evaluate a word.
 */

static void
evaluate(const char *input) {
    value = strdup(input);

    value[stem(value, 0, strlen(value) - 1) + 1] = 0;

    printf("%s\n", value);
}

int
main(int argc, char **argv) {
    char *arg;
    FILE *input;
    int index;

    arg = argv[1];

    if (argc == 2) {
        if (!strcmp(arg, "-v") || !strcmp(arg, "--version")) {
            printf("%s", "0.0.1\n");

            return EXIT_SUCCESS;
        }

        if (!strcmp(arg, "-h") || !strcmp(arg, "--help")) {
            printf("%s", "\n");
            printf("%s", "  Usage: stmr [options] file\n");
            printf("%s", "\n");
            printf("%s", "  Options:\n");
            printf("%s", "\n");
            printf("%s", "    -h, --help           output usage information\n");
            printf("%s", "    -v, --version        output version number\n");
            printf("%s", "    -e, --eval string    output stemmed word\n");
            printf("%s", "\n");
            printf("%s", "  Usage:\n");
            printf("%s", "\n");
            printf("%s", "  # stem a word\n");
            printf("%s", "  $ stmr -e nationalism\n");
            printf("%s", "  # nation\n");
            printf("%s", "\n");
            printf("%s", "  # print stems\n");
            printf("%s", "  $ stmr in.txt\n");
            printf("%s", "\n");
            printf("%s", "  # write stems to out.txt\n");
            printf("%s", "  $ stmr in.txt > out.txt\n");
            printf("%s", "\n");
            printf("%s", "  # stdin and stdout\n");
            printf("%s", "  $ echo \"Internationalise\" | stmr\n");
            printf("%s", "  # internationalis\n");
            printf("%s", "\n");

            return EXIT_SUCCESS;
        }
    }

    if (
        argc > 1 &&
        (!strcmp(arg, "-e") || !strcmp(arg, "--eval"))
    ) {
        arg = argv[2];

        if (arg == NULL) {
            fprintf(stderr, "stmr: -e requires an argument\n");

            exit(EXIT_FAILURE);
        }

        evaluate(arg);

        return EXIT_SUCCESS;
    }

    value = (char *) malloc(indexMax + 1);

    if (argc < 2) {
        stemFile(stdin);
    } else {
        index = 0;

        while (++index < argc) {
            arg = argv[index];

            input = fopen(arg, "r");

            if (NULL == input) {
                fprintf(
                    stderr, "Unable to open '%s': %s\n", arg, strerror(errno)
                );

                exit(EXIT_FAILURE);
            }

            stemFile(input);
        }
    }

    free(value);

    return EXIT_SUCCESS;
}
