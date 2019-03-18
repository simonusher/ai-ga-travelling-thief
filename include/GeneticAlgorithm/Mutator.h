//
// Created by Szymon on 18.03.2019.
//

#ifndef GENETICALGORITHM_MUTATOR_H
#define GENETICALGORITHM_MUTATOR_H

#include "Individual.h"

class Mutator {
public:
    Mutator(double mutProb, std::mt19937 *randomGenerator);
    virtual ~Mutator() = default;
    virtual void mutate(const std::vector<Individual*>& population) = 0;

protected:
    virtual bool shouldMutate();
    std::mt19937* randomGenerator;
    std::bernoulli_distribution mutationDistribution;
    double mutProb;
};
#endif //GENETICALGORITHM_MUTATOR_H
