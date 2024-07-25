//
// Created by burr on 25.07.2024.
//

#ifndef NETWORK_H
#define NETWORK_H

#include "Node.h"
#include <unordered_map>
#include <vector>

class Network {
public:
    std::unordered_map<Node*, std::vector<Node*>> neighbors;

    void addNode(Node* node);
    void removeNode(Node* node);
    void update();
};

#endif // NETWORK_H
