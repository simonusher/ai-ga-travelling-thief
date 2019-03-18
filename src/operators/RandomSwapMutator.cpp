//
// Created by Szymon on 18.03.2019.
//

#include "../../include/GeneticAlgorithm/operators/RandomSwapMutator.h"

RandomSwapMutator::RandomSwapMutator(double mutProb, std::mt19937 *randomGenerator) : Mutator(mutProb,
                                                                                              randomGenerator) {}

void RandomSwapMutator::mutate(const std::vector<Individual *> &population) {
    for(int i = 0; i < population.size(); i++){
        if(shouldMutate()){
            population[i]->mutate(*randomGenerator);
        }
    }
}
