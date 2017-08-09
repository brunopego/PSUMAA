cmake_minimum_required(VERSION 3.7)
project(PSUMAA)

set(CMAKE_CXX_STANDARD 11)
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fopenmp" )

set(SOURCE_FILES
        Job.cpp
        Job.h
        main.cpp
        Problema.cpp
        Problema.h
        Solucao.cpp
        Solucao.h
        Tarefa.cpp
        Tarefa.h Populacao.cpp Populacao.h)

add_executable(PSUMAA ${SOURCE_FILES})