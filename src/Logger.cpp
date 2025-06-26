#include "Logger.hpp"
#include <chrono>
#include <ctime>

Logger::Logger() {
    logFile.open("logs/server.log", std::ios::app);
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    logFile << "[" << std::ctime(&now) << "] " << message << std::endl;
}