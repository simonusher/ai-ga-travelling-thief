//
// Created by Szymon on 18.03.2019.
//

#include "../../include/GeneticAlgorithm/operators/AllGeneRandomSwapMutator.h"

AllGeneRandomSwapMutator::AllGeneRandomSwapMutator(double geneMutProb, double individualMutProb, std::mt19937 *randomGenerator) : Mutator(geneMutProb, individualMutProb,
                                                                                                            randomGenerator) {}

void AllGeneRandomSwapMutator::mutate(const std::vector<Individual *> &population) {
    for(int i = 0; i < population.size(); i++){
        for(int j = 0; j < population[i]->getTspSolution().size(); j++){
            if(shouldMutateIndividual()){
                population[i]->swapWithRandom(j, *randomGenerator);
            }
        }
    }
}
