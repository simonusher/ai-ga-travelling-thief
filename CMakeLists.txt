cmake_minimum_required(VERSION 3.10)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        GeneticAlgorithm src/main.cpp
        include/GeneticAlgorithm/problem/Individual.h
        include/GeneticAlgorithm/problem/Problem.h
        src/optimizers/GeneticAlgorithm.cpp
        include/GeneticAlgorithm/optimizers/GeneticAlgorithm.h
        src/problem/TTPProblem.cpp
        include/GeneticAlgorithm/problem/TTPProblem.h
        src/problem/Individual.cpp
        src/problem/KnapsackItem.cpp
        include/GeneticAlgorithm/problem/KnapsackItem.h
        src/problem/City.cpp
        include/GeneticAlgorithm/problem/City.h
        src/util/Logger.cpp
        include/GeneticAlgorithm/util/Logger.h
        src/optimizers/HillClimber.cpp
        include/GeneticAlgorithm/optimizers/HillClimber.h
        src/optimizers/RandomSearch.cpp
        include/GeneticAlgorithm/optimizers/RandomSearch.h
        include/GeneticAlgorithm/util/VectorHasher.h
        src/util/VectorHasher.cpp
        include/GeneticAlgorithm/operators/Selector.h
        src/operators/TournamentSelector.cpp
        include/GeneticAlgorithm/operators/TournamentSelector.h
        include/GeneticAlgorithm/operators/Mutator.h
        src/operators/RandomSwapMutator.cpp
        include/GeneticAlgorithm/operators/RandomSwapMutator.h
        src/operators/Mutator.cpp
        src/operators/AllGeneRandomSwapMutator.cpp
        include/GeneticAlgorithm/operators/AllGeneRandomSwapMutator.h src/operators/RouletteSelector.cpp include/GeneticAlgorithm/operators/RouletteSelector.h src/optimizers/Greedy.cpp include/GeneticAlgorithm/optimizers/Greedy.h)