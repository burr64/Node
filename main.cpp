#include "Node.h"
#include "Network.h"
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>

void initializeNetwork(Network& network, const int numNodes) {
    if (numNodes < 2) {
        std::cerr << "The number of nodes must be greater than 1!" << std::endl;
        return;
    }

    std::vector<Node*> nodes;

    for (int i = 0; i < numNodes; ++i) {
        const std::string name = "Node" + std::to_string(i + 1);
        auto node = new Node(name, &network);
        network.addNode(node);
        nodes.push_back(node);
    }

    for (Node* node : nodes) {
        Node* neighbor = nodes[(rand() % numNodes)];
        if (neighbor != node) {
            node->subscribe(neighbor);
        }
    }
}

int main() {
    Network network;

    int numNodes;
    std::cout << "Number of nodes:";
    std::cin >> numNodes;

    initializeNetwork(network, numNodes);

    int eventProbability, createNodeProbability, unsubscribeProbability;
    std::cout << "Probability event (0 to 100%):";
    std::cin >> eventProbability;
    std::cout << "Probability new node (0 to 100%):";
    std::cin >> createNodeProbability;
    std::cout << "Probability unsubscribing (0 to 100%):";
    std::cin >> unsubscribeProbability;

    while (network.neighbors.empty()) {
        network.update();

        for (auto& [node, _] : network.neighbors) {
            if (rand() % 100 < eventProbability) {
                node->createEvent(rand() % 100 + 1);
            }

            if (rand() % 100 < createNodeProbability) {
                node->createNode("NewNode");
            }

            if (rand() % 100 < createNodeProbability) {
                // Get a list of all nodes
                std::vector<Node*> allNodes;
                for (auto& [n, _] : network.neighbors) {
                    allNodes.push_back(n);
                }

                Node* potentialNeighbor = allNodes[rand() % allNodes.size()];
                if (potentialNeighbor != node) {
                    node->subscribe(potentialNeighbor);
                }
            }

            if (rand() % 100 < unsubscribeProbability) {
                if (!node->subscriptions.empty()) {
                    auto it = node->subscriptions.begin();
                    std::advance(it, rand() % node->subscriptions.size());
                    Node* toUnsubscribe = it->first;
                    node->unsubscribe(toUnsubscribe);
                }
            }
        }

        //std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "Network degenerated. Ending simulation." << std::endl;

    return 0;
}
