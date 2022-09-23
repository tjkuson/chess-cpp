# Chess CLI

![CMake](https://github.com/tjkuson/chess-cpp/workflows/CMake/badge.svg)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/393c681a2ce34fc78d64acf745398cee)](https://www.codacy.com/gh/tjkuson/chess-cpp/dashboard?utm_source=github.com&utm_medium=referral&utm_content=tjkuson/chess-cpp&utm_campaign=Badge_Grade)

This is a cross-platform command-line chess game written in object-orientated modern C++ using only the Standard Library. It aims to demonstrate the implementation of advanced C++ code features. Users are free to study, modify, and redistribute the source code in compliance with the GPLv3 software licence.

Most recent release: Chess-CLI v1.0.2 (22 May 2021).

## Table of contents

-   [Setup](#setup)
-   [Game functionality](#game-functionality)
-   [Code features](#code-features)
-   [Project status](#project-status)

## Setup

### GCC and G++

To compile and execute using GCC and G++, run the following.

    $ cd ../src
    $ g++ main.cpp game.cpp bishop.cpp board.cpp king.cpp knight.cpp pawn.cpp piece.cpp position.cpp queen.cpp rook.cpp colour.cpp -o ../bin/main.out
    $ ./../bin/main.out

## Game functionality

-   Move validation
-   Check and checkmate
-   Castling

### To-do

-   En passant
-   Save and load games
-   AI opponent
-   Custom starting conditions

## Code features

-   Source code organization (headers, class files, namespaces)
-   Dynamic memory allocation (and garbage collection)
-   Smart pointers
-   Exception handling
-   Use of the Standard Library (for example, use of container classes)
-   Lambda expressions

### To-do

-   Move semantics
-   Templates
-   Substantial input/output interface, namely reading and writing to storage

## Project status

Project is in progress. Working on:

-   Move castling logic to King class from Game class
-   Move pawn-finding function to Board class from Game class

## Licence

This project is open-source and available under the [GNU GPL version 3](LICENSE) or later.
