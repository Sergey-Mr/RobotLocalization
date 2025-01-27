cmake_minimum_required(VERSION 3.10)
project(RobotLocalization)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Copy Python script to build directory
configure_file(${CMAKE_SOURCE_DIR}/scripts/3dPlotting.py
               ${CMAKE_BINARY_DIR}/3dPlotting.py COPYONLY)

# Add source files
add_executable(robot_simulator
    src/main.cpp
    src/Robot.cpp
    src/Map.cpp
    src/Sensor.cpp
)

# Include directories
target_include_directories(robot_simulator PRIVATE include)

# Link libraries
target_link_libraries(robot_simulator
    PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

# Install targets
install(TARGETS robot_simulator DESTINATION bin)
install(FILES scripts/3dPlotting.py DESTINATION bin)