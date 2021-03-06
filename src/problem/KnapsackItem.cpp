//
// Created by Szymon on 10/03/2019.
//

#include "../../include/GeneticAlgorithm/problem/KnapsackItem.h"


KnapsackItem::KnapsackItem(int index, double profit, double weight, int assignedNodeIndex)
        : index(index), profit(profit), weight(weight), assignedNodeIndex(assignedNodeIndex){}

int KnapsackItem::getIndex() const {
    return index;
}

double KnapsackItem::getProfit() const {
    return profit;
}

double KnapsackItem::getWeight() const {
    return weight;
}

double KnapsackItem::getProfitWeightRatio() const {
    return profit / weight;
}

int KnapsackItem::getAssignedNodeIndex() const {
    return assignedNodeIndex;
}
