//
// Created by Szymon on 15.03.2019.
//

#ifndef GENETICALGORITHM_HILLCLIMBER_H
#define GENETICALGORITHM_HILLCLIMBER_H


#include "../problem/Problem.h"
#include "../util/Logger.h"
#include "../util/VectorHasher.h"
#include <unordered_set>
#include <vector>
using std::unordered_set;
using std::vector;

class HillClimber {
public:
    HillClimber(Problem *problem, Logger *logger);
    void hillClimb(int numberOfSolutions);
private:
    bool seenSolution(Individual *individual);
    Problem *problem;
    Logger *logger;
    Individual *bestOverall;
    unordered_set<vector<int>, VectorHasher> seenSolutions;

    void improve(Individual *individual);
};


#endif //GENETICALGORITHM_HILLCLIMBER_H
