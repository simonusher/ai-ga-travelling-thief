//
// Created by Szymon on 20.03.2019.
//

#ifndef GENETICALGORITHM_GREEDY_H
#define GENETICALGORITHM_GREEDY_H


#include "../problem/Problem.h"
#include "../util/Logger.h"

class Greedy {
public:
    Greedy(Problem *problem, Logger *logger);
private:
    Problem *problem;
    Logger *logger;
    Individual *bestOverall;
};


#endif //GENETICALGORITHM_GREEDY_H
