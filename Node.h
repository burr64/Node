//
// Created by burr on 25.07.2024.
//

#ifndef NODE_H
#define NODE_H
#include <string>
#include <unordered_map>

class Network;

class Node {
public:
    std::string name;
    std::unordered_map<Node*, std::pair<int,int>> subscriptions;

    explicit Node(std::string  name);

    void createEvent(int value);
    void subscribe(Node *other, Network *network);
    void unsubscribe(Node* other, Network* network);
    void createNode(Node* newNode, Network* network);
};

#endif //NODE_H