//
// Created by Szymon on 10/03/2019.
//

#include "../../include/GeneticAlgorithm/optimizers/GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int popSize, double crossProb, Problem* problem, Logger *logger,
        std::mt19937 *randomGenerator, Selector* selector, Mutator* mutator) :
    popSize(popSize),
    crossProb(crossProb),
    problem(problem),
    bestOverall(nullptr),
    iterationsPassed(0),
    populationDistribution(0, popSize - 1),
    crossoverDistribution(crossProb),
    logger(logger),
    randomGenerator(randomGenerator),
    selector(selector),
    mutator(mutator)
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
//    printResults();
}

void GeneticAlgorithm::runIteration() {
    selectBestAndCalculateMetrics();
    logData();
    select();
    crossover();
    mutate();
    evaluate();
    iterationsPassed++;
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
    mutator->mutate(population);
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
    *logger << "Iterations;Overall best;Worst;Average;Best;FFE\n";
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

void GeneticAlgorithm::logData() {
    *logger << iterationsPassed
    << ";" << (int)bestOverall->getFitness() << ";"
    << (int)currentWorstFitness << ";" << (int)currentAverageFitness << ";"
    << (int)currentBestFitness << ";" << problem->getFitnessFunctionEvaluations() << "\n";
}
