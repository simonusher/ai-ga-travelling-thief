//
// Created by Szymon on 18.03.2019.
//

#include "../../include/GeneticAlgorithm/operators/TournamentSelector.h"

TournamentSelector::TournamentSelector(Problem *problem, int tournamentSize, int populationSize, std::mt19937* randomGenerator) :
    Selector(problem, randomGenerator),
    tournamentSize(tournamentSize),
    populationSize(populationSize),
    populationIndices(std::vector<int>(populationSize))
{
    std::iota(populationIndices.begin(), populationIndices.end(), 0);
}

Individual* TournamentSelector::selectParent(const std::vector<Individual *> &population) {
    std::vector<Individual*> tournees = pickNAtRandom(population);
    Individual *best = performTournament(tournees);
    return best;
}

std::vector<Individual*> TournamentSelector::selectAllParents(const std::vector<Individual *> &population) {
    std::vector<Individual*> parentPopulation;
    while(parentPopulation.size() != population.size()){
        Individual *bestOfN = selectParent(population);
        parentPopulation.push_back(new Individual(*bestOfN));
    }
    return parentPopulation;
}

std::vector<Individual*> TournamentSelector::pickNAtRandom(const std::vector<Individual *> &population) {
    std::shuffle(populationIndices.begin(), populationIndices.end(), *randomGenerator);
    std::vector<Individual*> randomSolutions(tournamentSize);
    for(int i = 0; i < tournamentSize; i++){
        randomSolutions[i] = population[populationIndices[i]];
    }
    return randomSolutions;
}

Individual* TournamentSelector::performTournament(std::vector<Individual*>& tournees) {
    Individual *best = tournees[0];
    for(int i = 1; i < tournees.size(); i++){
        if(problem->compareSolutions(tournees[i], best)){
            best = tournees[i];
        }
    }
    return best;
}