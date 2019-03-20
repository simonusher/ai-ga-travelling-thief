//
// Created by Szymon on 18.03.2019.
//

#include "../../include/GeneticAlgorithm/operators/RouletteSelector.h"

RouletteSelector::RouletteSelector(Problem *problem, std::mt19937 *randomGenerator) : Selector(problem,
                                                                                               randomGenerator) {}

Individual *RouletteSelector::selectParent(std::vector<Individual *> &population) {
    sortPopulation(population);
    constructRoullete(population);
    int nextIndex = nextParentIndex();
    return new Individual(*population[nextIndex]);
}

std::vector<Individual *> RouletteSelector::selectAllParents(std::vector<Individual *> &population) {
    sortPopulation(population);
    constructRoullete(population);
    std::vector<Individual*> newPopulation;
    while (newPopulation.size() != population.size()){
        int nextIndex = nextParentIndex();
        newPopulation.push_back(new Individual(*(population[nextIndex])));
    }
    return newPopulation;
}

bool RouletteSelector::higherFitness(Individual *first, Individual *second) {
    return first->getFitness() > second->getFitness();
}

bool RouletteSelector::lowerFitness(Individual *first, Individual *second) {
    return first->getFitness() < second->getFitness();
}

void RouletteSelector::sortPopulation(std::vector<Individual *> &population) {
    std::sort(population.begin(), population.end(), lowerFitness);
}

void RouletteSelector::constructRoullete(std::vector<Individual *> &population) {
    roulette = std::vector<double>(population.size());
    double worstFitness = population[0]->getFitness();
    double fitnessSum = 0;


    if(worstFitness < 0){
        worstFitness *= -1;
        for(int i = 0; i < population.size(); i++){
            fitnessSum += population[i]->getFitness() + worstFitness;
            roulette[i] = population[i]->getFitness() + worstFitness;
        }
    } else {
        for(int i = 0; i < population.size(); i++){
            fitnessSum += population[i]->getFitness();
            roulette[i] = population[i]->getFitness();
        }
    }

    double sumUntilNow = 0;
    for(int i = 0; i < population.size(); i++){
        double roulettePart = roulette[i] / fitnessSum;
        roulette[i] = roulettePart + sumUntilNow;
        sumUntilNow = roulette[i];
    }

    worstFitness = roulette[0];
    double bestFitness = roulette[roulette.size() - 1];

    rouletteDistribution = std::uniform_real_distribution<double>(worstFitness, bestFitness);
}

int RouletteSelector::nextParentIndex() {
    double roll = rouletteDistribution(*randomGenerator);
    int index = roulette.size() -1;
    for(int i = 0; i < roulette.size(); i++){
        if(roll < roulette[i]){
            index = i;
            break;
        }
    }
    return index;
}
