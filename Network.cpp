//
// Created by burr on 25.07.2024.
//

#include "Network.h"
#include <iostream>
#include <algorithm>

void Network::addNode(Node* node) {
    neighbors[node] = {};
}

void Network::removeNode(Node* node) {
    const auto nodeInNetwork = neighbors.find(node);
    if (nodeInNetwork == neighbors.end()) {
        return;
    }

    for (Node* neighbor : nodeInNetwork->second) {
        neighbor->unsubscribe(node, this);
    }

    neighbors.erase(nodeInNetwork);
    delete node;
}

void Network::update() {
    for (const auto& [node, neighborList] : neighbors) {
        for (const auto& neighbor : neighborList) {
            std::cout << node->name
                      << " -> " << neighbor->name
                      << ": S = " << node->subscriptions[neighbor].first
                      << ", N = " << node->subscriptions[neighbor].second
                      << std::endl;
        }
    }

    for (const auto& [node, neighborList] : neighbors) {
        if (neighborList.empty()) {
            removeNode(node);
        }
    }
}
