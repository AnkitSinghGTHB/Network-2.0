#!/bin/bash


echo "=== Installing Network 2.0 Dependencies (Ubuntu/Debian) ==="

sudo apt-get update

echo "Installing build tools..."
sudo apt-get install -y \
    build-essential \
    cmake \
    git

echo "Installing libpcap development files..."
sudo apt-get install -y libpcap-dev

echo "Installing additional network tools (optional)..."
sudo apt-get install -y \
    tcpdump \
    nmap \
    netcat-openbsd

echo ""
echo "=== Dependencies Installed Successfully ==="
echo ""
echo "You can now build the project with:"
echo "  ./build.sh"
echo ""
echo "Or manually:"
echo "  mkdir build && cd build"
echo "  cmake .."
echo "  make"
