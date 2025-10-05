#include "../include/ChatModel.h"
#include <iostream>
#include <algorithm>

ChatModel::ChatModel() : localPlayerName("Player"), remotePlayerName("Opponent") {}

void ChatModel::addMessage(const std::string& sender, const std::string& content) {
    if (!content.empty()) {
        messages.emplace_back(sender, content);
    }
}

const std::vector<ChatMessage>& ChatModel::getMessages() const {
    return messages;
}

void ChatModel::setLocalPlayerName(const std::string& name) {
    if (!name.empty()) {
        localPlayerName = name;
    }
}

void ChatModel::setRemotePlayerName(const std::string& name) {
    if (!name.empty()) {
        remotePlayerName = name;
    }
}

std::string ChatModel::getLocalPlayerName() const {
    return localPlayerName;
}

std::string ChatModel::getRemotePlayerName() const {
    return remotePlayerName;
}

// Network methods - placeholder implementations
bool ChatModel::initializeNetwork() {
    // In a real implementation, this would initialize TCP sockets
    // For now, we'll just return true to indicate success
    std::cout << "Network initialization placeholder" << std::endl;
    return true;
}

void ChatModel::sendChatMessage(const std::string& message) {
    // In a real implementation, this would send the message over TCP
    // For now, we'll just add it to our local messages
    if (!message.empty()) {
        addMessage(localPlayerName, message);
    }
}

void ChatModel::receiveChatMessage(std::string& sender, std::string& message) {
    // In a real implementation, this would receive a message over TCP
    // For now, this is a placeholder
    sender = "";
    message = "";
}

void ChatModel::shutdownNetwork() {
    // In a real implementation, this would close TCP connections
    // For now, this is a placeholder
    std::cout << "Network shutdown placeholder" << std::endl;
}
