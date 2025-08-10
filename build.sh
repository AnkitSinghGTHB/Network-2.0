#!/bin/bash

set -e

echo "=== Building Network 2.0 ==="

echo "Checking dependencies..."

if ! command -v cmake &> /dev/null; then
    echo "Error: cmake not found. Please install cmake."
    exit 1
fi

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    if ! pkg-config --exists libpcap; then
        echo "Error: libpcap not found. Install with:"
        echo "  Ubuntu/Debian: sudo apt-get install libpcap-dev"
        echo "  RHEL/CentOS:   sudo yum install libpcap-devel"
        echo "  Fedora:        sudo dnf install libpcap-devel"
        exit 1
    fi
fi

if [ ! -d "build" ]; then
    mkdir build
fi

cd build

echo "Configuring with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release

echo "Building..."
make -j$(nproc 2>/dev/null || echo 4)

echo ""
echo "=== Build Complete ==="
echo "Executable: $(pwd)/network2.0"
echo ""
echo "To run with default settings:"
echo "  sudo ./network2.0"
echo ""
echo "To see all options:"
echo "  ./network2.0 --help"
