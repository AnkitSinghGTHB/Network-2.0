#ifndef PACKET_CAPTURE_H
#define PACKET_CAPTURE_H

#include "PacketTypes.h"
#include <string>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <pcap.h>
#else
#include <pcap/pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#endif

class PacketCapture {
private:
    pcap_t* handle;
    std::string interface;
    bool isCapturing;
    
    static void packetHandler(u_char* userData, const struct pcap_pkthdr* pkthdr, const u_char* packet);
    PacketInfo parsePacket(const struct pcap_pkthdr* pkthdr, const u_char* packet);
    std::string ipToString(uint32_t ip);
    
public:
    PacketCapture();
    ~PacketCapture();
    
    bool initialize(const std::string& interface = "");
    bool startCapture();
    void stopCapture();
    std::vector<std::string> getAvailableInterfaces();
    
    void (*onPacketReceived)(const PacketInfo& packet);
    
    bool isActive() const { return isCapturing; }
    const std::string& getInterface() const { return interface; }
};

#endif
