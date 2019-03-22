//
// Created by Szymon on 22.03.2019.
//

#include "../../include/GeneticAlgorithm/operators/InvertMutator.h"

InvertMutator::InvertMutator(double mutProb, std::mt19937 *randomGenerator) : Mutator(mutProb, randomGenerator) {}

void InvertMutator::mutate(const std::vector<Individual *> &population) {
    int numberOfGenes = population[0]->getSolution().size();
    std::uniform_int_distribution<int> geneDistribution(0, numberOfGenes-1);
    for(int i = 0; i < population.size(); i++){
        for(int j = 0; j < population[i]->getSolution().size(); j++){
            if(shouldMutate()){
                int firstGeneIndex = geneDistribution(*randomGenerator);
                int secondGeneIndex = geneDistribution(*randomGenerator);
                while(secondGeneIndex == firstGeneIndex){
                    secondGeneIndex = geneDistribution(*randomGenerator);
                }
                if(firstGeneIndex > secondGeneIndex){
                    std::swap(firstGeneIndex, secondGeneIndex);
                }
                population[i]->invert(firstGeneIndex, secondGeneIndex);
            }
        }
    }
}
