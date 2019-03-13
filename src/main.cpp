#include <iostream>
#include "../include/GeneticAlgorithm/Individual.h"
#include "../include/GeneticAlgorithm/TTPProblem.h"

int main() {
    TTPProblem problem;
    std::string filename("trivial_1.ttp");
    problem.initialize(filename, ProfitWeightRatio);
    Individual *i = problem.randomizedSolution();
    problem.evaluate(i);
    std::cout << i->getFitness();
}