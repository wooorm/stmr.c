# stmr([3](http://en.wikipedia.org/wiki/Man_page#Manual_sections)) [![Build Status](https://img.shields.io/travis/wooorm/stmr.c.svg?style=flat)](https://travis-ci.org/wooorm/stmr.c) [![Coverage Status](https://img.shields.io/coveralls/wooorm/stmr.c.svg?style=flat)](https://coveralls.io/r/wooorm/stmr.c?branch=master)

Martin Porter’s Stemming algorithm<sup>[1](http://tartarus.org/martin/PorterStemmer/)</sup> as a C library. There’s also a CLI: [stmr(1)](https://github.com/wooorm/stmr).

In fact, this is just a refactored version of the [initial ANCI C implementation](http://tartarus.org/martin/PorterStemmer/c.txt).

## Installation

CLib:
```sh
$ clib install wooorm/stmr.c
```

Or clone the repo.

## Usage

### int stem(char *pointer, int start, int end);

```c
#include <stdio.h>
#include <string.h>
#include "stmr.h"

int
main(int argc, char **argv) {
    char *word = argv[1];

    int end = stem(word, 0, strlen(word) - 1);

    word[end + 1] = 0;

    printf("%s", word);
}
```

## License

MIT © [Titus Wormer](http://wooorm.com)
