//
// Created by Szymon on 10/03/2019.
//

#ifndef GENETICALGORITHM_GENETICALGORITHM_H
#define GENETICALGORITHM_GENETICALGORITHM_H

#include <vector>
#include <random>
#include <algorithm>
#include "../problem/Individual.h"
#include "../problem/Problem.h"
#include "../util/Logger.h"
#include "../operators/Selector.h"
#include "../operators/Mutator.h"


class GeneticAlgorithm {
public:
    GeneticAlgorithm(int popSize, double crossProb, Problem *problem, Logger *logger,
            std::mt19937 *randomGenerator, Selector* selector, Mutator* mutator);
    ~GeneticAlgorithm();
    void run(int iters);

private:
    Individual* randomFromPopulation();
    std::vector<Individual*> pickTwoAtRandom();
    bool shouldCross();

    void initPopulation();

    void select();
    void crossover();
    void mutate();
    void evaluate();

    void clearPopulation();
    void runIteration();
    void selectBestAndCalculateMetrics();

    void printInfo();

    void printResults();

    std::vector<Individual*> population;
    int iterationsPassed;
    int popSize;
    Individual* bestOverall;
    double currentBestFitness;
    double currentWorstFitness;
    double currentAverageFitness;
    double crossProb;

    Selector* selector;
    Mutator* mutator;
    Logger* logger;
    Problem* problem;
    std::mt19937* randomGenerator;
    std::uniform_int_distribution<int> populationDistribution;
    std::bernoulli_distribution crossoverDistribution;

    void logData();
};


#endif //GENETICALGORITHM_GENETICALGORITHM_H
