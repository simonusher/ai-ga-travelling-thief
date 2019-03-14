//
// Created by Szymon on 10/03/2019.
//

#include "../include/GeneticAlgorithm/GeneticAlgorithm.h"
GeneticAlgorithm::GeneticAlgorithm(int popSize, double crossProb, double mutProb, Problem* problem, Logger &logger) :
    popSize(popSize), crossProb(crossProb), mutProb(mutProb), problem(problem), bestOverall(nullptr),
    iterationsPassed(0), populationDistribution(std::uniform_int_distribution<int>(0, popSize - 1)),
    logger(logger)
{
    initPopulation();
    randomGenerator = std::mt19937(randomDevice());
}

GeneticAlgorithm::~GeneticAlgorithm() {
    clearPopulation();
    if(bestOverall != nullptr){
        delete bestOverall;
    }
}

void GeneticAlgorithm::run(int iters) {
    evaluate();
    for (int i = 0; i < iters; i++){
        runIteration();
    }
}

void GeneticAlgorithm::runIteration() {
    select();
    crossover();
    mutate();
    evaluate();
    iterationsPassed++;
    logger << iterationsPassed << ";" << bestOverall->getFitness() << ";" << currentWorstFitness << ";" << currentAverageFitness << ";" << currentBestFitness << "\n";
}

double GeneticAlgorithm::getBestFitness() {
    if(bestOverall != nullptr){
        return problem->getWorstPossibleFitness();
    }
}

Individual *GeneticAlgorithm::getBestIndividual() {
    return bestOverall;
}

void GeneticAlgorithm::initPopulation() {
    clearPopulation();
    for(int i = 0; i < popSize; i++){
        population.push_back(problem->randomizedSolution());
    }
}

void GeneticAlgorithm::select() {
    std::vector<Individual*> parentPopulation;
    while(parentPopulation.size() != population.size()){
        std::vector<Individual*> randomIndividuals = pickTwoAtRandom();
        if(problem->compareSolutions(randomIndividuals[0], randomIndividuals[1])){
            parentPopulation.push_back(new Individual(*randomIndividuals[0]));
        } else {
            parentPopulation.push_back(new Individual(*randomIndividuals[1]));
        }
    }
    selectBestAndCalculateMetrics();
    clearPopulation();
    population = parentPopulation;
}

void GeneticAlgorithm::crossover() {
    std::vector<Individual*> newPopulation;
    Individual *firstOffspring;
    Individual *secondOffspring;
    while(newPopulation.size() != population.size()){
        std::vector<Individual*> parents = pickTwoAtRandom();
        if(shouldCross()){
            std::vector<Individual*> offspring = parents[0]->crossover(randomGenerator, *parents[1]);
            firstOffspring = offspring[0];
            secondOffspring = offspring[1];
        } else {
            firstOffspring = new Individual(*parents[0]);
            secondOffspring = new Individual(*parents[0]);
        }
        newPopulation.push_back(firstOffspring);
        newPopulation.push_back(secondOffspring);
    }
    clearPopulation();
    population = newPopulation;
}

void GeneticAlgorithm::mutate() {
    for(int i = 0; i < population.size(); i++){
        if(shouldMutate()){
            population[i]->mutate(randomGenerator);
        }
    }
}

void GeneticAlgorithm::evaluate() {
    for(Individual* individual : population){
        if(individual->isEvaluated()){
            problem->evaluate(individual);
        }
    }
}

void GeneticAlgorithm::clearPopulation() {
    for(int i = 0; i < population.size(); i++){
        delete population[i];
    }
    population.clear();
}

Individual *GeneticAlgorithm::randomFromPopulation() {
    return population[populationDistribution(randomGenerator)];
}

bool GeneticAlgorithm::shouldCross() {
    return crossoverDistribution(randomGenerator);
}

bool GeneticAlgorithm::shouldMutate() {
    return mutationDistribution(randomGenerator);
}

std::vector<Individual *> GeneticAlgorithm::pickTwoAtRandom() {
    Individual *p1 = randomFromPopulation();
    Individual *p2 = randomFromPopulation();
    while(p2 == p1){
        p2 = randomFromPopulation();
    }
    return std::vector<Individual *>{p1, p2};
}

void GeneticAlgorithm::selectBestAndCalculateMetrics() {
    Individual *best = population[0];
    double fitnessSum = best->getFitness();
    double worstFitness = best->getFitness();
    for(int i = 1; i < population.size(); i++){
        fitnessSum += population[i]->getFitness();
        if(problem->compareSolutions(population[i], best)){
            best = population[i];
        } else {
            worstFitness = population[i]->getFitness();
        }
    }
    currentAverageFitness =  fitnessSum / population.size();
    currentBestFitness = best->getFitness();
    currentWorstFitness = worstFitness;
    if(bestOverall == nullptr){
        bestOverall = new Individual(*best);
    }
    else if(problem->compareSolutions(best, bestOverall)){
        delete bestOverall;
        bestOverall = new Individual(*best);
    }

}