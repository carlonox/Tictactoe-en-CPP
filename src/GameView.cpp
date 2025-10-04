#include "../include/GameView.h"
#include <iostream>
#include <sstream>

GameView::GameView() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tic Tac Toe - Frutiger Aero Edition") {
    // Apply Frutiger Aero styling
    applyFrutigerAeroStyle();
    
    // Load resources
    loadResources();
    
    // Initialize UI elements
    initUI();
}

GameView::~GameView() {
    // Clean up resources if needed
}

void GameView::applyFrutigerAeroStyle() {
    // Frutiger Aero color scheme
    backgroundColor = sf::Color(173, 216, 230); // Light blue
    cellColor = sf::Color(240, 248, 255);        // Alice blue
    cellBorderColor = sf::Color(70, 130, 180);   // Steel blue
    textColor = sf::Color(0, 0, 139);            // Dark blue
    
    // Apply to window
    window.clear(backgroundColor);
}

void GameView::loadResources() {
    // In a real implementation, we would load fonts and textures here
    // For now, we'll use default SFML fonts
    if (!font.loadFromFile("arial.ttf")) {
        // If arial.ttf is not found, SFML will use a default font
        std::cout << "Warning: Could not load arial.ttf, using default font" << std::endl;
    }
}

void GameView::initUI() {
    // Initialize board background
    boardBackground.setSize(sf::Vector2f(CELL_SIZE * BOARD_SIZE + 20, CELL_SIZE * BOARD_SIZE + 20));
    boardBackground.setPosition(BOARD_OFFSET_X - 10, BOARD_OFFSET_Y - 10);
    boardBackground.setFillColor(sf::Color(255, 255, 255, 150)); // Semi-transparent white
    boardBackground.setOutlineThickness(2);
    boardBackground.setOutlineColor(cellBorderColor);
    
    // Initialize cells
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cells[i][j].setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cells[i][j].setPosition(BOARD_OFFSET_X + j * CELL_SIZE, BOARD_OFFSET_Y + i * CELL_SIZE);
            cells[i][j].setFillColor(cellColor);
            cells[i][j].setOutlineThickness(2);
            cells[i][j].setOutlineColor(cellBorderColor);
        }
    }
    
    // Initialize status text
    statusText.setFont(font);
    statusText.setCharacterSize(24);
    statusText.setFillColor(textColor);
    statusText.setPosition(50, WINDOW_HEIGHT - 100);
    
    // Initialize player turn text
    playerTurnText.setFont(font);
    playerTurnText.setCharacterSize(20);
    playerTurnText.setFillColor(textColor);
    playerTurnText.setPosition(50, WINDOW_HEIGHT - 70);
}

bool GameView::isOpen() const {
    return window.isOpen();
}

void GameView::close() {
    window.close();
}

void GameView::clear() {
    window.clear(backgroundColor);
}

void GameView::display() {
    window.display();
}

bool GameView::pollEvent(sf::Event& event) {
    return window.pollEvent(event);
}

void GameView::drawBoard() {
    // Draw board background
    window.draw(boardBackground);
    
    // Draw cells
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            window.draw(cells[i][j]);
        }
    }
}

void GameView::drawCell(int row, int col, char symbol) {
    // This method would draw X or O in the specified cell
    // For now, we'll just draw text
    sf::Text symbolText;
    symbolText.setFont(font);
    symbolText.setString(symbol);
    symbolText.setCharacterSize(48);
    symbolText.setFillColor(textColor);
    
    // Center the symbol in the cell
    sf::FloatRect textBounds = symbolText.getLocalBounds();
    symbolText.setPosition(
        BOARD_OFFSET_X + col * CELL_SIZE + (CELL_SIZE - textBounds.width) / 2,
        BOARD_OFFSET_Y + row * CELL_SIZE + (CELL_SIZE - textBounds.height) / 2 - 10
    );
    
    window.draw(symbolText);
}

void GameView::drawStatus(const std::string& status) {
    statusText.setString(status);
    window.draw(statusText);
}

void GameView::drawPlayerTurn(char currentPlayer) {
    std::stringstream ss;
    ss << "Turno del jugador: " << currentPlayer;
    playerTurnText.setString(ss.str());
    window.draw(playerTurnText);
}

bool GameView::getClickedCell(int mouseX, int mouseY, int& row, int& col) {
    // Check if click is within board bounds
    if (mouseX >= BOARD_OFFSET_X && mouseX < BOARD_OFFSET_X + CELL_SIZE * BOARD_SIZE &&
        mouseY >= BOARD_OFFSET_Y && mouseY < BOARD_OFFSET_Y + CELL_SIZE * BOARD_SIZE) {
        
        // Calculate row and column
        col = (mouseX - BOARD_OFFSET_X) / CELL_SIZE;
        row = (mouseY - BOARD_OFFSET_Y) / CELL_SIZE;
        
        return true;
    }
    
    return false;
}
