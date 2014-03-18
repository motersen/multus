[![Build Status](https://travis-ci.org/motersen/wordcount.png?branch=master)](https://travis-ci.org/motersen/wordcount)

wordcount
=========

Copyright (c) 2013, Moritz Petersen: Simplified BSD License  
See LICENSE File for full license text.

__wordcount__ is a tool to count the occurrences of words in texts.

## Build

### Requirements:

- Build Tools
  + GNU Make
  + pkg-config
- Libraries
  + glib-2.0

- Run ```make``` twice to compile.
- The executable should now be at bin/wordcount.
- Run ```make clean``` to reset the project to source state.

## Use

```
wordcount [OPTIONS] [INPUT]
OPTIONS:
  -h --help
    Display this Help
  -v --verbose
    Print status information

If INPUT is passed, it will be tried to read from a file with the name.
Otherwise, or if INPUT is '-', input will be read from stdin.
```
