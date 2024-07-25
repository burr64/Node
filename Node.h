//
// Created by burr on 25.07.2024.
//

#ifndef NODE_H
#define NODE_H
#include <string>
#include <unordered_map>


class Node {
public:
    std::string name;
    std::unordered_map<Node*, std::pair<int,int>> subscription;

    explicit Node(const std::string& name);

    void createEvent(int value);
    void subscribe(Node* other);
    void unsubscribe(Node* other);
    void createAndSubscribe();
    void update();
};

#endif //NODE_H