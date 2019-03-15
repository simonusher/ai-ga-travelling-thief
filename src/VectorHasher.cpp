//
// Created by Szymon on 24.11.2018.
//
#include "../include/GeneticAlgorithm/VectorHasher.h"

std::size_t VectorHasher::operator()(std::vector<int> const &vec) const {
    std::size_t seed = vec.size();
    for(const int& i : vec) {
        seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}