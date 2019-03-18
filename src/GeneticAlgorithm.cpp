//
// Created by Szymon on 10/03/2019.
//

#include "../include/GeneticAlgorithm/GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int popSize, double crossProb, double mutProb,
        Problem* problem, Logger *logger, std::mt19937 *randomGenerator, Selector* selector) :
    popSize(popSize),
    crossProb(crossProb),
    mutProb(mutProb), problem(problem),
    bestOverall(nullptr),
    iterationsPassed(0),
    populationDistribution(std::uniform_int_distribution<int>(0, popSize - 1)),
    crossoverDistribution(std::bernoulli_distribution(crossProb)),
    mutationDistribution(std::bernoulli_distribution(mutProb)),
    logger(logger),
    randomGenerator(randomGenerator),
    selector(selector)
{
    initPopulation();
}

GeneticAlgorithm::~GeneticAlgorithm() {
    clearPopulation();
    if(bestOverall != nullptr){
        delete bestOverall;
    }
}

void GeneticAlgorithm::run(int iters) {
    evaluate();
    printInfo();
    for (int i = 0; i < iters; i++){
        runIteration();
    }
    printResults();
}

void GeneticAlgorithm::runIteration() {
    selectBestAndCalculateMetrics();
    *logger << iterationsPassed << ";" << (int)bestOverall->getFitness() << ";" << (int)currentWorstFitness << ";" << (int)currentAverageFitness << ";" << (int)currentBestFitness << "\n";
    select();
    crossover();
    mutate();
    evaluate();
    iterationsPassed++;
}

double GeneticAlgorithm::getBestFitness() {
    if(bestOverall != nullptr){
        return problem->getWorstPossibleFitness();
    } else {
        return bestOverall->getFitness();
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
    std::vector<Individual*> parentPopulation = selector->selectAllParents(population);
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
            std::vector<Individual*> offspring = parents[0]->crossover(*randomGenerator, *parents[1]);
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
//        if(shouldMutate()){
//            population[i]->mutate(randomGenerator);
//        }
        for(int j = 0; j < population[i]->getSolution().size(); j++){
            if(shouldMutate()){
                population[i]->swapWithRandom(j, *randomGenerator);
            }
        }
    }
}

void GeneticAlgorithm::evaluate() {
    for(Individual* individual : population){
        problem->evaluate(individual);
    }
}

void GeneticAlgorithm::clearPopulation() {
    for(int i = 0; i < population.size(); i++){
        delete population[i];
    }
    population.clear();
}

Individual *GeneticAlgorithm::randomFromPopulation() {
    return population[populationDistribution(*randomGenerator)];
}

bool GeneticAlgorithm::shouldCross() {
    return crossoverDistribution(*randomGenerator);
}

bool GeneticAlgorithm::shouldMutate() {
    return mutationDistribution(*randomGenerator);
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
    Individual *worst = population[0];
    double fitnessSum = best->getFitness();
    for(int i = 1; i < population.size(); i++){
        Individual *current = population[i];
        fitnessSum += current->getFitness();
        if(problem->compareSolutions(current, best)){
            best = current;
        }
        if(problem->compareSolutions(worst, current)){
            worst = current;
        }
    }
    currentAverageFitness =  fitnessSum / population.size();
    currentBestFitness = best->getFitness();
    currentWorstFitness = worst->getFitness();
    if(bestOverall == nullptr){
        bestOverall = new Individual(*best);
    }
    else if(problem->compareSolutions(best, bestOverall)){
        delete bestOverall;
        bestOverall = new Individual(*best);
    }
}

void GeneticAlgorithm::printInfo() {
    *logger << "Iterations;Overall best;Worst;Average;Best\n";
}

void GeneticAlgorithm::printResults() {
    *logger << "Best solution:\n";
    *logger << "\tTSP: [";
    for(int i = 0; i < bestOverall->getSolution().size(); i++){
        *logger << bestOverall->getSolution()[i];
        if(i != bestOverall->getSolution().size() - 1){
            *logger << ", ";
        }
    }
    *logger << "]\n";
    *logger << "KSP: ";
}