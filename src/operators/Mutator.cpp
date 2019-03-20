//
// Created by Szymon on 18.03.2019.
//

#include "../../include/GeneticAlgorithm/operators/Mutator.h"

Mutator::Mutator(double mutProb, std::mt19937 *randomGenerator):
mutProb(mutProb),
randomGenerator(randomGenerator),
mutationDistribution(mutProb){}

bool Mutator::shouldMutate() {
    return mutationDistribution(*randomGenerator);
}