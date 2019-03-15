#include <iostream>
#include "../include/GeneticAlgorithm/Individual.h"
#include "../include/GeneticAlgorithm/TTPProblem.h"
#include "../include/GeneticAlgorithm/GeneticAlgorithm.h"
//#include "../include/GeneticAlgorithm/RandomSearch.h"
#include "../include/GeneticAlgorithm/HillClimber.h"
#include <chrono>
#include <ctime>

int main() {
    TTPProblem problem;
    std::string problemName("medium_0");
    std::string filename(problemName + ".ttp");
    int iterations = 1000;
    int popSize = 100;
    int tournamentSize = 5;
    double mutProb = 0.02;
    double crossProb = 0.7;
    problem.initialize(filename, ProfitWeightRatio);
    Logger logger(true, problemName + ".txt");
//    GeneticAlgorithm ga(popSize, crossProb, mutProb, tournamentSize, &problem, &logger);
//    ga.run(iterations);
//    RandomSearch randomSearch(&problem, &logger);
//    randomSearch.search(1000000);
    HillClimber hillClimber(&problem, &logger);
    hillClimber.hillClimb(100);
    std::cout << problem.getFitnessFunctionEvaluations();
    logger.close();
}