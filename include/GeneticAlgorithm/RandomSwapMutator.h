//
// Created by Szymon on 18.03.2019.
//

#ifndef GENETICALGORITHM_RANDOMSWAPMUTATOR_H
#define GENETICALGORITHM_RANDOMSWAPMUTATOR_H


#include "Mutator.h"

class RandomSwapMutator : public Mutator {
public:
    RandomSwapMutator(double mutProb, std::mt19937 *randomGenerator);

    void mutate(const std::vector<Individual *> &population) override;
};


#endif //GENETICALGORITHM_RANDOMSWAPMUTATOR_H
