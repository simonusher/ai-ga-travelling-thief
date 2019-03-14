#include <iostream>
#include "../include/GeneticAlgorithm/Individual.h"
#include "../include/GeneticAlgorithm/TTPProblem.h"
#include "../include/GeneticAlgorithm/GeneticAlgorithm.h"
#include <chrono>
#include <ctime>

int main() {
    TTPProblem problem;
    std::string problemName("easy_0");
    std::string filename(problemName + ".ttp");
    int iterations = 100;
    int popSize = 100;
    double mutProb = 0.1;
    double crossProb = 0.7;
    problem.initialize(filename, MostProfitable);
    Logger logger(true, problemName + ".txt");
    GeneticAlgorithm ga(popSize, crossProb, mutProb, &problem, &logger);
    ga.run(iterations);
    logger.close();
}