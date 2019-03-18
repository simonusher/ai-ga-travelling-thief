//
// Created by Szymon on 24.11.2018.
//

#ifndef GENETICALGORITHM_VECTORHASHER_H
#define GENETICALGORITHM_VECTORHASHER_H

#include <vector>
#include <cstddef>

class VectorHasher {
public:
    std::size_t operator()(std::vector<int> const& vec) const;
};

#endif //GENETICALGORITHM_VECTORHASHER_H