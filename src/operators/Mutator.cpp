//
// Created by Szymon on 18.03.2019.
//

#include "../../include/GeneticAlgorithm/operators/Mutator.h"

Mutator::Mutator(double geneMutProb, double individualMutProb, std::mt19937 *randomGenerator):
    geneMutProb(geneMutProb),
    individualMutProb(individualMutProb),
    randomGenerator(randomGenerator),
    individualMutationDistribution(individualMutProb),
    geneMutationDistribution(geneMutProb){}


bool Mutator::shouldMutateIndividual() {
    return individualMutationDistribution(*randomGenerator);
}

bool Mutator::shouldMutateGene() {
    return geneMutationDistribution(*randomGenerator);
}
