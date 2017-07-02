#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stmr.h"

static int assertionCount = 0;

static int errorCount = 0;

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
    errorCount++;

    fprintf(stderr, "\033[31m");
    fprintf(stderr, "  (✖) For `%s`. Expected `%s`, got `%s`", value, fixture, result);
    fprintf(stderr, "\033[0m");
    fprintf(stderr, "\n");
  } else {
    printf("\033[32m.\033[0m");
  }

  assertionCount++;

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

  printf("\n");

  if (errorCount != 0) {
    printf("\033[31m");
    printf("(✖) Failed on %d of %d assertions", errorCount, assertionCount);
    printf("\033[0m");
    printf("\n");

    exit(EXIT_FAILURE);
  }

  printf("\033[32m");
  printf("(✓) Passed %d assertions without errors", assertionCount);
  printf("\033[0m");
  printf("\n");

  return 0;
}
