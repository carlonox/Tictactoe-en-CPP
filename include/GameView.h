#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include <string>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int BOARD_SIZE = 3;
const int CELL_SIZE = 100;
const int BOARD_OFFSET_X = 50;
const int BOARD_OFFSET_Y = 50;

class GameView {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Texture xTexture;
    sf::Texture oTexture;
    sf::Sprite xSprite;
    sf::Sprite oSprite;
    
    // UI elements
    sf::RectangleShape boardBackground;
    sf::RectangleShape cells[BOARD_SIZE][BOARD_SIZE];
    sf::Text statusText;
    sf::Text playerTurnText;
    
    // Frutiger Aero styling colors
    sf::Color backgroundColor;
    sf::Color cellColor;
    sf::Color cellBorderColor;
    sf::Color textColor;
    
public:
    GameView();
    ~GameView();
    
    // Window management
    bool isOpen() const;
    void close();
    void clear();
    void display();
    
    // Event handling
    bool pollEvent(sf::Event& event);
    
    // Rendering methods
    void drawBoard();
    void drawCell(int row, int col, char symbol);
    void drawStatus(const std::string& status);
    void drawPlayerTurn(char currentPlayer);
    
    // Utility methods
    bool getClickedCell(int mouseX, int mouseY, int& row, int& col);
    void loadResources();
    
private:
    void initUI();
    void applyFrutigerAeroStyle();
};

#endif // GAMEVIEW_H
