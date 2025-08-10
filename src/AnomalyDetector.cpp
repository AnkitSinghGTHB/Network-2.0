#include "AnomalyDetector.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <string>

bool AnomalyDetector::analyzePacket(PacketInfo& packet) {
    cleanupOldEntries();

    bool isAnomalous = false;
    std::string reason;

    if (isPacketBurst(packet.sourceIP)) {
        isAnomalous = true;
        reason =+ "Packet burst detected; ";
    }

    if (isPortScan(packet)) {
        isAnomalous = true;
        reason =+ "Port scan detected; ";
    }

    if (packet.protocol == "TCP" && packet.packetSize < 100) {
        if (isFailedConnection(packet)) {
            isAnomalous = true;
            reason =+ "Multiple failed connections; ";
        }
    }

    if (isAnomalous) {
        packet.isAnomaly = true;
        packet.anomalyReason = reason; 
    }

    return isAnomalous;
}

bool AnomalyDetector::isPacketBurst(const std::string& sourceIP) {
    auto& tracker = burstTrackers[sourceIP];
    auto now = std::chrono::system_clock::now();

    tracker.recentPackets.push(now);

    while (!tracker.recentPackets.empty()) {
        auto packetTime = tracker.recentPackets.front();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - packetTime).count();

        if (elapsed > BurstTracker::BURST_WINDOW_SECONDS) {
            tracker.recentPackets.pop();
        } else {
            break;
        }
    }

    return tracker.recentPackets.size() > BurstTracker::BURST_THRESHOLD;
}

bool AnomalyDetector::isPortScan(const PacketInfo& packet) {
    if (packet.protocol != "TCP") return false;

    auto& tracker = scanTrackers[packet.sourceIP];
    auto now = std::chrono::system_clock::now();

    if (tracker.scannedPorts.empty()) {
        tracker.firstScanTime = now;
    } else {
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - tracker.firstScanTime).count();

        if (elapsed > ScanTracker::SCAN_WINDOW_SECONDS) {
            tracker.scannedPorts.clear();
            tracker.firstScanTime = now;
        }
    }

    tracker.scannedPorts.insert(packet.destPort);

    return tracker.scannedPorts.size() > ScanTracker::SCAN_THRESHOLD;
}

bool AnomalyDetector::isFailedConnection(const PacketInfo& packet) {
    auto& tracker = connectionTrackers[packet.sourceIP];
    auto now = std::chrono::system_clock::now();

    if (tracker.failedAttempts == 0) {
        tracker.firstFailTime = now;
    } else {
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - tracker.firstFailTime).count();

        if (elapsed > ConnectionTracker::FAILED_WINDOW_SECONDS) {
            tracker.failedAttempts = 0;
            tracker.firstFailTime = now;
        }
    }

    tracker.failedAttempts++;

    return tracker.failedAttempts > ConnectionTracker::FAILED_THRESHOLD;
}

void AnomalyDetector::cleanupOldEntries() {
    auto now = std::chrono::system_clock::now();

    for (auto it = burstTrackers.begin(); it != burstTrackers.end();) {
        if (it->second.recentPackets.empty()) {
            it = burstTrackers.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = scanTrackers.begin(); it != scanTrackers.end();) {
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - it->second.firstScanTime).count();

        if (elapsed > ScanTracker::SCAN_WINDOW_SECONDS && it->second.scannedPorts.empty()) {
            it = scanTrackers.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = connectionTrackers.begin(); it != connectionTrackers.end();) {
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - it->second.firstFailTime).count();

        if (elapsed > ConnectionTracker::FAILED_WINDOW_SECONDS && it->second.failedAttempts == 0) {
            it = connectionTrackers.erase(it);
        } else {
            ++it;
        }
    }
}

void AnomalyDetector::reset() {
    burstTrackers.clear();
    scanTrackers.clear();
    connectionTrackers.clear();
}

void AnomalyDetector::printStats() const {
    std::cout << Utils::Colors::BOLD << "\n=== Anomaly Detection Stats ===" << Utils::Colors::RESET << std::endl;
    std::cout << "Active burst trackers: " << burstTrackers.size() << std::endl;
    std::cout << "Active scan trackers: " << scanTrackers.size() << std::endl;
    std::cout << "Active connection trackers: " << connectionTrackers.size() << std::endl;
}
