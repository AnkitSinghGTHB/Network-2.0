#include "Logger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

std::string Logger::getTimestamp() {
    std::time_t now = std::time(nullptr);
    std::tm tm_struct{};
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm_struct, &now);
#else
    localtime_r(&now, &tm_struct);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm_struct, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void Logger::log(const std::string& message) {
    std::string timestamp = getTimestamp();
    std::ofstream logFile("network.log", std::ios::app);

    if (logFile.is_open()) {
        logFile << "[" << timestamp << "] " << message << std::endl;
        logFile.close();
    }

    std::cout << "[" << timestamp << "] " << message << std::endl;
}
