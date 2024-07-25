#include <iostream>
#include <vector>

#include "Node.h"

int main() {
    std::vector<Node*> network;

    const auto node1 = new Node("Node1");
    const auto node2 = new Node("Node2");

    node1 -> subscribe(node2);
    node2 -> subscribe(node1);

    network.push_back(node1);
    network.push_back(node2);

    const auto newNode = new Node("NewNode");
    network.push_back(newNode);

    node1->createAndSubscribe(newNode);

    for(int i = 0; i < 5; ++i) {
        for(const auto& node: network) {
            node -> createEvent(rand()%100+1);
        }

        for (const auto& node: network) {
            node -> update();
        }
    }

    for(const auto& node: network) {
        delete node;
    }

    return 0;
}