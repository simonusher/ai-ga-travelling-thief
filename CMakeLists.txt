cmake_minimum_required(VERSION 3.10)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(GeneticAlgorithm src/main.cpp include/GeneticAlgorithm/Individual.h include/GeneticAlgorithm/Problem.h src/GeneticAlgorithm.cpp include/GeneticAlgorithm/GeneticAlgorithm.h src/TTPProblem.cpp include/GeneticAlgorithm/TTPProblem.h src/Individual.cpp src/KnapsackItem.cpp include/GeneticAlgorithm/KnapsackItem.h src/City.cpp include/GeneticAlgorithm/City.h)