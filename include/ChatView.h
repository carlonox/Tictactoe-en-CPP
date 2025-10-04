#ifndef CHATVIEW_H
#define CHATVIEW_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

const int CHAT_WINDOW_WIDTH = 300;
const int CHAT_WINDOW_HEIGHT = 400;
const int CHAT_OFFSET_X = 500;
const int CHAT_OFFSET_Y = 50;

class ChatView {
private:
    sf::RectangleShape chatBackground;
    sf::RectangleShape messageInputBox;
    sf::Text messageInputText;
    sf::Text chatTitle;
    std::vector<sf::Text> chatMessages;
    
    // Frutiger Aero styling colors
    sf::Color backgroundColor;
    sf::Color borderColor;
    sf::Color inputBoxColor;
    sf::Color textColor;
    
    sf::Font font;
    std::string inputBuffer;
    
public:
    ChatView();
    
    // Rendering methods
    void draw(sf::RenderWindow& window);
    void addMessage(const std::string& sender, const std::string& message);
    
    // Event handling
    void handleTextInput(sf::Uint32 unicode);
    void handleKeyPress(sf::Keyboard::Key key);
    std::string getAndClearInput();
    
    // Utility methods
    void loadResources();
    
private:
    void applyFrutigerAeroStyle();
    void initUI();
    void updateInputText();
};

#endif // CHATVIEW_H
