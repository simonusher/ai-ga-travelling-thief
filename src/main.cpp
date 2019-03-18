#include <iostream>
#include "../include/GeneticAlgorithm/problem/Individual.h"
#include "../include/GeneticAlgorithm/problem/TTPProblem.h"
#include "../include/GeneticAlgorithm/optimizers/GeneticAlgorithm.h"
//#include "../include/GeneticAlgorithm/RandomSearch.h"
#include "../include/GeneticAlgorithm/optimizers/HillClimber.h"
#include "../include/GeneticAlgorithm/operators/TournamentSelector.h"
#include "../include/GeneticAlgorithm/operators/AllGeneRandomSwapMutator.h"
#include "../include/GeneticAlgorithm/operators/RandomSwapMutator.h"

#include <ctime>
using namespace std;

int main() {
    TTPProblem problem;
    std::random_device randomDevice;
    std::mt19937 randomGenerator(randomDevice());
    std::string problemName("medium_0");
    std::string filename(problemName + ".ttp");
    int iterations = 100;
    int popSize = 100;
    int tournamentSize = 15;
    double crossProb = 0.7;


    problem.initialize(filename, ProfitWeightRatio);
    Logger logger(true, problemName + ".txt");
    TournamentSelector selector(&problem, tournamentSize, popSize, &randomGenerator);

    double mutProb = 0.01;
//    double mutProb = 0.3;
    AllGeneRandomSwapMutator mutator(mutProb, &randomGenerator);
//    RandomSwapMutator mutator(mutProb, &randomGenerator);

    clock_t begin = clock();

    GeneticAlgorithm ga(popSize, crossProb, &problem, &logger, &randomGenerator, &selector, &mutator);
    ga.run(iterations);



//    RandomSearch randomSearch(&problem, &logger);
//    randomSearch.search(1000000);
//    HillClimber hillClimber(&problem, &logger);
//    hillClimber.hillClimb(100);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "elapsed secs: " << elapsed_secs << std::endl;
    std::cout << problem.getFitnessFunctionEvaluations();
    logger.close();
}