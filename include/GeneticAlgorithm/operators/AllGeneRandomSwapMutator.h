//
// Created by Szymon on 18.03.2019.
//

#ifndef GENETICALGORITHM_ALLGENERANDOMSWAPMUTATOR_H
#define GENETICALGORITHM_ALLGENERANDOMSWAPMUTATOR_H


#include "Mutator.h"

class AllGeneRandomSwapMutator : public Mutator {
public:
    AllGeneRandomSwapMutator(double geneMutProb, double individualMutProb, std::mt19937 *randomGenerator);
private:
    void mutate(const std::vector<Individual *> &population) override;
};


#endif //GENETICALGORITHM_ALLGENERANDOMSWAPMUTATOR_H
