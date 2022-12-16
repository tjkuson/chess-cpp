# Chess CLI

[![CMake Badge](https://img.shields.io/github/actions/workflow/status/tjkuson/chess-cpp/cmake.yml?branch=main)](https://github.com/tjkuson/chess-cpp/actions/workflows/cmake.yml)
[![Codacy Badge](https://img.shields.io/codacy/grade/393c681a2ce34fc78d64acf745398cee)](https://www.codacy.com/gh/tjkuson/chess-cpp/dashboard)

This is a cross-platform command-line chess game written in object-orientated modern C++
using only the Standard Library. It aims to demonstrate the implementation of advanced
C++ code features. Users are free to study, modify, and redistribute the source code as
per the software licence.

## Setup

### GCC and G++

To compile and execute using GCC and G++, run the following.

```commandline
cd ../src
g++ main.cpp game.cpp bishop.cpp board.cpp king.cpp knight.cpp pawn.cpp piece.cpp position.cpp queen.cpp rook.cpp colour.cpp -o ../bin/main.out
./../bin/main.out
```

## Game functionality

- Move validation
- Check and checkmate
- Castling

### To-do

- En passant
- Save and load games
- AI opponent
- Custom starting conditions

## Code features

- Source code organization (headers, class files, namespaces)
- Dynamic memory allocation (and garbage collection)
- Smart pointers
- Exception handling
- Use of the Standard Library (for example, use of container classes)
- Lambda expressions (anonymous functions)

_Note: files are referred to as columns (cols) in the code to avoid confusion with the
file system._

### To-do

- Move semantics
- Templates
- Substantial input/output interface, namely reading and writing to storage

## Licence

This project is distributed under the [GNU GPL version 3](LICENCE).
