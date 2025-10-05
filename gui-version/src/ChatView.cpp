#include "../include/ChatView.h"
#include <iostream>
#include <sstream>
#include <algorithm>

ChatView::ChatView() : inputBuffer("") {
    // Apply Frutiger Aero styling
    applyFrutigerAeroStyle();
    
    // Load resources
    loadResources();
    
    // Initialize UI elements
    initUI();
}

void ChatView::applyFrutigerAeroStyle() {
    // Frutiger Aero color scheme for chat
    backgroundColor = sf::Color(135, 206, 250, 200); // Light sky blue with transparency
    borderColor = sf::Color(30, 144, 255);           // Dodger blue
    inputBoxColor = sf::Color(240, 248, 255);        // Alice blue
    textColor = sf::Color(0, 0, 139);                // Dark blue
}

void ChatView::loadResources() {
    // In a real implementation, we would load fonts here
    // For now, we'll use default SFML fonts
    if (!font.loadFromFile("arial.ttf")) {
        // If arial.ttf is not found, SFML will use a default font
        std::cout << "Warning: Could not load arial.ttf, using default font" << std::endl;
    }
}

void ChatView::initUI() {
    // Initialize chat background
    chatBackground.setSize(sf::Vector2f(CHAT_WINDOW_WIDTH, CHAT_WINDOW_HEIGHT));
    chatBackground.setPosition(CHAT_OFFSET_X, CHAT_OFFSET_Y);
    chatBackground.setFillColor(backgroundColor);
    chatBackground.setOutlineThickness(2);
    chatBackground.setOutlineColor(borderColor);
    
    // Initialize chat title
    chatTitle.setFont(font);
    chatTitle.setString("Chat");
    chatTitle.setCharacterSize(20);
    chatTitle.setFillColor(textColor);
    chatTitle.setPosition(CHAT_OFFSET_X + 10, CHAT_OFFSET_Y + 10);
    
    // Initialize message input box
    messageInputBox.setSize(sf::Vector2f(CHAT_WINDOW_WIDTH - 20, 30));
    messageInputBox.setPosition(CHAT_OFFSET_X + 10, CHAT_OFFSET_Y + CHAT_WINDOW_HEIGHT - 40);
    messageInputBox.setFillColor(inputBoxColor);
    messageInputBox.setOutlineThickness(1);
    messageInputBox.setOutlineColor(borderColor);
    
    // Initialize message input text
    messageInputText.setFont(font);
    messageInputText.setCharacterSize(16);
    messageInputText.setFillColor(textColor);
    messageInputText.setPosition(CHAT_OFFSET_X + 15, CHAT_OFFSET_Y + CHAT_WINDOW_HEIGHT - 35);
}

void ChatView::draw(sf::RenderWindow& window) {
    // Draw chat background
    window.draw(chatBackground);
    
    // Draw chat title
    window.draw(chatTitle);
    
    // Draw message input box
    window.draw(messageInputBox);
    
    // Draw message input text
    window.draw(messageInputText);
    
    // Draw chat messages
    for (const auto& message : chatMessages) {
        window.draw(message);
    }
}

void ChatView::addMessage(const std::string& sender, const std::string& message) {
    // Create a new message text
    sf::Text messageText;
    messageText.setFont(font);
    messageText.setCharacterSize(14);
    messageText.setFillColor(textColor);
    
    // Format the message
    std::string formattedMessage = sender + ": " + message;
    messageText.setString(formattedMessage);
    
    // Position the message
    float yPos = CHAT_OFFSET_Y + 40 + (chatMessages.size() * 20);
    // If we have too many messages, remove the oldest ones
    if (chatMessages.size() >= 15) {
        chatMessages.erase(chatMessages.begin());
        // Adjust positions of remaining messages
        for (size_t i = 0; i < chatMessages.size(); ++i) {
            chatMessages[i].setPosition(CHAT_OFFSET_X + 10, CHAT_OFFSET_Y + 40 + (i * 20));
        }
        yPos = CHAT_OFFSET_Y + 40 + (chatMessages.size() * 20);
    }
    
    messageText.setPosition(CHAT_OFFSET_X + 10, yPos);
    chatMessages.push_back(messageText);
}

void ChatView::handleTextInput(sf::Uint32 unicode) {
    // Handle regular text input
    if (unicode >= 32 && unicode <= 126) { // Printable ASCII characters
        inputBuffer += static_cast<char>(unicode);
        updateInputText();
    }
}

void ChatView::handleKeyPress(sf::Keyboard::Key key) {
    // Handle special keys
    if (key == sf::Keyboard::Backspace) {
        if (!inputBuffer.empty()) {
            inputBuffer.pop_back();
            updateInputText();
        }
    }
}

std::string ChatView::getAndClearInput() {
    std::string temp = inputBuffer;
    inputBuffer.clear();
    updateInputText();
    return temp;
}

void ChatView::updateInputText() {
    // Limit the displayed text to fit in the input box
    std::string displayText = inputBuffer;
    if (displayText.length() > 30) {
        displayText = "..." + displayText.substr(displayText.length() - 27);
    }
    
    messageInputText.setString(displayText);
}
