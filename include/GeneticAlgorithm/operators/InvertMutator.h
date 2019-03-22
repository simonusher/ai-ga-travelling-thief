//
// Created by Szymon on 22.03.2019.
//

#ifndef GENETICALGORITHM_INVERTMUTATOR_H
#define GENETICALGORITHM_INVERTMUTATOR_H


#include "Mutator.h"

class InvertMutator : public Mutator {
public:
    InvertMutator(double geneMutProb, double individualMutProb, std::mt19937 *randomGenerator);
private:
    void mutate(const std::vector<Individual *> &population) override;
};


#endif //GENETICALGORITHM_INVERTMUTATOR_H
