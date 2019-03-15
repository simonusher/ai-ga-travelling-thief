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
#include "Logger.h"

class GeneticAlgorithm {
public:
    GeneticAlgorithm(int popSize, double crossProb, double mutProb, int tournamentSize, Problem *problem, Logger *logger);
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

    bool shouldCross();
    bool shouldMutate();
    Individual* randomFromPopulation();

    Individual* performTournament();
    Individual* performTournament(std::vector<Individual*>& tournees);
    std::vector<Individual*> pickNAtRandom(int n);
    std::vector<Individual*> pickTwoAtRandom();
    void clearPopulation();
    void runIteration();
    void selectBestAndCalculateMetrics();

    Logger* logger;

    std::vector<int> tournamentIndices;
    std::vector<Individual*> population;
    int iterationsPassed;
    int popSize;
    Individual* bestOverall;
    double currentBestFitness;
    double currentWorstFitness;
    double currentAverageFitness;
    int tournamentSize;
    double crossProb;
    double mutProb;
    Problem* problem;
    std::random_device randomDevice;
    std::mt19937 randomGenerator;
    std::uniform_int_distribution<int> populationDistribution;
    std::bernoulli_distribution crossoverDistribution;
    std::bernoulli_distribution mutationDistribution;

    void printInfo();

    void printResults();
};


#endif //GENETICALGORITHM_GENETICALGORITHM_H
