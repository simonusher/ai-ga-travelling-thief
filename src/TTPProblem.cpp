//
// Created by Szymon on 10/03/2019.
//

#include "../include/GeneticAlgorithm/TTPProblem.h"

void TTPProblem::initialize(std::string &filename, ItemSelectionPolicy policy) {
    load(filename);
    calculateDistances();
    selectItems(policy);
}

double TTPProblem::evaluate(Individual* individual) {
    if(!individual->isEvaluated()){
        double itemsWeight = 0;
        double totalTime = 0;
        double currentVelocity = 0;
        const std::vector<int> &solution = individual->solution;

        for(int i = 0; i < solution.size() - 1; i++){
            itemsWeight += weightsInCities[solution[i]];
            currentVelocity = vMax - (itemsWeight * ((vMax - vMin) / (double)capacityOfKnapsack));
            double distance = getDistance(solution[i], solution[i + 1]);
            double time = distance / currentVelocity;
            totalTime += time;
//            std::cout <<  distance << "," << time << "\n";
        }
        itemsWeight += weightsInCities[solution[solution.size() - 1]];
        currentVelocity = vMax - (itemsWeight * ((vMax - vMin) / (double)capacityOfKnapsack));
        double time = getDistance(solution[solution.size() - 1], solution[0]) / currentVelocity;
        totalTime += time;
//        std::cout <<  getDistance(solution[solution.size() - 1], solution[0]) << "," << time << "\n";
        individual->setFitness(selectedItemsProfit - totalTime);
    }
    return individual->getFitness();
}

void TTPProblem::load(std::string &filename) {
    std::ifstream file;
    std::string line;

    file.open(filename, std::ios::in);
    std::vector<std::string> lineTokens;

    if(file.is_open()){
        std::getline(file, line);
        std::getline(file, line);

        std::getline(file, line);
        lineTokens = splitInputLine(line);
        numberOfCities = std::stoi(lineTokens[lineTokens.size()-1]);

        std::getline(file, line);
        lineTokens = splitInputLine(line);
        numberOfItems = std::stoi(lineTokens[lineTokens.size() - 1]);

        std::getline(file, line);
        lineTokens = splitInputLine(line);
        capacityOfKnapsack = std::stoi(lineTokens[lineTokens.size() - 1]);

        std::getline(file, line);
        lineTokens = splitInputLine(line);
        vMin = std::stod(lineTokens[lineTokens.size() - 1]);

        std::getline(file, line);
        lineTokens = splitInputLine(line);
        vMax = std::stod(lineTokens[lineTokens.size() - 1]);

        std::getline(file, line);
        std::getline(file, line);
        std::getline(file, line);


        for(int i = 0; i < numberOfCities; i++){
            std::getline(file, line);
            lineTokens = splitInputLine(line);
            int index = std::stoi(lineTokens[0]);
            double x = std::stod(lineTokens[1]);
            double y = std::stod(lineTokens[2]);
            cities.push_back(new City(index, x, y));
        }

        std::getline(file, line);

        for(int i = 0; i < numberOfItems; i++){
            std::getline(file, line);
            lineTokens = splitInputLine(line);
            int index = std::stoi(lineTokens[0]);
            int profit = std::stoi(lineTokens[1]);
            int weight = std::stoi(lineTokens[2]);
            int nodeNumber = std::stoi(lineTokens[3]);
            addNewItem(index, profit, weight, nodeNumber);
        }
    }
}

Individual *TTPProblem::randomizedSolution() {
    std::vector<int> solution(numberOfCities);
    std::iota(solution.begin(), solution.end(), cities[0]->getIndex());
    std::random_shuffle(solution.begin(), solution.end());
    return new Individual(solution);
}

double TTPProblem::getWorstPossibleFitness() {
    return std::numeric_limits<double>::lowest();
}

bool TTPProblem::compareSolutions(Individual *i1, Individual *i2) {
    evaluate(i1);
    evaluate(i2);
    return i1->getFitness() >= i2->getFitness();
}

