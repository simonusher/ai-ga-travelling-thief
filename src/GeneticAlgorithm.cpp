//
// Created by Szymon on 10/03/2019.
//

#include "../include/GeneticAlgorithm/GeneticAlgorithm.h"
template<typename T>
GeneticAlgorithm<T>::GeneticAlgorithm(int popSize, double crossProb, double mutProb, std::string problemFilename) :
    popSize(popSize), crossProb(crossProb), mutProb(mutProb)
{
    problem = new T();
    problem->load(problemFilename);
    bestIndividual = nullptr;
    iterationsPassed = 0;
    populationDistribution = std::uniform_int_distribution<int>(0, popSize - 1);
    initPopulation();
}

template<typename T>
GeneticAlgorithm<T>::~GeneticAlgorithm() {
    clearPopulation();
    delete problem;
    if(bestIndividual != nullptr){
        delete bestIndividual;
    }
}

template<typename T>
void GeneticAlgorithm<T>::run(int iters) {
    evaluate();
    for (int i = 0; i < iters; i++){
        runIteration();
    }
}

template<typename T>
void GeneticAlgorithm<T>::runIteration() {
    select();
    crossover();
    mutate();
    evaluate();
    iterationsPassed++;
}

template<typename T>
double GeneticAlgorithm<T>::getBestFitness() {
    if(bestIndividual != nullptr){
        return problem->getWorstPossibleFitness();
    }
}

template<typename T>
Individual *GeneticAlgorithm<T>::getBestIndividual() {
    return bestIndividual;
}

template<typename T>
void GeneticAlgorithm<T>::initPopulation() {
    clearPopulation();
    for(int i = 0; i < popSize; i++){
        population.push_back(problem->randomizedSolution());
    }
}

template<typename T>
void GeneticAlgorithm<T>::select() {
    std::vector<Individual*> parentPopulation;
    while(parentPopulation.size() != population.size()){
        std::vector<Individual*> randomIndividuals = pickTwoAtRandom();
        if(problem->compareSolutions(randomIndividuals[0], randomIndividuals[1])){
            parentPopulation.push_back(new Individual(*randomIndividuals[0]));
        } else {
            parentPopulation.push_back(new Individual(*randomIndividuals[1]));
        }
    }
}

template<typename T>
void GeneticAlgorithm<T>::crossover() {
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

template<typename T>
void GeneticAlgorithm<T>::mutate() {
    for(int i = 0; i < population.size(); i++){
        if(shouldMutate()){
            population[i]->mutate(randomGenerator);
        }
    }
}

template<typename T>
void GeneticAlgorithm<T>::evaluate() {
    for(Individual* individual : population){
        if(individual->isEvaluated()){
            problem->evaluate(individual);
        }
    }
}

template<typename T>
void GeneticAlgorithm<T>::clearPopulation() {
    for(int i = 0; i < population.size(); i++){
        delete population[i];
    }
    population.clear();
}

template<typename T>
Individual *GeneticAlgorithm<T>::randomFromPopulation() {
    return population[populationDistribution(randomGenerator)];
}

template<typename T>
bool GeneticAlgorithm<T>::shouldCross() {
    return crossoverDistribution(randomGenerator);
}

template<typename T>
bool GeneticAlgorithm<T>::shouldMutate() {
    return mutationDistribution(randomGenerator);
}

template<typename T>
void GeneticAlgorithm<T>::sortPopulationDesc() {
    std::sort(population.begin(), population.end(), T::compareSolutions);
}

template<typename T>
std::vector<Individual *> GeneticAlgorithm<T>::pickTwoAtRandom() {
    Individual *p1 = randomFromPopulation();
    Individual *p2 = randomFromPopulation();
    while(p2 == p1){
        p2 = randomFromPopulation();
    }
    return std::vector<Individual *>{p1, p2};
}
