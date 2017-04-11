cmake_minimum_required(VERSION 3.6)
project(PSUMAA)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Tarefa.cpp Tarefa.h Problema.cpp Problema.h Solucao.cpp Solucao.h Job.cpp Job.h)
add_executable(PSUMAA ${SOURCE_FILES})