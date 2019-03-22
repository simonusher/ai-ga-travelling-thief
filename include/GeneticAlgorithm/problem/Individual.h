//
// Created by Szymon on 10/03/2019.
//

#ifndef GENETICALGORITHM_INDIVIDUAL_H
#define GENETICALGORITHM_INDIVIDUAL_H

#include <vector>
#include <random>
#include <set>
#include <iostream>
#include <algorithm>

class Individual {
public:
    explicit Individual(std::vector<int>& tspSolution, std::vector<bool>& knapsackSolution);
    virtual std::vector<Individual*> crossover(std::mt19937 &randomGenerator, Individual& other);
    virtual void mutate(std::mt19937& randomGenerator);
    virtual void swapWithRandom(int firstGeneIndex, std::mt19937& randomGenerator);
    virtual void swapGenes(int firstGeneIndex, int secondGeneIndex);
    virtual void flipKspGene(int index);
    virtual void invertTsp(int firstGeneIndex, int secondGeneIndex);

    double getFitness() const;

    void setFitness(double fitness);

    bool isEvaluated() const;

    void setEvaluated(bool evaluated);

    const std::vector<int> &getTspSolution() const;

    const std::vector<bool> &getKnapsackSolution() const;

private:
    std::vector<int> tspSolution;
    std::vector<bool> knapsackSolution;
    double fitness;
    bool evaluated;
};


#endif //GENETICALGORITHM_INDIVIDUAL_H