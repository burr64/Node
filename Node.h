//
// Created by burr on 25.07.2024.
//

#ifndef NODE_H
#define NODE_H
#include <memory>
#include <string>
#include <unordered_map>


class Node {
public:
    std::string name;
    std::unordered_map<Node*, std::pair<int,int>> subscriptions;

    explicit Node(std::string  name);

    void createEvent(int value);
    void subscribe(Node* other);
    void unsubscribe(Node* other);
    void createAndSubscribe(Node* newNode);
    void update();
};

#endif //NODE_H