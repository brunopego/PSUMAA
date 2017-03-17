cmake_minimum_required(VERSION 3.6)
project(PSUMAA)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Tarefa.cpp Tarefa.h)
add_executable(PSUMAA ${SOURCE_FILES})