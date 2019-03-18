//
// Created by Szymon on 18.03.2019.
//

#include "../include/GeneticAlgorithm/Mutator.h"

Mutator::Mutator(double mutProb, std::mt19937 *randomGenerator):
mutProb(mutProb),
randomGenerator(randomGenerator),
mutationDistribution(std::bernoulli_distribution(mutProb)){}

bool Mutator::shouldMutate() {
    return mutationDistribution(*randomGenerator);
}