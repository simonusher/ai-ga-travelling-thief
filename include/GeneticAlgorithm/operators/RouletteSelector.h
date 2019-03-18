//
// Created by Szymon on 18.03.2019.
//

#ifndef GENETICALGORITHM_ROULETTESELECTOR_H
#define GENETICALGORITHM_ROULETTESELECTOR_H

#include <algorithm>
#include "Selector.h"

class RouletteSelector : public Selector {
public:
    RouletteSelector(Problem *problem, std::mt19937 *randomGenerator);
    std::vector<Individual*> selectAllParents(std::vector<Individual *> &population) override;
    Individual *selectParent(std::vector<Individual *> &population) override;
    static bool higherFitness(Individual *first, Individual *second);
    static bool lowerFitness(Individual *first, Individual *second);
private:
    void sortPopulation(std::vector<Individual*> &population);
    void constructRoullete(std::vector<Individual*> &population);
    int nextParentIndex();
    std::uniform_real_distribution<double> rouletteDistribution;
    std::vector<double> roulette;
};


#endif //GENETICALGORITHM_ROULETTESELECTOR_H
