# Contributing to Network 2.0 🚀

Thank you for being part of the DSCWoC '26 mission! We welcome contributions to enhance our network monitoring capabilities.

## 🛠️ Environment Setup
Since this project uses `libpcap`, ensure you have the following installed:
- **Linux:** `sudo apt-get install libpcap-dev cmake build-essential`
- **Windows:** Install **Npcap SDK** and CMake.

## 🚦 Contribution Workflow
1. **Claim an Issue:** Comment on an existing issue or open a new one to discuss your idea.
2. **Fork & Clone:** Create your own copy of the repo.
3. **Branching:** Use descriptive names: `feat/anomaly-logic` or `fix/pcap-memory-leak`.
4. **Local Testing:** Ensure the project compiles with `cmake .. && make`. **Note:** You must run the binary with `sudo` (Linux) or Administrator (Windows) to capture packets.
5. **Submit PR:** Fill out the PR template completely.

## 📜 Coding Standards
- Follow modern C++17/20 standards.
- Use meaningful variable names (e.g., `packetSource` instead of `ps`).
- Ensure all new features are documented in the README.
