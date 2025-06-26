#pragma once
#include <string>
#include <mutex>
#include <fstream>

class Logger {
public:
    static Logger& getInstance();
    void log(const std::string& message);

private:
    Logger();
    std::mutex logMutex;
    std::ofstream logFile;
};