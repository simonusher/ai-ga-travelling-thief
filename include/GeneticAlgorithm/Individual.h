//
// Created by Szymon on 10/03/2019.
//

#ifndef GENETICALGORITHM_INDIVIDUAL_H
#define GENETICALGORITHM_INDIVIDUAL_H

#include <vector>
#include <random>
#include <set>
#include <iostream>

class Individual {
public:
    explicit Individual(std::vector<int>& solution);
    virtual std::vector<Individual*> crossover(std::mt19937 &randomGenerator, Individual& other);
    virtual void mutate(std::mt19937 randomGenerator);
    virtual void swap(int firstGeneIndex, std::mt19937 randomGenerator);

    double getFitness() const;

    void setFitness(double fitness);

    bool isEvaluated() const;

    void setEvaluated(bool evaluated);

    std::vector<int> solution;
private:
    double fitness;
    bool evaluated;
};


#endif //GENETICALGORITHM_INDIVIDUAL_H