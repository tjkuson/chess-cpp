cmake_minimum_required(VERSION 3.19)
project(chess_cli)

set(CMAKE_CXX_STANDARD 20)

add_executable(chesscli
        src/main.cpp
        src/main.h
        src/piece.cpp src/piece.h src/board.cpp src/board.h src/colour.cpp src/colour.h src/pawn.cpp src/pawn.h)