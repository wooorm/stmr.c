# stmr(1) [![Build Status](https://img.shields.io/travis/wooorm/stmr.c.svg?style=flat)](https://travis-ci.org/wooorm/stmr.c)

Martin Porter’s Stemming algorithm<sup>[1](http://tartarus.org/martin/PorterStemmer/)</sup>.

In fact, this is just a refactored version of the [initial ANCI C implementation](http://tartarus.org/martin/PorterStemmer/c.txt), with a nice CLI.

## Installation

```
$ make install
```

CLib:
```
$ clib install wooorm/stmr.c
```

## Usage

```
  Usage: stmr [options] file

  Options:

    -h, --help           output usage information
    -v, --version        output version number

  Usage:

  # print stems
  $ stmr in.txt

  # write stems to out.txt
  $ stmr in.txt > out.txt

  # stdin and stdout
  $ echo "Internationalise" | ./stmr | cat
  # internationalis
```

## License

MIT © Titus Wormer
