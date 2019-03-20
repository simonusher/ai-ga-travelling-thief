//
// Created by Szymon on 10/03/2019.
//

#ifndef GENETICALGORITHM_EVALUATOR_H
#define GENETICALGORITHM_EVALUATOR_H

#include "Individual.h"
#include <string>

class Problem {
public:
    virtual ~Problem() = default;
    virtual double evaluate(Individual* individual) = 0;
    virtual void load(std::string& filename) = 0;
    virtual Individual* randomizedSolution() = 0;
    virtual double getWorstPossibleFitness() = 0;
    virtual bool compareSolutions(Individual *i1, Individual *i2) = 0;
    virtual bool operator()(Individual *i1, Individual *i2) = 0;
    virtual bool compareFitnesses(double firstFitness, double secondFitness) = 0;
    virtual bool fitnessStrictlyBetter(double firstFitness, double secondFitness) = 0;
    virtual int getProblemSize() = 0;
};


#endif //GENETICALGORITHM_EVALUATOR_H
