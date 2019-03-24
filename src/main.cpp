#include <iostream>
#include "../include/GeneticAlgorithm/problem/Individual.h"
#include "../include/GeneticAlgorithm/problem/TTPProblem.h"
#include "../include/GeneticAlgorithm/optimizers/GeneticAlgorithm.h"
#include "../include/GeneticAlgorithm/optimizers/RandomSearch.h"
#include "../include/GeneticAlgorithm/optimizers/HillClimber.h"
#include "../include/GeneticAlgorithm/operators/TournamentSelector.h"
#include "../include/GeneticAlgorithm/operators/AllGeneRandomSwapMutator.h"
#include "../include/GeneticAlgorithm/operators/RandomSwapMutator.h"
#include "../include/GeneticAlgorithm/operators/RouletteSelector.h"
#include "../include/GeneticAlgorithm/operators/InvertMutator.h"

#include <ctime>
using namespace std;

void runHillClimberTests(std::vector<std::string> fileNames, int numberOfTests, int numberOfIndividuals){
    for(int j = 0; j < fileNames.size(); j++){
        std::string problemName(fileNames[j]);
        std::string fileName(fileNames[j] + ".ttp");
        std::random_device randomDevice;
        for(int i = 0; i < numberOfTests; i++){
            std::mt19937 randomGenerator(randomDevice());
            TTPProblem problem(&randomGenerator);
            Logger logger(true, "results/hc/" + problemName + "/" + std::to_string(i) + ".csv");

            problem.initialize(fileName);

            clock_t begin = clock();
            HillClimber hillClimber(&problem, &logger);
            hillClimber.hillClimb(numberOfIndividuals);
            clock_t end = clock();
            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            std::cout << "elapsed secs: " << elapsed_secs << std::endl;
            std::cout << problem.getFitnessFunctionEvaluations();
            logger.close();
        }
    }
}


void runGaTests(){
//    std::vector<std::string> problemNames {"easy_0", "easy_1", "medium_0", "medium_1", "hard_0"};
//    std::vector<std::string> problemNames {"easy_0"};
//    std::vector<std::string> problemNames {"hard_0"};
    std::vector<std::string> problemNames {"trivial_0"};
    for(int j = 0; j < problemNames.size(); j++){
        std::string problemName(problemNames[j]);
        std::string filename(problemName + ".ttp");
        int iterations = 300;
        int popSize = 100;
        double crossProb = 0.8;
        int tournamentSize = 10;
//        double individualMutProb = 0.05;
        double geneMutProb = 0.015;
        double individualMutProb = 0.6;

        for(int i = 0; i < 10; i++){
            std::random_device randomDevice;
            std::mt19937 randomGenerator(randomDevice());
            TTPProblem problem(&randomGenerator);
            problem.initialize(filename);

            Logger logger(true, "i" + std::to_string(iterations) + "p"
                                + std::to_string(popSize) + "c" + std::to_string(crossProb) + "m" + std::to_string(geneMutProb) + "t" + std::to_string(tournamentSize)
                                + "_" + std::to_string(i) + ".csv");


            TournamentSelector selector(&problem, tournamentSize, popSize, &randomGenerator);
//            RouletteSelector selector(&problem, &randomGenerator);

//            AllGeneRandomSwapMutator mutator(individualMutProb, &randomGenerator);
//            RandomSwapMutator mutator(individualMutProb, &randomGenerator);
            InvertMutator mutator(geneMutProb, individualMutProb, &randomGenerator);

            clock_t begin = clock();

            GeneticAlgorithm ga(popSize, crossProb, &problem, &logger, &randomGenerator, &selector, &mutator);
            ga.run(iterations);

            clock_t end = clock();
            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            std::cout << "elapsed secs: " << elapsed_secs << std::endl;
            std::cout << problem.getFitnessFunctionEvaluations();
            logger.close();
        }
    }
}

int main() {
//    std::vector<std::string> problemNames {"easy_0", "easy_1", "medium_0", "medium_1", "hard_0"};
//    runHillClimberTests(problemNames, 10, 1000);
//    runGreedyTests(problemNames);
//    runRandomSearchTests(problemNames, 10, 10000);
//    TTPProblem problem;
//    std::string test("hard_0.ttp");
//    problem.initialize(test, ProfitWeightRatio);
//    std::vector<int> tspSolution {19, 20, 21, 22, 24, 23, 66, 67, 68, 69, 70, 71, 89, 88, 72, 90, 91, 104, 105, 106, 107, 108, 109, 146, 144, 147, 148, 145, 185, 190, 191, 184, 192, 183, 182, 181, 180, 179, 178, 177, 159, 158, 157, 156, 155, 154, 153, 151, 152, 143, 150, 142, 141, 140, 139, 138, 137, 136, 135, 134, 162, 163, 164, 165, 167, 166, 169, 170, 168, 171, 172, 174, 173, 204, 203, 202, 201, 200, 199, 198, 197, 196, 195, 194, 193, 221, 220, 219, 218, 217, 216, 215, 214, 213, 212, 211, 210, 250, 251, 209, 253, 252, 249, 248, 247, 246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 236, 235, 234, 233, 222, 223, 224, 273, 274, 275, 276, 277, 278, 279, 294, 295, 296, 297, 298, 299, 300, 333, 334, 335, 336, 337, 338, 339, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 378, 385, 386, 387, 388, 401, 400, 416, 415, 419, 420, 421, 414, 389, 390, 380, 379, 377, 376, 345, 346, 348, 349, 347, 350, 351, 353, 354, 352, 355, 356, 358, 359, 357, 292, 293, 291, 290, 289, 288, 287, 286, 285, 280, 232, 231, 225, 188, 189, 187, 230, 281, 282, 229, 228, 283, 284, 344, 343, 342, 341, 373, 372, 371, 383, 382, 384, 394, 395, 393, 398, 397, 396, 399, 392, 391, 381, 375, 374, 340, 226, 227, 186, 149, 83, 84, 85, 53, 54, 55, 56, 82, 81, 80, 79, 57, 58, 78, 77, 87, 86, 59, 60, 61, 76, 75, 62, 32, 31, 30, 29, 27, 26, 28, 63, 73, 74, 64, 25, 65, 102, 92, 93, 94, 100, 101, 123, 125, 126, 124, 127, 129, 130, 131, 132, 133, 128, 99, 98, 97, 96, 95, 120, 117, 115, 103, 114, 113, 116, 118, 119, 121, 122, 160, 161, 175, 176, 205, 206, 207, 208, 255, 254, 316, 315, 314, 313, 312, 311, 310, 309, 308, 307, 264, 263, 262, 261, 260, 259, 258, 257, 256, 318, 317, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 331, 330, 303, 302, 304, 305, 306, 267, 266, 265, 268, 269, 270, 271, 272, 301, 332, 370, 110, 111, 112, 18, 33, 34, 35, 36, 37, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 52, 51, 50, 48, 47, 49, 46, 45, 43, 41, 40, 39, 38, 42, 44, 1, 13, 14, 15, 16, 17, 406, 407, 413, 412, 423, 422, 427, 430, 424, 425, 410, 411, 409, 408, 403, 426, 433, 432, 434, 438, 437, 436, 435, 439, 402, 404, 405, 417, 418, 428, 429, 431};
//    Individual i(tspSolution);
//    std::cout << problem.evaluate(&i);

    runGaTests();
}