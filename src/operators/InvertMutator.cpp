//
// Created by Szymon on 22.03.2019.
//

#include "../../include/GeneticAlgorithm/operators/InvertMutator.h"

InvertMutator::InvertMutator(double geneMutProb, double individualMutProb, std::mt19937 *randomGenerator) :
    Mutator(geneMutProb, individualMutProb, randomGenerator) {}

void InvertMutator::mutate(const std::vector<Individual *> &population) {
    int numberOfGenes = population[0]->getTspSolution().size();
    std::uniform_int_distribution<int> geneDistribution(0, numberOfGenes-1);
    for(int i = 0; i < population.size(); i++){
        if(shouldMutateIndividual()){
            int firstGeneIndex = geneDistribution(*randomGenerator);
            int secondGeneIndex = geneDistribution(*randomGenerator);
            while(secondGeneIndex == firstGeneIndex){
                secondGeneIndex = geneDistribution(*randomGenerator);
            }
            if(firstGeneIndex > secondGeneIndex){
                std::swap(firstGeneIndex, secondGeneIndex);
            }
            population[i]->invertTsp(firstGeneIndex, secondGeneIndex);
        }
        for(int j = 0; j < numberOfGenes; j++){
            if(shouldMutateGene()){
                population[i]->flipKspGene(j);
            }
        }
    }
}
