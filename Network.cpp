//
// Created by burr on 25.07.2024.
//

#include "Network.h"
#include "Node.h"
#include <iostream>
#include <algorithm>
#include <map>

void Network::addNode(Node* node) {
    neighbors[node] = {};
}

void Network::removeNode(Node* node) {
    const auto nodeInNetwork = neighbors.find(node);
    if (nodeInNetwork == neighbors.end()) {
        return;
    }

    for (Node* neighbor : nodeInNetwork->second) {
        neighbor->unsubscribe(node);
    }

    neighbors.erase(nodeInNetwork);
    delete node;
}

void Network::update() {
    for (const auto& [node, neighborList] : neighbors) {
        if (neighborList.empty()) {
            removeNode(node);
        }
    }

    for (const auto& [node, neighborList] : neighbors) {
        for (const auto& neighbor : neighborList) {
            std::cout << node->name
                      << " -> " << neighbor->name
                      << ": S = " << node->subscriptions[node].first
                      << ", N = " << node->subscriptions[node].second
                      << std::endl;
        }
    }
    std::cout << "\n";
}

void Network::printNetwork() const {
    for (const auto& [node, neighborList] : neighbors) {
        std::cout << node->name << ": [";
        for (size_t i = 0; i < neighborList.size(); ++i) {
            std::cout << neighborList[i]->name;
            if (i < neighborList.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
}

