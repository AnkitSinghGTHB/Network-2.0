# Windows Dependencies Installation Guide for Network 2.0

## Prerequisites for Building Network 2.0 on Windows

### 1. Visual Studio

Install Visual Studio 2019 or later with C++ development tools:
- Download from: https://visualstudio.microsoft.com/downloads/
- During installation, select "Desktop development with C++"

### 2. CMake

Install CMake 3.15 or later:
- Download from: https://cmake.org/download/
- Add CMake to your system PATH during installation

### 3. WinPcap or Npcap

Choose one of these packet capture libraries:

#### Option A: Npcap (Recommended)
- Download from: https://npcap.com/#download
- Install with "WinPcap API-compatible Mode" enabled
- Development files are typically installed to `C:\Program Files\Npcap SDK`

#### Option B: WinPcap (Legacy)
- Download from: https://www.winpcap.org/install/
- Development files typically installed to `C:\WinPcap`

### 4. Build Instructions

```cmd
# Clone the repository
git clone <repository-url>
cd network-monitor

# Create build directory
mkdir build
cd build

# Configure with CMake (adjust paths as needed)
cmake .. -G "Visual Studio 16 2019" ^
    -DPCAP_INCLUDE_DIR="C:\Program Files\Npcap SDK\Include" ^
    -DWPCAP_LIBRARY="C:\Program Files\Npcap SDK\Lib\x64\wpcap.lib"

# Build
cmake --build . --config Release
```

### 5. Running the Application

The built executable will be in `build\Release\network2.0.exe`

**Important**: Run as Administrator to access network interfaces for packet capture.

```cmd
# Run as Administrator
network2.0.exe --help
```

### Troubleshooting

1. **CMake can't find WinPcap/Npcap**:
   - Verify installation paths
   - Use -DPCAP_INCLUDE_DIR and -DWPCAP_LIBRARY flags

2. **Access denied when capturing**:
   - Ensure running as Administrator
   - Check Windows Firewall settings

3. **No interfaces found**:
   - Verify Npcap/WinPcap service is running
   - Check Device Manager for network adapters

### Alternative: Using vcpkg

You can also use vcpkg to manage dependencies:

```cmd
# Install vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

# Install pcap
.\vcpkg install pcap:x64-windows

# Build with vcpkg toolchain
cmake .. -DCMAKE_TOOLCHAIN_FILE=<vcpkg-root>/scripts/buildsystems/vcpkg.cmake
```
