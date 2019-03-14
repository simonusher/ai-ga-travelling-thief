#include <iostream>
#include "../include/GeneticAlgorithm/Individual.h"
#include "../include/GeneticAlgorithm/TTPProblem.h"
#include "../include/GeneticAlgorithm/GeneticAlgorithm.h"

int main() {
    TTPProblem problem;
    std::string filename("hard_1.ttp");
    problem.initialize(filename, MostProfitable);
//    Individual *i = problem.randomizedSolution();
//    problem.evaluate(i);
//    std::cout << i->getFitness();
    Logger logger(true, "ble.txt");
    Logger &logger1 = logger;
    GeneticAlgorithm ga(100, 0.7, 0.1, &problem, logger1);
    ga.run(100);
    logger.close();
}