//
// Created by Szymon on 10/03/2019.
//

#ifndef GENETICALGORITHM_CITY_H
#define GENETICALGORITHM_CITY_H
#include <cmath>

class City {
public:
    City(int index, double x, double y);

    int getIndex() const;

    double getX() const;

    double getY() const;

    double distance(City *other);

private:
    int index;
    double x;
    double y;
};


#endif //GENETICALGORITHM_CITY_H
