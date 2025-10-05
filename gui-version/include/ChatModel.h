#ifndef CHATMODEL_H
#define CHATMODEL_H

#include <string>
#include <vector>
#include <queue>
#include <ctime>

struct ChatMessage {
    std::string sender;
    std::string content;
    std::time_t timestamp;
    
    ChatMessage(const std::string& s, const std::string& c) 
        : sender(s), content(c), timestamp(std::time(nullptr)) {}
};

class ChatModel {
private:
    std::vector<ChatMessage> messages;
    std::string localPlayerName;
    std::string remotePlayerName;
    
public:
    ChatModel();
    
    // Message management
    void addMessage(const std::string& sender, const std::string& content);
    const std::vector<ChatMessage>& getMessages() const;
    
    // Player management
    void setLocalPlayerName(const std::string& name);
    void setRemotePlayerName(const std::string& name);
    std::string getLocalPlayerName() const;
    std::string getRemotePlayerName() const;
    
    // Network methods (to be implemented)
    bool initializeNetwork();
    void sendChatMessage(const std::string& message);
    void receiveChatMessage(std::string& sender, std::string& message);
    void shutdownNetwork();
};

#endif // CHATMODEL_H
