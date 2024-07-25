//
// Created by burr on 25.07.2024.
//

#ifndef NODE_H
#define NODE_H
#include <string>
#include <unordered_map>
#include "Network.h"

class Network;

class Node {
public:
    std::string name;
    std::unordered_map<Node*, std::pair<int, int>> subscriptions;
    explicit Node(std::string  name, Network* network);

    void createEvent(int value);
    void subscribe(Node *other);
    void unsubscribe(Node* other);
    void createNode(const std::string& newName);

private:
    Network* network;
};

#endif //NODE_H