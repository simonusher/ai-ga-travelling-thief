//
// Created by Szymon on 20.03.2019.
//

#ifndef GENETICALGORITHM_GREEDY_H
#define GENETICALGORITHM_GREEDY_H


#include "../util/Logger.h"
#include "../problem/TTPProblem.h"

class GreedyTTP {
public:
    GreedyTTP(TTPProblem *problem, Logger *logger);
    void solve();
private:
    std::vector<int> solveForStartingIndex(int startingIndex);
    int findMinimumDistanceCityIndex(int startingCityIndex);
    std::vector<int> remainingCities;
    std::vector<int> possibleGenes;
    TTPProblem *problem;
    Logger *logger;
    Individual *bestOverall;
};


#endif //GENETICALGORITHM_GREEDY_H
