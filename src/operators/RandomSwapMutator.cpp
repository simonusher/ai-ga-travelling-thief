//
// Created by Szymon on 18.03.2019.
//

#include "../../include/GeneticAlgorithm/operators/RandomSwapMutator.h"

RandomSwapMutator::RandomSwapMutator(double geneMutProb, double individualMutProb, std::mt19937 *randomGenerator) : Mutator(geneMutProb, individualMutProb,
                                                                                              randomGenerator) {}

void RandomSwapMutator::mutate(const std::vector<Individual *> &population) {
    for(int i = 0; i < population.size(); i++){
        if(shouldMutateIndividual()){
            population[i]->mutate(*randomGenerator);
        }
    }
}
