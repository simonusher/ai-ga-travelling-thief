//
// Created by Szymon on 15.03.2019.
//

#include "../include/GeneticAlgorithm/RandomSearch.h"

void RandomSearch::search(int numberOfSolutions) {
    Individual *current = problem->randomizedSolution();
    problem->evaluate(current);
    delete bestOverall;
    bestOverall = current;
    seen.clear();
    seen.insert(current->getSolution());

    for(int i = 0; i < numberOfSolutions; i++){
        current = problem->randomizedSolution();
        while(seenSolution(current->getSolution())){
            delete current;
            current = problem->randomizedSolution();
        }
        problem->evaluate(current);
        seen.insert(current->getSolution());
        if(problem->compareSolutions(current, bestOverall)){
            delete bestOverall;
            bestOverall = current;
        }
        *logger << i << ";" << bestOverall->getFitness() << ";" << current->getFitness() << "\n";
    }
}

RandomSearch::~RandomSearch() {
    delete bestOverall;
}

RandomSearch::RandomSearch(Problem *problem, Logger *logger) : problem(problem), logger(logger), bestOverall(nullptr) {}

bool RandomSearch::seenSolution (const std::vector<int> &solution) {
    return seen.find(solution) != seen.end();
}
