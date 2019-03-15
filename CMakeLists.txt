cmake_minimum_required(VERSION 3.10)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        GeneticAlgorithm src/main.cpp
        include/GeneticAlgorithm/Individual.h
        include/GeneticAlgorithm/Problem.h
        src/GeneticAlgorithm.cpp
        include/GeneticAlgorithm/GeneticAlgorithm.h
        src/TTPProblem.cpp
        include/GeneticAlgorithm/TTPProblem.h
        src/Individual.cpp
        src/KnapsackItem.cpp
        include/GeneticAlgorithm/KnapsackItem.h
        src/City.cpp
        include/GeneticAlgorithm/City.h
        src/Logger.cpp
        include/GeneticAlgorithm/Logger.h
        src/HillClimber.cpp
        include/GeneticAlgorithm/HillClimber.h
        src/RandomSearch.cpp
        include/GeneticAlgorithm/RandomSearch.h
        include/GeneticAlgorithm/VectorHasher.h
        src/VectorHasher.cpp)