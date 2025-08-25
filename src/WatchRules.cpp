#include "WatchRules.h"
#include "Utils.h"
#include <iostream>

void WatchRules::addWatchIP(const std::string& ip) {
    if (Utils::isValidIP(ip)) {
        watchedIPs.insert(ip);
        std::cout << Utils::Colors::GREEN << "Added IP watch: " << ip << Utils::Colors::RESET << std::endl;
    } else {
        std::cout << Utils::Colors::RED << "Invalid IP address: " << ip << Utils::Colors::RESET << std::endl;
    }
}

void WatchRules::addWatchPort(uint16_t port) {
    if (port > 0 && port <= 65535) {
        watchedPorts.insert(port);
        std::cout << Utils::Colors::GREEN << "Added port watch: " << port << Utils::Colors::RESET << std::endl;
    } else {
        std::cout << Utils::Colors::RED << "Invalid port number: " << port << Utils::Colors::RESET << std::endl;
    }
}

void WatchRules::removeWatchIP(const std::string& ip) {
    auto it = watchedIPs.find(ip);
    if (it != watchedIPs.end()) {
        watchedIPs.erase(it);
        std::cout << Utils::Colors::YELLOW << "Removed IP watch: " << ip << Utils::Colors::RESET << std::endl;
    }
}

void WatchRules::removeWatchPort(uint16_t port) {
    auto it = watchedPorts.find(port);
    if (it != watchedPorts.end()) {
        watchedPorts.erase(it);
        std::cout << Utils::Colors::YELLOW << "Removed port watch: " << port << Utils::Colors::RESET << std::endl;
    }
}

bool WatchRules::checkPacket(const PacketInfo& packet) {
    bool matched = false;
    if (watchedIPs.count(packet.sourceIP) || watchedIPs.count(packet.destIP)) {
        addAlert(AlertType::IP_WATCH, "Watched IP traffic detected: " + packet.sourceIP + " -> " + packet.destIP, packet);
        matched = true;
    }
    if (watchedPorts.count(packet.sourcePort) || watchedPorts.count(packet.destPort)) {
        addAlert(AlertType::PORT_WATCH, "Watched port traffic detected: " + std::to_string(packet.sourcePort) + " -> " + std::to_string(packet.destPort), packet);
        matched = true;
    }
    return matched;
}

void WatchRules::addAlert(AlertType type, const std::string& message, const PacketInfo& packet) {
    Alert alert;
    alert.type = type;
    alert.message = message;
    alert.packet = packet;
    alert.timestamp = std::chrono::system_clock::now();
    alerts.emplace_back(std::move(alert));
    Utils::playBeep();
}

const std::vector<Alert>& WatchRules::getAlerts() const {
    return alerts;
}

const std::unordered_set<std::string>& WatchRules::getWatchedIPs() const {
    return watchedIPs;
}

const std::unordered_set<uint16_t>& WatchRules::getWatchedPorts() const {
    return watchedPorts;
}

void WatchRules::clearAlerts() {
    alerts.clear();
}

void WatchRules::printWatchedItems() const {
    std::cout << Utils::Colors::BOLD << "\n=== Watch Rules ===" << Utils::Colors::RESET << std::endl;

    if (!watchedIPs.empty()) {
        std::cout << Utils::Colors::CYAN << "Watched IPs:" << Utils::Colors::RESET;
        for (const auto& ip : watchedIPs) {
            std::cout << " " << ip;
        }
        std::cout << std::endl;
    }

    if (!watchedPorts.empty()) {
        std::cout << Utils::Colors::CYAN << "Watched Ports:" << Utils::Colors::RESET;
        for (const auto& port : watchedPorts) {
            std::cout << " " << port;
        }
        std::cout << std::endl;
    }

    if (watchedIPs.empty() && watchedPorts.empty()) {
        std::cout << Utils::Colors::YELLOW << "No watch rules configured" << Utils::Colors::RESET << std::endl;
    }
    std::cout << std::endl;
}
