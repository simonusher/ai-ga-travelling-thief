//
// Created by Szymon on 10/03/2019.
//

#ifndef GENETICALGORITHM_TTPEVALUATOR_H
#define GENETICALGORITHM_TTPEVALUATOR_H


#include "Problem.h"
#include "KnapsackItem.h"
#include "City.h"
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <limits>

class TTPProblem : public Problem {
public:
    TTPProblem(std::mt19937 *randomGenerator);
    ~TTPProblem();
    double evaluate(Individual* individual) override;

    void initialize(std::string &filename);
    Individual *randomizedSolution() override;

    double getWorstPossibleFitness() override;
    bool compareSolutions(Individual *i1, Individual *i2) override;

    bool compareFitnesses(double firstFitness, double secondFitness) override;
    bool fitnessStrictlyBetter(double firstFitness, double secondFitness) override;

    int getProblemSize() override;

    int getFitnessFunctionEvaluations() override;
    double getDistance(int firstCityIndex, int secondCityIndex);
    void fixIfIncorrect(Individual *individual) override;
private:
    void load(std::string &filename) override;
    void calculateDistances();
    void addNewItem(int index, int profit, int weight, int assignedNodeIndex);

    std::vector<std::string> splitInputLine(std::string &line);

    int fitnessFunctionEvaluationsNumber;
    int numberOfCities;
    int numberOfItems;
    int capacityOfKnapsack;
    double vMin;

    double vMax;

    std::unordered_map<int, std::unordered_map<int, double>> cityDistances;
    std::vector<City*> cities;
    std::vector<KnapsackItem*> allItems;

    std::unordered_map<int, std::vector<KnapsackItem*>> itemsInCities;

    std::mt19937 *randomGenerator;

    std::pair<double, double> getWeightAndProfitInCity(int cityIndex, const std::vector<bool> &knapsackSolution);

    double calculateDistance(City *firstCity, City *secondCity);

    void setItemsInCities();

    void fixup(double weight, Individual *individual, std::vector<int> selectedItemsIndices);
};


#endif //GENETICALGORITHM_TTPEVALUATOR_H
