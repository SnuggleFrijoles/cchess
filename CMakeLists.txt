cmake_minimum_required(VERSION 3.6)
project(cchess)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/ai.c
        src/board.c
        src/cchess.c
        src/gameState.c
        src/linkedList.c
        src/piece.c
        src/player.c
        src/valid.c
        src/move.c)

include_directories(src/include)

add_executable(cchess ${SOURCE_FILES})