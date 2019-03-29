//

#include "../../include/GeneticAlgorithm/problem/TTPProblem.h"

//
// Created by Szymon on 10/03/2019.
TTPProblem::TTPProblem(std::mt19937 *randomGenerator) : Problem(), randomGenerator(randomGenerator) {

}

void TTPProblem::initialize(std::string &filename) {
    load(filename);
    calculateDistances();
    setItemsInCities();
    fitnessFunctionEvaluationsNumber = 0;
}

double TTPProblem::evaluate(Individual* individual) {
    if(!individual->isEvaluated()){
        fitnessFunctionEvaluationsNumber++;
        double itemsWeight = 0;
        double itemsProfit = 0;
        double totalTime = 0;
        double currentVelocity = 0;
        const std::vector<int> &tspSolution = individual->getTspSolution();
        const std::vector<bool> &knapsackSolution = individual->getKnapsackSolution();

        for(int i = 0; i < tspSolution.size() - 1; i++){
            std::pair<double, double> weightAndProfitInCity = getWeightAndProfitInCity(tspSolution[i], knapsackSolution);
            itemsWeight += weightAndProfitInCity.first;
            itemsProfit += weightAndProfitInCity.second;
            currentVelocity = vMax - (itemsWeight * ((vMax - vMin) / (double)capacityOfKnapsack));
            double distance = getDistance(tspSolution[i], tspSolution[i + 1]);
            double time = distance / currentVelocity;
            totalTime += time;
        }
        std::pair<double, double> weightAndProfitInCity = getWeightAndProfitInCity(tspSolution[tspSolution.size() - 1], individual->getKnapsackSolution());
        itemsWeight += weightAndProfitInCity.first;
        itemsProfit += weightAndProfitInCity.second;
        currentVelocity = vMax - (itemsWeight * ((vMax - vMin) / (double)capacityOfKnapsack));
        double time = getDistance(tspSolution[tspSolution.size() - 1], tspSolution[0]) / currentVelocity;
        totalTime += time;
        individual->setFitness(itemsProfit - totalTime);
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
    std::vector<int> tspSolution(numberOfCities);
    std::iota(tspSolution.begin(), tspSolution.end(), cities[0]->getIndex());
    std::shuffle(tspSolution.begin(), tspSolution.end(), *randomGenerator);

    std::vector<bool> knapsackSolution(numberOfItems);
    std::bernoulli_distribution kspDistribution;
    for(int i = 0; i < numberOfItems; i++){
        knapsackSolution[i] = kspDistribution(*randomGenerator);
    }
    Individual *individual = new Individual(tspSolution, knapsackSolution);
    fixIfIncorrect(individual);
    return individual;
}

double TTPProblem::getWorstPossibleFitness() {
    return std::numeric_limits<double>::lowest();
}

bool TTPProblem::compareSolutions(Individual *i1, Individual *i2) {
    evaluate(i1);
    evaluate(i2);
    return compareFitnesses(i1->getFitness(), i2->getFitness());
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

double TTPProblem::getDistance(int firstCityIndex, int secondCityIndex) {
    return cityDistances[firstCityIndex][secondCityIndex];
}

int TTPProblem::getFitnessFunctionEvaluations() {
    return fitnessFunctionEvaluationsNumber;
}

bool TTPProblem::compareFitnesses(double firstFitness, double secondFitness) {
    return firstFitness > secondFitness;
}

bool TTPProblem::fitnessStrictlyBetter(double firstFitness, double secondFitness) {
    return firstFitness > secondFitness;
}

int TTPProblem::getProblemSize() {
    return numberOfCities;
}

void TTPProblem::fixIfIncorrect(Individual *individual) {
    double totalWeight = 0;
    const std::vector<bool> &knapsackSolution = individual->getKnapsackSolution();

    std::vector<int> selectedItemsIndices;
    for(int i = 0; i < knapsackSolution.size(); i++){
        if(knapsackSolution[i]){
            totalWeight += allItems[i]->getWeight();
            selectedItemsIndices.push_back(i);
        }
    }

    if(totalWeight > capacityOfKnapsack){
        fixup(totalWeight, individual, selectedItemsIndices);
    }
}

void TTPProblem::fixup(double weight, Individual *individual, std::vector<int> selectedItemsIndices) {
    int selectedItemsLeft = selectedItemsIndices.size();
    while(weight > capacityOfKnapsack){
        std::uniform_int_distribution<int> randomItemDistribution(0, selectedItemsLeft-1);
        int itemIndex = randomItemDistribution(*randomGenerator);
        individual->flipKspGene(selectedItemsIndices[itemIndex]);
        weight -= allItems[selectedItemsIndices[itemIndex]]->getWeight();
        selectedItemsLeft--;
        std::swap(selectedItemsIndices[itemIndex], selectedItemsIndices[selectedItemsLeft]);
    }
}

void TTPProblem::setItemsInCities() {
    itemsInCities.clear();
    for(int i = 0; i < cities.size(); i++){
        itemsInCities[cities[i]->getIndex()] = std::vector<KnapsackItem*>();
    }

    for(int i = 0; i < allItems.size(); i++){
        itemsInCities[allItems[i]->getAssignedNodeIndex()].push_back(allItems[i]);
    }
}

std::pair<double, double> TTPProblem::getWeightAndProfitInCity(int cityIndex, const std::vector<bool> &knapsackSolution) {
    std::vector<KnapsackItem*>& items = itemsInCities[cityIndex];
    double profit = 0;
    double weight = 0;
    for(int i = 0; i < items.size(); i++){
        if(knapsackSolution[items[i]->getIndex()-1]){
            profit += items[i]->getProfit();
            weight += items[i]->getWeight();
        }
    }
    return { weight, profit };
}
