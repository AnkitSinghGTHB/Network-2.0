#ifndef WATCH_RULES_H
#define WATCH_RULES_H

#include "PacketTypes.h"
#include "Alert.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <cstdint>

class WatchRules {
private:
    std::unordered_set<std::string> watchedIPs;
    std::unordered_set<uint16_t> watchedPorts;
    std::vector<Alert> alerts;

public:
    WatchRules() = default;

    void addWatchIP(const std::string& ip);
    void addWatchPort(uint16_t port);
    void removeWatchIP(const std::string& ip);
    void removeWatchPort(uint16_t port);

    bool checkPacket(const PacketInfo& packet);
    void addAlert(AlertType type, const std::string& message, const PacketInfo& packet);

    const std::vector<Alert>& getAlerts() const;
    const std::unordered_set<std::string>& getWatchedIPs() const;
    const std::unordered_set<uint16_t>& getWatchedPorts() const;

    void clearAlerts();
    void printWatchedItems() const;
};

#endif 
