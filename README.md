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

- Run ```make``` to compile.
- The executable should now be at bin/wordcount.
- Run ```make clean``` to remove all object files.

## Use

```
wordcount [options] [File]
required:
    -f --file <filename>
        Specifies the path to the File to be read
optional:
    -h --help
        Display this Help
    -v --verbose
        Print information about operations
```

## ToDo

- Add support for Pipes & Here-Documents
- Add case insensitivity
- Add Documentation

