#ifndef NETWORK_STATS_H
#define NETWORK_STATS_H

#include "PacketTypes.h"
#include <unordered_map>
#include <string>
#include <chrono>

class NetworkStats {
private:
    uint64_t totalPackets;
    uint64_t totalBytes;
    uint64_t anomalousPackets;
    
    std::unordered_map<std::string, uint64_t> protocolCounts;
    std::unordered_map<std::string, uint64_t> ipCounts;
    
    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point lastPacketTime;
    
public:
    NetworkStats();
    
    void recordPacket(const PacketInfo& packet);
    void reset();
    void printStats() const;
    void printLiveTable(const PacketInfo* recentPackets, size_t count) const;
    
    uint64_t getTotalPackets() const { return totalPackets; }
    uint64_t getTotalBytes() const { return totalBytes; }
    uint64_t getAnomalousPackets() const { return anomalousPackets; }
    double getPacketsPerSecond() const;
};

#endif
