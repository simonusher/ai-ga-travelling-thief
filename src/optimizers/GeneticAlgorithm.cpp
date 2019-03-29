//
// Created by Szymon on 10/03/2019.
//

#include "../../include/GeneticAlgorithm/optimizers/GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int popSize, double crossProb, Problem* problem, Logger *logger,
        std::mt19937 *randomGenerator, Selector* selector, Mutator* mutator,
        int purgeThreshold, int purgeNumber) :
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
    mutator(mutator),
    purgeThreshold(purgeThreshold),
    purgedNumber(purgeNumber),
    itersSinceImprovement(0),
    bestImproved(false)
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
    purgeIfNecessary();
    logData();
    select();
    crossover();
    mutate();
    fixup();
    evaluate();
    iterationsPassed++;
}

void GeneticAlgorithm::initPopulation() {
    clearPopulation();
    for(int i = 0; i < popSize; i++){
        population.push_back(problem->randomizedSolution());
    }
    fixup();
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
        bestImproved = true;
        itersSinceImprovement = 0;
    }
    else if(problem->compareSolutions(best, bestOverall)){
        delete bestOverall;
        bestOverall = new Individual(*best);
        bestImproved = true;
        itersSinceImprovement = 0;
    } else {
        bestImproved = false;
        itersSinceImprovement ++;
    }
}

void GeneticAlgorithm::printInfo() {
    *logger << "Iterations;Overall best;Worst;Average;Best;FFE\n";
}

void GeneticAlgorithm::printResults() {
    *logger << "Best tspSolution:\n";
    *logger << "\tTSP: [";
    for(int i = 0; i < bestOverall->getTspSolution().size(); i++){
        *logger << bestOverall->getTspSolution()[i];
        if(i != bestOverall->getTspSolution().size() - 1){
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

void GeneticAlgorithm::fixup() {
    for(int i = 0; i < population.size(); i++){
        problem->fixIfIncorrect(population[i]);
    }
}

void GeneticAlgorithm::purge() {
//    std::sort(population.begin(), population.end(), [](Individual *i1, Individual *i2) { return i1->getFitness() > i2->getFitness(); });
    for(int j = population.size(), i = purgedNumber; i > 0; i--, j--){
        delete population[i];
        population[i] = problem->randomizedSolution();
        problem->evaluate(population[i]);
    }
    itersSinceImprovement = 0;
    bestImproved = false;
    fixup();
}

void GeneticAlgorithm::purgeIfNecessary() {
    if(itersSinceImprovement > purgeThreshold){
        std::cout << "PURGING\n";
        purge();
    }
}
