@echo off
echo Building TicTacToe with SFML...

REM Create build directory if it doesn't exist
if not exist build mkdir build

REM Change to build directory
cd build

REM Run CMake to generate build files
cmake .. -G "Visual Studio 17 2022"

REM Build the project
cmake --build . --config Release

echo.
echo Build complete!
echo To run the game, execute: build\Release\TicTacToe.exe
pause
