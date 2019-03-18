//
// Created by Szymon on 15.03.2019.
//

#ifndef GENETICALGORITHM_RANDOMSEARCH_H
#define GENETICALGORITHM_RANDOMSEARCH_H


#include "Problem.h"
#include "Logger.h"
#include "VectorHasher.h"
#include <unordered_set>
#include <vector>

using std::vector;
using std::unordered_set;

class RandomSearch {
public:
    RandomSearch(Problem *problem, Logger *logger);
    void search(int numberOfSolutions);
    bool seenSolution(const std::vector<int> &solution);
    ~RandomSearch();
private:
    Problem *problem;
    Logger *logger;
    Individual *bestOverall;
    unordered_set<vector<int>, VectorHasher> seen;
};


#endif //GENETICALGORITHM_RANDOMSEARCH_H
