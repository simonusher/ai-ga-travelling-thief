//
// Created by Szymon on 18.03.2019.
//

#include "../include/GeneticAlgorithm/AllGeneRandomSwapMutator.h"

AllGeneRandomSwapMutator::AllGeneRandomSwapMutator(double mutProb, std::mt19937 *randomGenerator) : Mutator(mutProb,
                                                                                                            randomGenerator) {}

void AllGeneRandomSwapMutator::mutate(const std::vector<Individual *> &population) {
    for(int i = 0; i < population.size(); i++){
        for(int j = 0; j < population[i]->getSolution().size(); j++){
            if(shouldMutate()){
                population[i]->swapWithRandom(j, *randomGenerator);
            }
        }
    }
}
