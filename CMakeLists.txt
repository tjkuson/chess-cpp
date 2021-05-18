cmake_minimum_required(VERSION 3.19)
project(chess_cli)

set(CMAKE_CXX_STANDARD 20)

add_executable(chesscli
        src/main.cpp
        src/main.h
        src/position.cpp
        src/position.h
        src/board.cpp
        src/board.h
        src/piece.cpp
        src/piece.h
        src/game.cpp
        src/game.h
        src/pawn.cpp
        src/pawn.h
        src/king.cpp
        src/king.h
        src/queen.cpp
        src/queen.h
        src/rook.cpp
        src/rook.h
        src/bishop.cpp
        src/bishop.h
        src/knight.cpp
        src/knight.h
        src/colour.cpp
        src/colour.h
        )