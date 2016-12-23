cmake_minimum_required(VERSION 3.3)
project(cchess)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

add_custom_target(cchess COMMAND make -C ${cchess_SOURCE_DIR}
        CLION_EXE_DIR=${PROJECT_BINARY_DIR})

