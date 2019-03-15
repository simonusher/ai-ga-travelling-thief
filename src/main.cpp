#include <iostream>
#include "../include/GeneticAlgorithm/Individual.h"
#include "../include/GeneticAlgorithm/TTPProblem.h"
#include "../include/GeneticAlgorithm/GeneticAlgorithm.h"
#include <chrono>
#include <ctime>

int main() {
    TTPProblem problem;
    std::string problemName("medium_0");
    std::string filename(problemName + ".ttp");
    int iterations = 100;
    int popSize = 100;
    int tournamentSize = 2;
    double mutProb = 0.01;
    double crossProb = 0.7;
    problem.initialize(filename, ProfitWeightRatio);
    Logger logger(true, problemName + ".txt");
    GeneticAlgorithm ga(popSize, crossProb, mutProb, tournamentSize, &problem, &logger);
    ga.run(iterations);
    logger.close();
}