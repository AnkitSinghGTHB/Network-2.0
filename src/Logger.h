#ifndef LOGGER_H
#define LOGGER_H

#include "PacketTypes.h"
#include "Alert.h"
#include <string>
#include <fstream>
#include <vector>

class Logger {
private:
    std::string csvFilename;
    std::ofstream csvFile;
    bool isLoggingEnabled;
    
    void writeCSVHeader();
    
public:
    Logger();
    ~Logger();
    
    bool enableLogging(const std::string& filename);
    void disableLogging();
    void logPacket(const PacketInfo& packet);
    void logAlert(const Alert& alert);
    void exportToCSV(const std::vector<PacketInfo>& packets, const std::string& filename);
    
    bool isEnabled() const { return isLoggingEnabled; }
    const std::string& getFilename() const { return csvFilename; }
};

#endif
