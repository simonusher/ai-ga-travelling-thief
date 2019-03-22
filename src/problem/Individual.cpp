//
// Created by Szymon on 10/03/2019.
//

#include "../../include/GeneticAlgorithm/problem/Individual.h"

Individual::Individual(std::vector<int> &solution, std::vector<bool>& knapsackSolution) : tspSolution(solution), knapsackSolution(knapsackSolution), fitness(0), evaluated(false){}

std::vector<Individual *> Individual::crossover(std::mt19937 &randomGenerator, Individual &other) {
    std::uniform_int_distribution<int> geneDistribution(0, tspSolution.size() - 1);
    int firstGeneIndex = geneDistribution(randomGenerator);
    int secondGeneIndex = geneDistribution(randomGenerator);
    while(secondGeneIndex == firstGeneIndex){
        secondGeneIndex = geneDistribution(randomGenerator);
    }
    if(firstGeneIndex > secondGeneIndex){
        std::swap(firstGeneIndex, secondGeneIndex);
    }
    if(firstGeneIndex == 0 && secondGeneIndex == tspSolution.size()){
        geneDistribution = std::uniform_int_distribution<int>(1, tspSolution.size() - 2);
        secondGeneIndex = geneDistribution(randomGenerator);
    }

    std::vector<Individual*> offspring;
    std::vector<int> firstTspSolution(tspSolution.size());
    std::vector<int> secondTspSolution(tspSolution.size());

    std::set<int> firstCrossedGenes(tspSolution.begin() + firstGeneIndex, tspSolution.begin() + secondGeneIndex + 1);
    std::set<int> secondCrossedGenes(other.tspSolution.begin() + firstGeneIndex, other.tspSolution.begin() + secondGeneIndex + 1);

    for(int i = firstGeneIndex; i < secondGeneIndex; i++){
        firstTspSolution[i] = tspSolution[i];
        secondTspSolution[i] = other.tspSolution[i];
    }

    int firstTakeIndex = 0;
    int secondTakeIndex = 0;

    for(int i = 0; i < tspSolution.size(); i++){
        if(i >= firstGeneIndex && i <= secondGeneIndex){
            firstTspSolution[i] = other.tspSolution[i];
            secondTspSolution[i] = tspSolution[i];
        }
        else {
            while(firstCrossedGenes.find(other.tspSolution[secondTakeIndex]) != firstCrossedGenes.end()){
                secondTakeIndex++;
            }
            while(secondCrossedGenes.find(tspSolution[firstTakeIndex]) != secondCrossedGenes.end()){
                firstTakeIndex++;
            }
            firstTspSolution[i] = tspSolution[firstTakeIndex];
            secondTspSolution[i] = other.tspSolution[secondTakeIndex];
            firstTakeIndex++;
            secondTakeIndex++;
        }
    }

    std::uniform_int_distribution<int> crossPointDistribution(1, knapsackSolution.size() - 2);
    int crossPoint = crossPointDistribution(randomGenerator);

    std::vector<bool> firstKnapsackSolution(this->knapsackSolution);
    std::vector<bool> secondKnapsackSolution(other.knapsackSolution);

    for(int i = crossPoint; i < knapsackSolution.size(); i++){
        firstKnapsackSolution[i] = other.knapsackSolution[i];
        secondKnapsackSolution[i] = this->knapsackSolution[i];
    }

    return std::vector<Individual *>{ new Individual(firstTspSolution, firstKnapsackSolution), new Individual(secondTspSolution, secondKnapsackSolution) };
}

void Individual::mutate(std::mt19937 &randomGenerator) {
    std::uniform_int_distribution<int> geneDistribution(0, tspSolution.size() -1);
    int firstGeneIndex = geneDistribution(randomGenerator);
    int secondGeneIndex = geneDistribution(randomGenerator);
    while(secondGeneIndex == firstGeneIndex){
        secondGeneIndex = geneDistribution(randomGenerator);
    }
    std::swap(tspSolution[firstGeneIndex], tspSolution[secondGeneIndex]);
    setEvaluated(false);
}

double Individual::getFitness() const {
    return fitness;
}

void Individual::setFitness(double fitness) {
    this->fitness = fitness;
    this->setEvaluated(true);
}

bool Individual::isEvaluated() const {
    return evaluated;
}

void Individual::setEvaluated(bool evaluated) {
    this->evaluated = evaluated;
}

void Individual::swapWithRandom(int firstGeneIndex, std::mt19937 &randomGenerator) {
    std::uniform_int_distribution<int> geneDistribution(0, tspSolution.size() -1);
    int secondGeneIndex = geneDistribution(randomGenerator);
    while(secondGeneIndex == firstGeneIndex){
        secondGeneIndex = geneDistribution(randomGenerator);
    }
    std::swap(tspSolution[firstGeneIndex], tspSolution[secondGeneIndex]);
    setEvaluated(false);
}

const std::vector<int> &Individual::getTspSolution() const {
    return tspSolution;
}

const std::vector<bool> &Individual::getKnapsackSolution() const {
    return knapsackSolution;
}

void Individual::swapGenes(int firstGeneIndex, int secondGeneIndex) {
    std::swap(tspSolution[firstGeneIndex], tspSolution[secondGeneIndex]);
    setEvaluated(false);
}

void Individual::invertTsp(int firstGeneIndex, int secondGeneIndex) {
//    std::reverse(tspSolution.begin() + firstGeneIndex, tspSolution.begin() + secondGeneIndex);
    for(int i = firstGeneIndex, j = secondGeneIndex; i < j; i++, j--){
        std::swap(tspSolution[i], tspSolution[j]);
    }
    setEvaluated(false);
}

void Individual::flipKspGene(int index) {
    knapsackSolution[index] = !knapsackSolution[index];
}
