//
// Created by Szymon on 18.03.2019.
//

#ifndef GENETICALGORITHM_MUTATOR_H
#define GENETICALGORITHM_MUTATOR_H

#include "../problem/Individual.h"

class Mutator {
public:
    Mutator(double geneMutProb, double individualMutProb, std::mt19937 *randomGenerator);
    virtual ~Mutator() = default;
    virtual void mutate(const std::vector<Individual*>& population) = 0;

protected:
    virtual bool shouldMutateIndividual();
    virtual bool shouldMutateGene();
    std::mt19937* randomGenerator;
    std::bernoulli_distribution individualMutationDistribution;
    std::bernoulli_distribution geneMutationDistribution;
    double geneMutProb;
    double individualMutProb;
};
#endif //GENETICALGORITHM_MUTATOR_H
