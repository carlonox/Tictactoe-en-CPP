#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <vector>
#include <string>

const int BOARD_SIZE = 3;
const char EMPTY_CELL = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

class GameModel {
private:
    char board[BOARD_SIZE][BOARD_SIZE];
    char currentPlayer;
    bool gameEnded;
    char winner;

public:
    GameModel();
    
    // Game state methods
    void resetGame();
    char getCurrentPlayer() const;
    bool isGameEnded() const;
    char getWinner() const;
    
    // Board methods
    char getCell(int row, int col) const;
    bool isCellEmpty(int row, int col) const;
    bool placePiece(int row, int col, char player);
    
    // Game logic methods
    bool checkWin(char player) const;
    bool checkDraw() const;
    char getOpponent(char player) const;
    
    // AI methods (from original implementation)
    void getCPUMove(int& row, int& col);
    
private:
    // Helper methods for AI
    void cloneBoard(char destination[BOARD_SIZE][BOARD_SIZE]) const;
    int countUp(int row, int col, char player) const;
    int countRight(int row, int col, char player) const;
    int countUpRight(int row, int col, char player) const;
    int countDownRight(int row, int col, char player) const;
    int getMaxCount(char player) const;
    void getWinningMove(char player, int& row, int& col);
    void getBestMove(char player, int& row, int& col, int& count);
    
    // Utility methods
    int getRandomInRange(int min, int max) const;
    void getRandomMove(int& row, int& col);
};

#endif // GAMEMODEL_H
