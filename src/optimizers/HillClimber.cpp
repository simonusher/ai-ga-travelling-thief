//
// Created by Szymon on 15.03.2019.
//

#include "../../include/GeneticAlgorithm/optimizers/HillClimber.h"

HillClimber::HillClimber(Problem *problem, Logger *logger) : problem(problem), logger(logger), bestOverall(nullptr) {}

void HillClimber::hillClimb(int numberOfSolutions) {
    for(int i = 0; i < numberOfSolutions; i++){
        Individual *current = problem->randomizedSolution();
        while(seenSolution(current)){
            delete current;
            current = problem->randomizedSolution();
        }
        seenSolutions.insert(current->getTspSolution());
        improve(current);
        if(bestOverall == nullptr || problem->compareSolutions(current, bestOverall)){
            delete bestOverall;
            bestOverall = current;
        }
        *logger << i << ";" <<  bestOverall->getFitness() << ";" << current->getFitness() << ";" << problem->getFitnessFunctionEvaluations() << "\n";
    }
}

bool HillClimber::seenSolution(Individual *individual) {
    return seenSolutions.find(individual->getTspSolution()) != seenSolutions.end();
}

void HillClimber::improve(Individual *individual) {
    bool improved = true;
    double currentBestFitness = problem->evaluate(individual);
    while(improved){
        improved = false;
        for (int i = 0; i < individual->getTspSolution().size() - 1; i++) {
            for (int j = i + 1; j < individual->getTspSolution().size(); j++) {
                individual->swapGenes(i, j);
                problem->evaluate(individual);
                if(problem->fitnessStrictlyBetter(individual->getFitness(), currentBestFitness)){
                    currentBestFitness = individual->getFitness();
                    improved = true;
                } else {
                    individual->swapGenes(i, j);
                }
            }
        }
    }
}
