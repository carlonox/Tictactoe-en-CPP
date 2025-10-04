#include "../include/GameModel.h"
#include <cstdlib>
#include <ctime>
#include <cstring>

GameModel::GameModel() : currentPlayer(PLAYER_X), gameEnded(false), winner(EMPTY_CELL) {
    resetGame();
}

void GameModel::resetGame() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY_CELL;
        }
    }
    currentPlayer = PLAYER_X;
    gameEnded = false;
    winner = EMPTY_CELL;
}

char GameModel::getCurrentPlayer() const {
    return currentPlayer;
}

bool GameModel::isGameEnded() const {
    return gameEnded;
}

char GameModel::getWinner() const {
    return winner;
}

char GameModel::getCell(int row, int col) const {
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
        return board[row][col];
    }
    return EMPTY_CELL;
}

bool GameModel::isCellEmpty(int row, int col) const {
    return getCell(row, col) == EMPTY_CELL;
}

bool GameModel::placePiece(int row, int col, char player) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return false;
    }
    
    if (player != PLAYER_X && player != PLAYER_O) {
        return false;
    }
    
    if (!isCellEmpty(row, col)) {
        return false;
    }
    
    board[row][col] = player;
    
    // Check for win or draw
    if (checkWin(player)) {
        gameEnded = true;
        winner = player;
    } else if (checkDraw()) {
        gameEnded = true;
        winner = EMPTY_CELL; // No winner in draw
    } else {
        // Switch player
        currentPlayer = getOpponent(player);
    }
    
    return true;
}

bool GameModel::checkWin(char player) const {
    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
    }
    
    // Check columns
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player) {
            return true;
        }
    }
    
    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }
    
    return false;
}

bool GameModel::checkDraw() const {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY_CELL) {
                return false;
            }
        }
    }
    return true;
}

char GameModel::getOpponent(char player) const {
    return (player == PLAYER_X) ? PLAYER_O : PLAYER_X;
}

// AI Implementation (based on original code)
void GameModel::cloneBoard(char destination[BOARD_SIZE][BOARD_SIZE]) const {
    memcpy(destination, board, BOARD_SIZE * BOARD_SIZE);
}

int GameModel::countUp(int row, int col, char player) const {
    int count = 0;
    for (int i = row; i >= 0 && board[i][col] == player; i--) {
        count++;
    }
    return count;
}

int GameModel::countRight(int row, int col, char player) const {
    int count = 0;
    for (int j = col; j < BOARD_SIZE && board[row][j] == player; j++) {
        count++;
    }
    return count;
}

int GameModel::countUpRight(int row, int col, char player) const {
    int count = 0;
    for (int i = row, j = col; i >= 0 && j < BOARD_SIZE && board[i][j] == player; i--, j++) {
        count++;
    }
    return count;
}

int GameModel::countDownRight(int row, int col, char player) const {
    int count = 0;
    for (int i = row, j = col; i < BOARD_SIZE && j < BOARD_SIZE && board[i][j] == player; i++, j++) {
        count++;
    }
    return count;
}

int GameModel::getMaxCount(char player) const {
    int maxCount = 0;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            int count = 0;
            count = countUp(i, j, player);
            if (count > maxCount) maxCount = count;
            
            count = countRight(i, j, player);
            if (count > maxCount) maxCount = count;
            
            count = countUpRight(i, j, player);
            if (count > maxCount) maxCount = count;
            
            count = countDownRight(i, j, player);
            if (count > maxCount) maxCount = count;
        }
    }
    
    return maxCount;
}

