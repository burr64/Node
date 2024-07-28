//
// Created by burr on 25.07.2024.
//

#include "Node.h"
#include "Network.h"
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <algorithm>
#include <cstdlib>

void printSubscriptions(Node* node) {
    std::cout << "Subscriptions of " << node->name << ": [";
    bool first = true;
    for (const auto& [subscribedNode, stats] : node->subscriptions) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << subscribedNode->name;
        first = false;
    }
    std::cout << "]" << std::endl;
}

void randomInitializeNetwork(Network& network, const int numNodes) {
    if (numNodes < 1) {
        std::cerr << "The number of nodes must be at least 1!" << std::endl;
        return;
    }

    const auto initialNode = new Node("Node1", &network);
    network.addNode(initialNode);

    std::vector<Node*> allNodes;
    allNodes.push_back(initialNode);

    for (int i = 1; i < numNodes; ++i) {
        Node* randomNode = allNodes[rand() % allNodes.size()];
        std::string newName = "Node" + std::to_string(i + 1);
        randomNode->createNode(newName);

        Node* newNode = network.neighbors[randomNode].back();
        allNodes.push_back(newNode);
    }
}

void randomSubscription(Network& network) {
    std::vector<Node*> allNodes;
    for (const auto& [node, _] : network.neighbors) {
        allNodes.push_back(node);
    }

    for (Node* node : allNodes) {
        if (node->subscriptions.empty()) {
            std::vector<Node*> potentialNeighbors;
            for (Node* potentialNode : allNodes) {
                if (potentialNode != node) {
                    potentialNeighbors.push_back(potentialNode);
                }
            }

            if (!potentialNeighbors.empty()) {
                Node* randomNode = potentialNeighbors[std::rand() % potentialNeighbors.size()];
                node->subscriptions[randomNode]={0,0};
                network.neighbors[node].push_back(randomNode);
            }
        }
    }
}


int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    Network network;

    int numNodes;
    std::cout << "Number of nodes (excluding the initial node):";
    std::cin >> numNodes;

    randomInitializeNetwork(network, numNodes);
    randomSubscription(network);

    int eventProbability, createNodeProbability, unsubscribeProbability;
    std::cout << "Probability event (0 to 100%):";
    std::cin >> eventProbability;
    std::cout << "Probability new node (0 to 100%):";
    std::cin >> createNodeProbability;
    std::cout << "Probability unsubscribing (0 to 100%):";
    std::cin >> unsubscribeProbability;

    while (!network.neighbors.empty()) {
        network.update();

        for (auto& [backupNode, _] : network.neighbors) {
            for (auto& [node, _] : network.neighbors) {
                if (node == backupNode) {
                    if (rand() % 100 < eventProbability) {
                        node->createEvent(rand() % 100 + 1);
                    }

                    if (rand() % 100 < createNodeProbability) {
                        node->createNode("Node" + std::to_string(network.neighbors.size() + 1));
                    }

                    if (rand() % 100 < unsubscribeProbability) {
                        if (!node->subscriptions.empty()) {
                            const auto randomNode = network.neighbors[node][std::rand() % network.neighbors[node].size()];
                            node->unsubscribe(randomNode);
                        }
                    }
                }
            }
        }
    }
    std::cout << "end";
    return 0;
}

