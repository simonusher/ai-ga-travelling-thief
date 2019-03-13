//
// Created by Szymon on 10/03/2019.
//

#ifndef GENETICALGORITHM_ITEM_H
#define GENETICALGORITHM_ITEM_H


class KnapsackItem {
public:
    KnapsackItem(int index, double profit, double weight, int assignedNodeIndex);
    int getIndex() const;
    double getProfit() const;
    double getWeight() const;
    double getProfitWeightRatio() const;

    int getAssignedNodeIndex() const;

private:
    int index;
    double profit;
    double weight;
    int assignedNodeIndex;
};


#endif //GENETICALGORITHM_ITEM_H
