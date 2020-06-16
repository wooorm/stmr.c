# stmr(3) [![Build Status][travis-badge]][travis] [![Coverage Status][coveralls-badge]][coveralls]

Martin Porter’s [Stemming algorithm][algo] as a C library.
There’s also a CLI: [stmr(1)][cli].

## Installation

[clib][]:

```bash
clib install wooorm/stmr.c
```

Or clone the repo.

## Usage

### `int stem(char *pointer, int start, int end)`

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

## Related

*   [`stemmer`][lib] — Same algorithm in JavaScript
*   [`stmr`][cli]
    — CLI in C

## License

[MIT][license] © [Titus Wormer][author]

<!-- Definitions -->

[travis-badge]: https://img.shields.io/travis/wooorm/stmr.c.svg

[travis]: https://travis-ci.org/wooorm/stmr.c

[coveralls-badge]: https://img.shields.io/coveralls/wooorm/stmr.c.svg

[coveralls]: https://coveralls.io/github/wooorm/stmr.c

[license]: license

[author]: http://wooorm.com

[algo]: http://tartarus.org/martin/PorterStemmer/

[cli]: https://github.com/wooorm/stmr

[lib]: https://github.com/words/stemmer

[clib]: https://github.com/clibs/clib
