#include <iostream>
#include "../include/GeneticAlgorithm/problem/Individual.h"
#include "../include/GeneticAlgorithm/problem/TTPProblem.h"
#include "../include/GeneticAlgorithm/optimizers/GeneticAlgorithm.h"
#include "../include/GeneticAlgorithm/optimizers/RandomSearch.h"
#include "../include/GeneticAlgorithm/optimizers/HillClimber.h"
#include "../include/GeneticAlgorithm/operators/TournamentSelector.h"
#include "../include/GeneticAlgorithm/operators/AllGeneRandomSwapMutator.h"
#include "../include/GeneticAlgorithm/operators/RandomSwapMutator.h"
#include "../include/GeneticAlgorithm/operators/RouletteSelector.h"
#include "../include/GeneticAlgorithm/optimizers/GreedyTTP.h"

#include <ctime>
using namespace std;

int main() {

    TTPProblem problem;
    std::random_device randomDevice;
    std::mt19937 randomGenerator(randomDevice());
    std::string problemName("easy_1");
    std::string filename(problemName + ".ttp");
    int iterations = 100;
    int popSize = 1000;
    double crossProb = 0.9;


    problem.initialize(filename, ProfitWeightRatio);
    Logger logger(true, "results/" + problemName + ".txt");

    int tournamentSize = 50;
    TournamentSelector selector(&problem, tournamentSize, popSize, &randomGenerator);
//    RouletteSelector selector(&problem, &randomGenerator);

    double mutProb = 0.007;
    AllGeneRandomSwapMutator mutator(mutProb, &randomGenerator);
//    double mutProb = 0.3;
//    RandomSwapMutator mutator(mutProb, &randomGenerator);

    clock_t begin = clock();

    GeneticAlgorithm ga(popSize, crossProb, &problem, &logger, &randomGenerator, &selector, &mutator);
    ga.run(iterations);
//    GreedyTTP greedyTTP(&problem, &logger);
//    greedyTTP.solve();


//    RandomSearch randomSearch(&problem, &logger);
//    randomSearch.search(1000000);
//    HillClimber hillClimber(&problem, &logger);
//    hillClimber.hillClimb(1000);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "elapsed secs: " << elapsed_secs << std::endl;
    std::cout << problem.getFitnessFunctionEvaluations();
    logger.close();
}