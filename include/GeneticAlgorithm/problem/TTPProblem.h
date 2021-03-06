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
enum ItemSelectionPolicy {
    ProfitWeightRatio, Lightest, MostProfitable
};

class TTPProblem : public Problem {
public:
    TTPProblem() = default;
    ~TTPProblem();
    double evaluate(Individual* individual) override;

    void initialize(std::string &filename, ItemSelectionPolicy policy);
    Individual *randomizedSolution() override;

    double getWorstPossibleFitness() override;
    bool compareSolutions(Individual *i1, Individual *i2) override;

    bool operator()(Individual *i1, Individual *i2) override;

    bool compareFitnesses(double firstFitness, double secondFitness) override;
    bool fitnessStrictlyBetter(double firstFitness, double secondFitness) override;

    int getProblemSize() override;

    double selectedItemsWeight;
    double selectedItemsProfit;
    int getFitnessFunctionEvaluations() override;
    double getDistance(int firstCityIndex, int secondCityIndex);
private:
    void load(std::string &filename) override;
    void selectItems(ItemSelectionPolicy policy);
    void calculateDistances();
    void addNewItem(int index, int profit, int weight, int assignedNodeIndex);
    std::vector<std::string> splitInputLine(std::string &line);

    int fitnessFunctionEvaluationsNumber;

    static bool selectBetterWeightProfitItem(KnapsackItem *firstItem, KnapsackItem *secondItem);
    static bool selectLighterItem(KnapsackItem *firstItem, KnapsackItem *secondItem);
    static bool selectProfitableItem(KnapsackItem *firstItem, KnapsackItem *secondItem);
    int numberOfCities;
    int numberOfItems;
    int capacityOfKnapsack;
    double vMin;
    double vMax;

    std::unordered_map<int, std::unordered_map<int, double>> cityDistances;

    std::vector<KnapsackItem*> allItems;
    std::unordered_map<int, std::vector<KnapsackItem*>> selectedItems;
    std::unordered_map<int, double> weightsInCities;
    std::unordered_map<int, double> profitInCities;

    std::vector<City*> cities;

    double calculateDistance(City *firstCity, City *secondCity);

    void selectAllFittingItems();
};


#endif //GENETICALGORITHM_TTPEVALUATOR_H
