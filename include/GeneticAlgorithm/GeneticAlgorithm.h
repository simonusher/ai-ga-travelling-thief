//
// Created by Szymon on 10/03/2019.
//

#ifndef GENETICALGORITHM_GENETICALGORITHM_H
#define GENETICALGORITHM_GENETICALGORITHM_H

#include <vector>
#include <random>
#include <algorithm>
#include "Individual.h"
#include "Problem.h"

template <typename T>
class GeneticAlgorithm {
public:
    GeneticAlgorithm<T>(int popSize, double crossProb, double mutProb, std::string problemFilename);
    ~GeneticAlgorithm();
    void run(int iters);
    double getBestFitness();
    Individual* getBestIndividual();
private:
    void initPopulation();
    void select();
    void crossover();
    void mutate();
    void evaluate();
    void sortPopulationDesc();

    bool shouldCross();
    bool shouldMutate();
    Individual *randomFromPopulation();
    std::vector<Individual*> pickTwoAtRandom();
    void clearPopulation();
    void runIteration();
    std::vector<Individual*> population;
    int iterationsPassed;
    int popSize;
    Individual* bestIndividual;
    double crossProb;
    double mutProb;
    Problem* problem;
    std::mt19937 randomGenerator;
    std::uniform_int_distribution<int> populationDistribution;
    std::bernoulli_distribution crossoverDistribution;
    std::bernoulli_distribution mutationDistribution;
};


#endif //GENETICALGORITHM_GENETICALGORITHM_H
