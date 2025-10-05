cmake_minimum_required(VERSION 3.10)
project(TicTacToe)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add include directories
include_directories(include)

# Add executable
add_executable(TicTacToe
    src/main.cpp
    src/GameModel.cpp
    src/ChatModel.cpp
    src/GameView.cpp
    src/ChatView.cpp
    src/Controller.cpp
)

# Link SFML
target_link_libraries(TicTacToe sfml-graphics sfml-window sfml-system)

# Copy resources if needed
# configure_file(resources/arial.ttf ${CMAKE_BINARY_DIR}/arial.ttf COPYONLY)
