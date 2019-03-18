//
// Created by Szymon on 10/03/2019.
//

#include "../include/GeneticAlgorithm/Individual.h"

Individual::Individual(std::vector<int> &solution) : solution(solution), fitness(0), evaluated(false){}

std::vector<Individual *> Individual::crossover(std::mt19937 &randomGenerator, Individual &other) {
    std::uniform_int_distribution<int> geneDistribution(0, solution.size() - 1);
    int firstGeneIndex = geneDistribution(randomGenerator);
    int secondGeneIndex = geneDistribution(randomGenerator);
    while(secondGeneIndex == firstGeneIndex){
        secondGeneIndex = geneDistribution(randomGenerator);
    }
    if(firstGeneIndex > secondGeneIndex){
        std::swap(firstGeneIndex, secondGeneIndex);
    }
    if(firstGeneIndex == 0 && secondGeneIndex == solution.size()){
        geneDistribution = std::uniform_int_distribution<int>(1, solution.size() - 2);
        secondGeneIndex = geneDistribution(randomGenerator);
    }

    std::vector<Individual*> offspring;
    std::vector<int> firstSolution(solution.size());
    std::vector<int> secondSolution(solution.size());

    std::set<int> firstCrossedGenes(solution.begin() + firstGeneIndex, solution.begin() + secondGeneIndex + 1);
    std::set<int> secondCrossedGenes(other.solution.begin() + firstGeneIndex, other.solution.begin() + secondGeneIndex + 1);

    for(int i = firstGeneIndex; i < secondGeneIndex; i++){
        firstSolution[i] = solution[i];
        secondSolution[i] = other.solution[i];
    }

    int firstTakeIndex = 0;
    int secondTakeIndex = 0;

    for(int i = 0; i < solution.size(); i++){
        if(i >= firstGeneIndex && i <= secondGeneIndex){
            firstSolution[i] = other.solution[i];
            secondSolution[i] = solution[i];
        }
        else {
            while(firstCrossedGenes.find(other.solution[secondTakeIndex]) != firstCrossedGenes.end()){
                secondTakeIndex++;
            }
            while(secondCrossedGenes.find(solution[firstTakeIndex]) != secondCrossedGenes.end()){
                firstTakeIndex++;
            }
            firstSolution[i] = solution[firstTakeIndex];
            secondSolution[i] = other.solution[secondTakeIndex];
            firstTakeIndex++;
            secondTakeIndex++;
        }
    }

    return std::vector<Individual *>{ new Individual(firstSolution), new Individual(secondSolution) };
}

void Individual::mutate(std::mt19937 &randomGenerator) {
    std::uniform_int_distribution<int> geneDistribution(0, solution.size() -1);
    int firstGeneIndex = geneDistribution(randomGenerator);
    int secondGeneIndex = geneDistribution(randomGenerator);
    while(secondGeneIndex == firstGeneIndex){
        secondGeneIndex = geneDistribution(randomGenerator);
    }
    std::swap(solution[firstGeneIndex], solution[secondGeneIndex]);
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
    std::uniform_int_distribution<int> geneDistribution(0, solution.size() -1);
    int secondGeneIndex = geneDistribution(randomGenerator);
    while(secondGeneIndex == firstGeneIndex){
        secondGeneIndex = geneDistribution(randomGenerator);
    }
    std::swap(solution[firstGeneIndex], solution[secondGeneIndex]);
    setEvaluated(false);
}

const std::vector<int> &Individual::getSolution() const {
    return solution;
}

void Individual::swapGenes(int firstGeneIndex, int secondGeneIndex) {
    std::swap(solution[firstGeneIndex], solution[secondGeneIndex]);
    setEvaluated(false);
}
