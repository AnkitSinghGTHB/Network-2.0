cmake_minimum_required(VERSION 3.15)
project(Network2.0 VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_definitions(-D_WIN32_WINNT=0x0601)
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    add_definitions(-DWPCAP)
    add_definitions(-DHAVE_REMOTE)
endif()

if(WIN32)
    find_library(WPCAP_LIBRARY wpcap HINTS 
        "${CMAKE_SOURCE_DIR}/npcap-sdk/Lib/x64" 
        "${CMAKE_SOURCE_DIR}/npcap-sdk/Lib"
        "C:/WinPcap/Lib/x64" 
        "C:/WinPcap/Lib")
    find_path(PCAP_INCLUDE_DIR pcap.h HINTS 
        "${CMAKE_SOURCE_DIR}/npcap-sdk/Include"
        "C:/WinPcap/Include")
    set(PCAP_LIBRARIES ${WPCAP_LIBRARY} ws2_32)
else()
    find_library(PCAP_LIBRARY pcap)
    find_path(PCAP_INCLUDE_DIR pcap/pcap.h)
    set(PCAP_LIBRARIES ${PCAP_LIBRARY})
endif()

if(WIN32)
    if(NOT WPCAP_LIBRARY OR NOT PCAP_INCLUDE_DIR)
        message(FATAL_ERROR "libpcap not found. Please install libpcap development package.")
    endif()
else()
    if(NOT PCAP_LIBRARY OR NOT PCAP_INCLUDE_DIR)
        message(FATAL_ERROR "libpcap not found. Please install libpcap development package.")
    endif()
endif()

include_directories(${PCAP_INCLUDE_DIR})
include_directories(src)

set(SOURCES
    src/main.cpp
    src/PacketCapture.cpp
    src/AnomalyDetector.cpp
    src/NetworkStats.cpp
    src/WatchRules.cpp
    src/Logger.cpp
    src/Utils.cpp
)

set(HEADERS
    src/PacketCapture.h
    src/AnomalyDetector.h
    src/NetworkStats.h
    src/WatchRules.h
    src/Logger.h
    src/Utils.h
    src/PacketTypes.h
)

add_executable(network2.0 ${SOURCES} ${HEADERS})

target_link_libraries(network2.0 ${PCAP_LIBRARIES})

if(WIN32)
    target_link_libraries(network2.0 ws2_32 iphlpapi)
endif()

if(MSVC)
    target_compile_options(network2.0 PRIVATE /W4)
else()
    target_compile_options(network2.0 PRIVATE -Wall -Wextra -pedantic)
endif()

install(TARGETS network2.0 DESTINATION bin)
