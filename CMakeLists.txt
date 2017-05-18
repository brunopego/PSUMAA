cmake_minimum_required(VERSION 3.7)
project(PSUMAA)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        HeuristicaConstrutiva.cpp
        HeuristicaConstrutiva.h
        Job.cpp
        Job.h
        main.cpp
        Problema.cpp
        Problema.h
        Solucao.cpp
        Solucao.h
        Tarefa.cpp
        Tarefa.h)

add_executable(PSUMAA ${SOURCE_FILES})