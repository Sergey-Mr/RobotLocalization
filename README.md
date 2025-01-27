# Robot Localization

## Prerequisites
- CMake 3.10+
- SFML 2.5+
- Python 3.8+
- matplotlib
- numpy
- scipy

## Installation

### Install Dependencies
```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install cmake libsfml-dev python3-dev python3-numpy python3-matplotlib python3-scipy

# Clone repository
git clone https://github.com/YOUR_USERNAME/robot-localization.git
cd robot-localization

# Build
chmod +x build.sh
./build.sh

# Run
./build/robot_simulator

cd build
sudo make install