std::vector<std::string> TTPProblem::splitInputLine(std::string &line) {
    std::istringstream stringStream(line);
    std::vector<std::string> lineTokens;
    std::copy(std::istream_iterator<std::string>(stringStream),
              std::istream_iterator<std::string>(),
              std::back_inserter(lineTokens));
    return lineTokens;
}

TTPProblem::~TTPProblem() {
    for(int i = 0; i < cities.size(); i++){
        delete cities[i];
    }

    for(int i = 0; i < allItems.size(); i++){
        delete allItems[i];
    }
}

void TTPProblem::calculateDistances() {
    cityDistances.clear();
    for(int i = 0; i < cities.size(); i++){
        cityDistances.emplace(cities[i]->getIndex(), std::unordered_map<int, double>());
        for(int j = 0; j < cities.size(); j++){
            cityDistances[cities[i]->getIndex()][cities[j]->getIndex()] = calculateDistance(cities[i], cities[j]);
        }
    }
}

void TTPProblem::addNewItem(int index, int profit, int weight, int assignedNodeIndex) {
    allItems.push_back(new KnapsackItem(index, profit, weight, assignedNodeIndex));
}

double TTPProblem::calculateDistance(City *firstCity, City *secondCity) {
    return firstCity->distance(secondCity);
}

void TTPProblem::selectItems(ItemSelectionPolicy policy) {
    switch (policy){
        case ProfitWeightRatio:
            std::sort(allItems.begin(), allItems.end(), TTPProblem::selectBetterWeightProfitItem);
            break;
        case Lightest:
            std::sort(allItems.begin(), allItems.end(), TTPProblem::selectLighterItem);
            break;
        case MostProfitable:
            std::sort(allItems.begin(), allItems.end(), TTPProblem::selectProfitableItem);
            break;
    }
    selectAllFittingItems();
}

bool TTPProblem::selectBetterWeightProfitItem(KnapsackItem *firstItem, KnapsackItem *secondItem){
    return firstItem->getProfitWeightRatio() >= secondItem->getProfitWeightRatio();
}

bool TTPProblem::selectLighterItem(KnapsackItem *firstItem, KnapsackItem *secondItem) {
    return firstItem->getWeight() <= secondItem->getWeight();
}

bool TTPProblem::selectProfitableItem(KnapsackItem *firstItem, KnapsackItem *secondItem) {
    return firstItem->getProfit() >= secondItem->getProfit();
}

double TTPProblem::getDistance(int firstCityIndex, int secondCityIndex) {
    return cityDistances[firstCityIndex][secondCityIndex];
}

void TTPProblem::selectAllFittingItems() {
    selectedItems.clear();
    selectedItemsWeight = 0;
    selectedItemsProfit = 0;
    for(int i = 0; i < cities.size(); i++){
        weightsInCities[cities[i]->getIndex()] = 0;
        profitInCities[cities[i]->getIndex()] = 0;
    }

    for(int i = 0; i < allItems.size() && selectedItemsWeight < capacityOfKnapsack; i++) {
        KnapsackItem *currentItem = allItems[i];
        selectedItems.emplace(currentItem->getAssignedNodeIndex(), std::vector<KnapsackItem*>());

        if(selectedItemsWeight + currentItem->getWeight() < capacityOfKnapsack){
            selectedItems[currentItem->getAssignedNodeIndex()].push_back(currentItem);
            selectedItemsWeight += currentItem->getWeight();
            selectedItemsProfit += currentItem->getProfit();
            weightsInCities[currentItem->getAssignedNodeIndex()] += currentItem->getWeight();
            profitInCities[currentItem->getAssignedNodeIndex()] += currentItem->getProfit();
        }
    }
}

bool TTPProblem::compareForSort(Individual *i1, Individual *i2) {
    return i1->getFitness() >= i2->getFitness();
}