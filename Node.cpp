//
// Created by burr on 25.07.2024.
//

#include "Node.h"
#include "Network.h"
#include <iostream>
#include <utility>
#include <algorithm>

Node::Node(std::string  name, Network* network)
    : name(std::move(name)), network(network) {}

void Node::createEvent(const int value) {
    for (auto& [receiver, stats] : subscriptions) {
        stats.first += value;
        stats.second++;
    }
}

void Node::subscribe(Node* other) {
    if (other != this) {
        for (const auto& [neighbor, _] : network->neighbors) {
            if (std::find(network->neighbors[neighbor].begin(), network->neighbors[neighbor].end(), other) != network->neighbors[neighbor].end()) {
                subscriptions[other] = {0, 0};
                network->neighbors[this].push_back(other);
                break;
            }
        }
    }
}

void Node::unsubscribe(Node* other) {
    if (subscriptions.find(other) != subscriptions.end()) {
        subscriptions.erase(other);
        auto& neighborList = network->neighbors[this];
        const auto it = std::remove(neighborList.begin(), neighborList.end(), other);
        neighborList.erase(it, neighborList.end());
    }
}

void Node::createNode(const std::string &newName) {
    auto newNode = new Node(newName, network);
    network->addNode(newNode);
    subscribe(newNode);
}
