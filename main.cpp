#include <iostream>
#include <vector>

#include "Network.h"
#include "Node.h"

int main() {
    const auto network = new Network;

    const auto node1 = new Node("Node1");

    network->addNode(node1);

    node1->createNode(new Node("Node2"), network);


    //
    // const auto newNode = new Node("NewNode");
    // network.push_back(newNode);
    //
    // node1->createAndSubscribe(newNode);
    //
    // for(int i = 0; i < 5; ++i) {
    //     for(const auto& node: network) {
    //         node -> createEvent(rand()%100+1);
    //     }
    //
    //     for (const auto& node: network) {
    //         node -> update();
    //     }
    // }
    //
    // for(const auto& node: network) {
    //     delete node;
    // }
    //
    return 0;
}