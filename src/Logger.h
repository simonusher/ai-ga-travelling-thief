//
// Created by Szymon on 14.03.2019.
//

#ifndef GENETICALGORITHM_LOGGER_H
#define GENETICALGORITHM_LOGGER_H


#include <vector>
#include <ostream>
#include <fstream>
#include <iostream>

class Logger {
public:
    Logger(bool logToConsole, const std::string &logFileName);
    void close();
    Logger& operator<< (std::string& text);
    Logger& operator<< (int number);
    Logger& operator<< (double number);
    Logger& operator<< (const char* text);
private:
    void consoleLog(std::string &text);
    void consoleLog (int number);
    void consoleLog (double number);
    void consoleLog (const char* text);
    bool logToConsole;
    std::string logFileName;
    std::ofstream logFile;
};


#endif //GENETICALGORITHM_LOGGER_H
