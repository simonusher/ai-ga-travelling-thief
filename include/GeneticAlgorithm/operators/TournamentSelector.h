//
// Created by Szymon on 18.03.2019.
//

#ifndef GENETICALGORITHM_TOURNAMENTSELECTOR_H
#define GENETICALGORITHM_TOURNAMENTSELECTOR_H


#include "Selector.h"
#include <vector>
#include <algorithm>

class TournamentSelector : public Selector {
public:
    TournamentSelector(Problem *problem, int tournamentSize, int populationSize, std::mt19937* randomGenerator);

    Individual *selectParent(const std::vector<Individual *> &population) override;

    std::vector<Individual*> selectAllParents(const std::vector<Individual *> &population) override;

    std::vector<Individual*> pickNAtRandom(const std::vector<Individual *> &population);
    Individual* performTournament(std::vector<Individual*>& tournees);


private:
    int tournamentSize;
    int populationSize;
    std::vector<int> populationIndices;
};


#endif //GENETICALGORITHM_TOURNAMENTSELECTOR_H
