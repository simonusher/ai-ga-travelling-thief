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
#include "../include/GeneticAlgorithm/optimizers/GreedyTTP.h"

#include <ctime>
using namespace std;

void runHillClimberTests(std::vector<std::string> fileNames, int numberOfTests, int numberOfIndividuals){
    for(int j = 0; j < fileNames.size(); j++){
        std::string problemName(fileNames[j]);
        std::string fileName(fileNames[j] + ".ttp");
        for(int i = 0; i < numberOfTests; i++){
            TTPProblem problem;
            Logger logger(true, "results/hc/" + problemName + "/" + std::to_string(i) + ".csv");

            problem.initialize(fileName, ProfitWeightRatio);

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

void runRandomSearchTests(std::vector<std::string> fileNames, int numberOfTests, int numberOfIndividuals){
    for(int j = 0; j < fileNames.size(); j++){
        std::string problemName(fileNames[j]);
        std::string fileName(fileNames[j] + ".ttp");
        for(int i = 0; i < numberOfTests; i++){
            TTPProblem problem;
            Logger logger(true, "results/rs/" + problemName + "/" + std::to_string(i) + ".csv");

            problem.initialize(fileName, ProfitWeightRatio);

            clock_t begin = clock();
            RandomSearch randomSearch(&problem, &logger);
            randomSearch.search(numberOfIndividuals);
            clock_t end = clock();
            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            std::cout << "elapsed secs: " << elapsed_secs << std::endl;
            std::cout << problem.getFitnessFunctionEvaluations();
            logger.close();
        }
    }
}

void runGreedyTests(std::vector<std::string> fileNames){
    for(int j = 0; j < fileNames.size(); j++){
        std::string problemName(fileNames[j]);
        std::string fileName(fileNames[j] + ".ttp");
            TTPProblem problem;
            Logger logger(true, "results/greedy/" + problemName + ".csv");
            problem.initialize(fileName, ProfitWeightRatio);

            clock_t begin = clock();
            GreedyTTP greedyTTP(&problem, &logger);
            greedyTTP.solve();
            clock_t end = clock();

            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            std::cout << "elapsed secs: " << elapsed_secs << std::endl;
            std::cout << problem.getFitnessFunctionEvaluations();
            logger.close();
    }
}

void runGaTests(){
    std::vector<std::string> problemNames {"easy_0", "easy_1", "medium_0", "medium_1", "hard_0"};
    for(int j = 0; j < problemNames.size(); j++){
        std::string problemName(problemNames[j]);
        std::string filename(problemName + ".ttp");
        int iterations = 300;
        int popSize = 1000;
        double crossProb = 0.8;
        int tournamentSize = 50;
        double mutProb = 0.005;
//        double mutProb = 0.3;

        for(int i = 0; i < 10; i++){
            TTPProblem problem;
            std::random_device randomDevice;
            std::mt19937 randomGenerator(randomDevice());

            Logger logger(true, "results/" + problemName + "/i" + std::to_string(iterations) + "p"
                                + std::to_string(popSize) + "c" + std::to_string(crossProb) + "m" + std::to_string(mutProb) + "t" + std::to_string(tournamentSize)
                                + "_" + std::to_string(i) + ".csv");

            problem.initialize(filename, ProfitWeightRatio);

            TournamentSelector selector(&problem, tournamentSize, popSize, &randomGenerator);
//            RouletteSelector selector(&problem, &randomGenerator);

            AllGeneRandomSwapMutator mutator(mutProb, &randomGenerator);
//            RandomSwapMutator mutator(mutProb, &randomGenerator);

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
    std::vector<std::string> problemNames {"easy_0", "easy_1", "medium_0", "medium_1", "hard_0"};
//    runHillClimberTests(problemNames, 10, 1000);
//    runGreedyTests(problemNames);
    runRandomSearchTests(problemNames, 10, 10000);
}