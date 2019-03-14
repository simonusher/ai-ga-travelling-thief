#include <iostream>
#include "../include/GeneticAlgorithm/Individual.h"
#include "../include/GeneticAlgorithm/TTPProblem.h"
#include "../include/GeneticAlgorithm/GeneticAlgorithm.h"
#include <chrono>
#include <ctime>

int main() {
    TTPProblem problem;
    std::string problemName("trivial_0");
    std::string filename(problemName + ".ttp");
    int iterations = 100;
    int popSize = 100;
    int tournamentSize = 2;
    double mutProb = 0.1;
    double crossProb = 0.7;
    problem.initialize(filename, MostProfitable);
//    std::cout << problem.selectedItemsWeight << "\n";
//    std::cout << problem.selectedItemsProfit << "\n";
//    std::vector<int> solution {2, 7, 42, 17, 3, 41, 9, 10, 8, 19, 45, 32, 49, 1, 22, 18, 31, 21, 30, 23, 20, 50, 29, 16, 46, 44, 34, 35, 36, 39, 40, 37, 38, 15, 43, 33, 4, 6, 5, 24, 48, 25, 12, 51, 11, 28, 26, 27, 13, 52, 14, 47};
//    Individual i(solution);
//    std::cout << problem.evaluate(&i);
    Logger logger(true, problemName + ".txt");
    GeneticAlgorithm ga(popSize, crossProb, mutProb, tournamentSize, &problem, &logger);
    ga.run(iterations);
    logger.close();
}