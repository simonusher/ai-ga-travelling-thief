#include <iostream>
#include "../include/GeneticAlgorithm/Individual.h"
#include "../include/GeneticAlgorithm/TTPProblem.h"
#include "../include/GeneticAlgorithm/GeneticAlgorithm.h"

int main() {
    TTPProblem problem;
    std::string filename("hard_1.ttp");
    problem.initialize(filename, MostProfitable);
//    Individual *i = problem.randomizedSolution();
//    problem.evaluate(i);
//    std::cout << i->getFitness();
    GeneticAlgorithm ga(100, 0.9, 0.1, &problem);
    ga.run(100);
    for(int i = 0; i < ga.getBestIndividual()->solution.size(); i++){
        std::cout << ga.getBestIndividual()->solution[i] << " ";
    }
}