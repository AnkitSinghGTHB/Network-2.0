#ifndef ALERT_H
#define ALERT_H

#include <string>
#include "PacketTypes.h"

enum class AlertType {
    INFO,
    WARNING,
    CRITICAL
};

class Alert {
private:
    AlertType type;
    std::string message;
    PacketInfo packet;

public:
    Alert(AlertType t, const std::string& msg, const PacketInfo& p)
        : type(t), message(msg), packet(p) {}

    AlertType getType() const { return type; }
    const std::string& getMessage() const { return message; }
    const PacketInfo& getPacket() const { return packet; }
};

#endif
