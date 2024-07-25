//
// Created by burr on 25.07.2024.
//

#include "Node.h"
#include <iostream>
#include <memory>
#include <utility>

Node::Node(std::string name) : name(std::move(name)) {}

void Node::createEvent(const int value) {
    for(auto& [receiver, stats]: subscriptions) {
        stats.first += value;
        stats.second++;
    }
}

void Node::subscribe(Node *other) {
    if(other && other != this) {
        subscriptions[other] = {0,0};
    }
}

void Node::unsubscribe(Node *other) {
    subscriptions.erase(other);
}

void Node::createAndSubscribe() {
    static int nodeCounter = 1;
    std::string newName = "Node" + std::to_string(nodeCounter++);
    const auto newNode = std::make_shared<Node>(newName);
    subscribe(newNode.get());
}

void Node::update() {
    for(auto& [receiver, stats]: subscriptions) {
        std::cout << name
            << " -> " << receiver->name
            << ": S = " << stats.first
            << ", N = " << stats.second
        << std::endl;
    }
}