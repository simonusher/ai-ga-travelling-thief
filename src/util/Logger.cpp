//
// Created by Szymon on 14.03.2019.
//

#include "../../include/GeneticAlgorithm/util/Logger.h"

Logger::Logger(bool logToConsole, const std::string &logFileName) : logToConsole(logToConsole),
                                                                    logFileName(logFileName) {
    this->logFile.open(logFileName);
}

void Logger::close() {
    this->logFile.close();
}

Logger &Logger::operator<<(std::string &text) {
    logFile << text;
    consoleLog(text);
    return *this;
}

Logger &Logger::operator<<(double number) {
    logFile << number;
    consoleLog(number);
    return *this;
}

Logger &Logger::operator<<(const char *text) {
    logFile << text;
    consoleLog(text);
    return *this;
}

void Logger::consoleLog(std::string &text) {
    if(logToConsole){
        std::cout << text;
    }
}

void Logger::consoleLog(int number) {
    if(logToConsole){
        std::cout << number;
    }
}

void Logger::consoleLog(double number) {
    if(logToConsole){
        std::cout << number;
    }
}

void Logger::consoleLog(const char *text) {
    if(logToConsole){
        std::cout << text;
    }
}
