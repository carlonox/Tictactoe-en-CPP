#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "GameModel.h"
#include "ChatModel.h"
#include "GameView.h"
#include "ChatView.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

class Controller {
private:
    GameModel gameModel;
    ChatModel chatModel;
    GameView gameView;
    ChatView chatView;
    
    bool gameRunning;
    bool chatInitialized;
    
public:
    Controller();
    
    // Main game loop
    void run();
    
    // Event handling
    void handleEvents();
    void handleGameInput(int row, int col);
    void handleChatInput();
    
    // Game state management
    void resetGame();
    void updateGameDisplay();
    void updateChatDisplay();
    
    // Network methods
    void initializeChat();
    void processNetworkMessages();
    
private:
    void processChatMessage(const std::string& message);
};

#endif // CONTROLLER_H
