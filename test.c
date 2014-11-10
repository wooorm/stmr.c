#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stmr.h"

static int hasError = 0;

static void
assertStem(const char *input, const char *output) {
    char *value;
    char *result;
    char *fixture;

    value = strdup(input);
    result = strdup(input);
    fixture = strdup(output);

    result[stem(result, 0, strlen(result) - 1) + 1] = 0;

    if (strcmp(fixture, result)) {
        hasError = 1;
        fprintf(stderr, "\033[31m");
        fprintf(stderr,
            "  (✖) For `%s`. Expected `%s`, got `%s`",
            value, fixture, result
        );
        fprintf(stderr, "\033[0m");
        fprintf(stderr, "\n");
    }

    free(value);
    free(fixture);
    free(result);
}

int
main() {
    FILE *input;
    FILE *output;

    char *lineIn;
    char *lineOut;
    size_t lengthIn;
    size_t lengthOut;

    lineIn = NULL;
    lineOut = NULL;
    lengthIn = 0;
    lengthOut = 0;

    input = fopen("fixture/input.txt", "r");
    output = fopen("fixture/output.txt", "r");

    while (
        getline(&lineIn, &lengthIn, input) != -1 &&
        getline(&lineOut, &lengthOut, output) != -1
    ) {

        lineIn[strlen(lineIn) - 1] = 0;
        lineOut[strlen(lineOut) - 1] = 0;

        assertStem(lineIn, lineOut);
    }

    /**
     * These two fixture are treated in `stmr.h`, but
     * not covered by the fixtures provided Martin
     * Porter.
     */

    assertStem("nationalization", "nation");
    assertStem("nationalism", "nation");

    if (hasError == 1) {
        exit(EXIT_FAILURE);
    }
}
