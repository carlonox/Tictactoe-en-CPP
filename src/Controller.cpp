#include "../include/Controller.h"
#include <iostream>
#include <sstream>

Controller::Controller() : gameRunning(true), chatInitialized(false) {
    // Initialize chat
    initializeChat();
}

void Controller::initializeChat() {
    // Set player names
    chatModel.setLocalPlayerName("Player X");
    chatModel.setRemotePlayerName("Player O");
    
    // In a real implementation, we would initialize network here
    // For now, we'll just add a welcome message
    chatModel.addMessage("System", "Bienvenido al chat de Tic Tac Toe!");
    chatInitialized = true;
}

void Controller::run() {
    // Main game loop
    while (gameRunning && gameView.isOpen()) {
        handleEvents();
        updateGameDisplay();
        updateChatDisplay();
        gameView.display();
    }
}

void Controller::handleEvents() {
    sf::Event event;
    while (gameView.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            gameRunning = false;
            gameView.close();
        }
        
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                int row, col;
                if (gameView.getClickedCell(event.mouseButton.x, event.mouseButton.y, row, col)) {
                    handleGameInput(row, col);
                }
            }
        }
        
        if (event.type == sf::Event::TextEntered) {
            chatView.handleTextInput(event.text.unicode);
        }
        
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                handleChatInput();
            } else {
                chatView.handleKeyPress(event.key.code);
            }
        }
    }
    
    // Process network messages (placeholder)
    processNetworkMessages();
}

void Controller::handleGameInput(int row, int col) {
    // Only process input if game is not ended
    if (!gameModel.isGameEnded()) {
        char currentPlayer = gameModel.getCurrentPlayer();
        
        // Only allow player X to make moves (player O is CPU)
        if (currentPlayer == PLAYER_X) {
            if (gameModel.placePiece(row, col, currentPlayer)) {
                // Successfully placed piece
                // CPU will make its move if game is not ended
                if (!gameModel.isGameEnded()) {
                    int cpuRow, cpuCol;
                    gameModel.getCPUMove(cpuRow, cpuCol);
                    gameModel.placePiece(cpuRow, cpuCol, PLAYER_O);
                }
            }
        }
    } else {
        // Game has ended, check for restart
        resetGame();
    }
}

void Controller::handleChatInput() {
    std::string message = chatView.getAndClearInput();
    if (!message.empty()) {
        // Add to local chat
        chatModel.addMessage(chatModel.getLocalPlayerName(), message);
        
        // In a real implementation, we would send this over network
        // For now, we'll just process it locally
        processChatMessage(message);
    }
}

void Controller::processChatMessage(const std::string& message) {
    // Process special chat commands
    if (message == "/reset") {
        resetGame();
        chatModel.addMessage("System", "Juego reiniciado");
    } else if (message == "/help") {
        chatModel.addMessage("System", "Comandos: /reset, /help");
    }
}

void Controller::resetGame() {
    gameModel.resetGame();
}

void Controller::updateGameDisplay() {
    gameView.clear();
    gameView.drawBoard();
    
    // Draw all pieces on the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            char cell = gameModel.getCell(i, j);
            if (cell != EMPTY_CELL) {
                gameView.drawCell(i, j, cell);
            }
        }
    }
    
    // Draw game status
    if (gameModel.isGameEnded()) {
        if (gameModel.getWinner() != EMPTY_CELL) {
            std::stringstream ss;
            ss << "Jugador " << gameModel.getWinner() << " gana!";
            gameView.drawStatus(ss.str());
        } else {
            gameView.drawStatus("Empate!");
        }
    } else {
        gameView.drawPlayerTurn(gameModel.getCurrentPlayer());
    }
}

void Controller::updateChatDisplay() {
    // Add any new messages to the chat view
    // In a real implementation, we would check for new network messages
    // For now, we'll just redraw all messages
    
    // Draw chat view
    chatView.draw(gameView); // Pass the render window
}

void Controller::processNetworkMessages() {
    // In a real implementation, we would check for incoming network messages
    // For now, this is a placeholder
}
