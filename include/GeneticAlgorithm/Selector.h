//
// Created by Szymon on 18.03.2019.
//

#ifndef GENETICALGORITHM_SELECTOR_H
#define GENETICALGORITHM_SELECTOR_H


#include "Individual.h"
#include "Problem.h"

class Selector {
public:
    Selector(Problem *problem, std::mt19937* randomGenerator) : problem(problem), randomGenerator(randomGenerator) {}
    virtual ~Selector() = default;
    virtual Individual* selectParent(const std::vector<Individual*>& population) = 0;
    virtual std::vector<Individual*> selectAllParents(const std::vector<Individual*>& population) = 0;

protected:
    Problem* problem;
    std::mt19937* randomGenerator;
};


#endif //GENETICALGORITHM_SELECTOR_H