void GameModel::getWinningMove(char player, int& row, int& col) {
    char tempBoard[BOARD_SIZE][BOARD_SIZE];
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (isCellEmpty(i, j)) {
                cloneBoard(tempBoard);
                tempBoard[i][j] = player;
                
                // Create a temporary model to check win
                GameModel tempModel;
                for (int x = 0; x < BOARD_SIZE; x++) {
                    for (int y = 0; y < BOARD_SIZE; y++) {
                        if (tempBoard[x][y] != EMPTY_CELL) {
                            // We can't directly set the board, so we'll check differently
                            if (tempBoard[x][y] == player) {
                                // This is a simplified check - in a real implementation,
                                // we would need a more sophisticated approach
                                continue;
                            }
                        }
                    }
                }
                
                // Simplified win check for this position
                bool win = false;
                // Check row
                if ((j == 0 && tempBoard[i][1] == player && tempBoard[i][2] == player) ||
                    (j == 1 && tempBoard[i][0] == player && tempBoard[i][2] == player) ||
                    (j == 2 && tempBoard[i][0] == player && tempBoard[i][1] == player)) {
                    win = true;
                }
                // Check column
                else if ((i == 0 && tempBoard[1][j] == player && tempBoard[2][j] == player) ||
                         (i == 1 && tempBoard[0][j] == player && tempBoard[2][j] == player) ||
                         (i == 2 && tempBoard[0][j] == player && tempBoard[1][j] == player)) {
                    win = true;
                }
                // Check diagonals
                else if ((i == j && 
                         ((i == 0 && tempBoard[1][1] == player && tempBoard[2][2] == player) ||
                          (i == 1 && tempBoard[0][0] == player && tempBoard[2][2] == player) ||
                          (i == 2 && tempBoard[0][0] == player && tempBoard[1][1] == player))) ||
                         (i + j == 2 &&
                         ((i == 0 && tempBoard[1][1] == player && tempBoard[2][0] == player) ||
                          (i == 1 && tempBoard[0][2] == player && tempBoard[2][0] == player) ||
                          (i == 2 && tempBoard[0][2] == player && tempBoard[1][1] == player)))) {
                    win = true;
                }
                
                if (win) {
                    row = i;
                    col = j;
                    return;
                }
            }
        }
    }
    
    row = col = -1;
}

void GameModel::getBestMove(char player, int& row, int& col, int& count) {
    char tempBoard[BOARD_SIZE][BOARD_SIZE];
    int maxCount = 0;
    int bestRow = -1, bestCol = -1;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (isCellEmpty(i, j)) {
                cloneBoard(tempBoard);
                tempBoard[i][j] = player;
                
                // Create a temporary model to check counts
                GameModel tempModel;
                int tempCount = 0;
                
                // Simplified count check
                // Check row
                int rowCount = 0;
                for (int k = 0; k < BOARD_SIZE; k++) {
                    if (tempBoard[i][k] == player) rowCount++;
                }
                if (rowCount > tempCount) tempCount = rowCount;
                
                // Check column
                int colCount = 0;
                for (int k = 0; k < BOARD_SIZE; k++) {
                    if (tempBoard[k][j] == player) colCount++;
                }
                if (colCount > tempCount) tempCount = colCount;
                
                // Check diagonals
                if (i == j) { // Main diagonal
                    int diagCount = 0;
                    for (int k = 0; k < BOARD_SIZE; k++) {
                        if (tempBoard[k][k] == player) diagCount++;
                    }
                    if (diagCount > tempCount) tempCount = diagCount;
                }
                
                if (i + j == 2) { // Anti-diagonal
                    int antiDiagCount = 0;
                    for (int k = 0; k < BOARD_SIZE; k++) {
                        if (tempBoard[k][2-k] == player) antiDiagCount++;
                    }
                    if (antiDiagCount > tempCount) tempCount = antiDiagCount;
                }
                
                if (tempCount > maxCount) {
                    maxCount = tempCount;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }
    
    row = bestRow;
    col = bestCol;
    count = maxCount;
}

int GameModel::getRandomInRange(int min, int max) const {
    return min + (rand() % (max - min + 1));
}

void GameModel::getRandomMove(int& row, int& col) {
    do {
        row = getRandomInRange(0, BOARD_SIZE - 1);
        col = getRandomInRange(0, BOARD_SIZE - 1);
    } while (!isCellEmpty(row, col));
}

void GameModel::getCPUMove(int& row, int& col) {
    char opponent = getOpponent(PLAYER_O);
    
    // 1. Try to win
    getWinningMove(PLAYER_O, row, col);
    if (row != -1 && col != -1) {
        return;
    }
    
    // 2. Try to block opponent
    getWinningMove(opponent, row, col);
    if (row != -1 && col != -1) {
        return;
    }
    
    // 3. Try to get best move
    int count;
    getBestMove(PLAYER_O, row, col, count);
    if (row != -1 && col != -1) {
        return;
    }
    
    // 4. Random move
    getRandomMove(row, col);
}
