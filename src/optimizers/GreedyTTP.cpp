//
// Created by Szymon on 20.03.2019.
//

#include "../../include/GeneticAlgorithm/optimizers/GreedyTTP.h"

GreedyTTP::GreedyTTP(TTPProblem *problem, Logger *logger): problem(problem), logger(logger), bestOverall(nullptr) {
    int problemSize = problem->getProblemSize();
    possibleGenes = std::vector<int>(problemSize);
    std::iota(possibleGenes.begin(), possibleGenes.end(), 1);
}

void GreedyTTP::solve() {
    for(int i = 0; i < possibleGenes.size(); i++){
        int startingCity = possibleGenes[i];
        remainingCities = possibleGenes;
        remainingCities.erase(remainingCities.begin() + i);
        std::vector<int> solution = solveForStartingIndex(startingCity);
        Individual individual(solution);
        if(bestOverall == nullptr || problem->compareSolutions(&individual, bestOverall)){
            delete bestOverall;
            bestOverall = new Individual(individual);
        }
        *logger << i << ";" << bestOverall->getFitness() << ";" << individual.getFitness() << "\n";
    }
}

std::vector<int> GreedyTTP::solveForStartingIndex(int startingIndex) {
    std::vector<int> solution;
    solution.push_back(startingIndex);
    int lastCity = startingIndex;
    while(remainingCities.size() != 0){
        int bestCityIndex = findMinimumDistanceCityIndex(lastCity);
        lastCity = remainingCities[bestCityIndex];
        remainingCities.erase(remainingCities.begin() + bestCityIndex);
        solution.push_back(lastCity);
    }
    return solution;
}

int GreedyTTP::findMinimumDistanceCityIndex(int startingCityIndex) {
    double shortestDistance = std::numeric_limits<double>::max();
    int bestCityIndex = -1;
    for(int i = 0; i < remainingCities.size(); i++){
        double distance = problem->getDistance(startingCityIndex, remainingCities[i]);
        if(shortestDistance > distance){
            shortestDistance = distance;
            bestCityIndex = i;
        }
    }
    return bestCityIndex;
}
