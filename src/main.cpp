#include <iostream>
#include "../include/GeneticAlgorithm/Individual.h"
#include "../include/GeneticAlgorithm/TTPProblem.h"
#include "../include/GeneticAlgorithm/GeneticAlgorithm.h"
//#include "../include/GeneticAlgorithm/RandomSearch.h"
#include "../include/GeneticAlgorithm/HillClimber.h"
#include "../include/GeneticAlgorithm/TournamentSelector.h"
#include "../include/GeneticAlgorithm/AllGeneRandomSwapMutator.h"
#include "../include/GeneticAlgorithm/RandomSwapMutator.h"

int main() {
    TTPProblem problem;
    std::random_device randomDevice;
    std::mt19937 randomGenerator(randomDevice());
    std::string problemName("medium_0");
    std::string filename(problemName + ".ttp");
    int iterations = 250;
    int popSize = 100;
    int tournamentSize = 15;
    double crossProb = 0.8;


    problem.initialize(filename, ProfitWeightRatio);
    Logger logger(true, problemName + ".txt");
    TournamentSelector selector(&problem, tournamentSize, popSize, &randomGenerator);

    double mutProb = 0.03;
    AllGeneRandomSwapMutator mutator(mutProb, &randomGenerator);
//    RandomSwapMutator mutator(mutProb, &randomGenerator);


    GeneticAlgorithm ga(popSize, crossProb, &problem, &logger, &randomGenerator, &selector, &mutator);
    ga.run(iterations);
//    RandomSearch randomSearch(&problem, &logger);
//    randomSearch.search(1000000);
//    HillClimber hillClimber(&problem, &logger);
//    hillClimber.hillClimb(100);
    std::cout << problem.getFitnessFunctionEvaluations();
    logger.close();
}