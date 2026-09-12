# Tic-Tac-Toe with a Strategic CPU

> Implementation of the classic Tic-Tac-Toe game (known as "Triqui" or "Tres en Raya" in Spanish) in **C++**, with a **CPU that makes strategic decisions** to win, block, or maximize its score. Includes a dice system to decide who starts. A good exercise for learning game logic and decision-making algorithms.

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Console](https://img.shields.io/badge/Console-Text-333333?style=for-the-badge)
![MIT License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

![Console game screenshot](https://via.placeholder.com/600x300/2c3e50/ffffff?text=Tic-Tac-Toe+C%2B%2B+Console)  
*(Replace this with a real screenshot of your game running)*

---

## Description

This project is an improved version of the Tic-Tac-Toe game, where:
- The human player plays with **`X`**.
- The CPU plays with **`O`**.
- **Dice system:** before starting, virtual dice are rolled to randomly decide who goes first.
- The CPU follows a **6-tier strategy**:
  1. Win if it can.
  2. Block the player if they are about to win.
  3. Take the opponent's best move (highest score).
  4. Take its own best move.
  5. Choose the top-left corner (0,0) if it is free.
  6. If everything else fails, choose randomly.

**Recent improvements:**
- **Intuitive coordinate system**: Cartesian coordinates, (1,1) = bottom-left corner
- **Fixed turn handling**: the player must enter valid coordinates before the turn passes
- **Input validation**: detection and handling of invalid input
- **Bug fixes**: resolved recursion problems and infinite loops

Ideal for learning programming logic, matrices, recursion, and decision-making in C++.

---

## Technologies Used

- **Language**: C++ (standard)
- **Compiler**: GCC, Clang, MSVC (any compatible one)
- **Standard libraries**: `<iostream>`, `<vector>`, `<ctime>`, `<cstdlib>`, `<cstdio>`
- **Platform**: Console (cross-platform: Windows, Linux, macOS)

---

## How to Compile and Run

### Requirements
- A C++ compiler (g++, clang++, etc.)
- Operating system: Windows, Linux, or macOS

### Steps

1. Clone the repository (or copy the `.cpp` file):
   ```bash
   git clone https://github.com/carlonox/Tictactoe-en-CPP.git
   cd Tictactoe-en-CPP
   ```

2. Compile the program:
   ```bash
   g++ -o tictactoe Cpp-Tictactoe.cpp
   ```

3. Run the game:
   ```bash
   ./tictactoe
   ```

### How to play
- The game displays a board with Cartesian coordinates
- Enter the coordinates as `x,y` where:
  - (1,1) is the bottom-left corner
  - (3,3) is the top-right corner
- The dice system determines who starts
- The CPU implements an advanced 6-tier strategy

---

## Implemented Improvements

### Version 2.0 - Cartesian Coordinate System
- Implementation of intuitive Cartesian coordinates
- Fixed turn handling
- Improved validation of user input
- Fixed recursion bugs

### Version 1.0 - Base
- Working game with a strategic CPU
- Dice system to determine who starts
- Basic console interface

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## Contributing

Contributions are welcome. Please open an issue first to discuss what you would like to change.

---

## Contact

Carlos Javier Cuervo Baracaldo - [@carlonox](https://github.com/carlonox)

Project link: [https://github.com/carlonox/Tictactoe-en-CPP](https://github.com/carlonox/Tictactoe-en-CPP)
