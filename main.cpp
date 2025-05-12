#include "Graph.hpp"
#include <iostream>
#include <limits>
#include <vector>
#include <string>

int main() {
    Graph g;
    std::vector<std::string> path;
    int choice;

    while (true) {
        std::cout << "Dynamic Graph Menu:\n";
        std::cout << "1. Add Vertex \n";
        std::cout << "2. Remove Vertex\n";
        std::cout << "3. Add Edge\n";
        std::cout << "4. Remove Edge\n";
        std::cout << "5. Compute Shortest Path\n";
        std::cout << "6. Print Graph\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: \n";
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "Exiting program.";
            break;
        }

        switch (choice) {
            case 1: {
                std::string label;
                std::cout << "Enter vertex label: ";
                std::cin >> label;
                g.addVertex(label);
                break;
            }
            case 2: {
                std::string label;
                std::cout << "Enter vertex label to remove: ";
                std::cin >> label;
                g.removeVertex(label);
                break;
            }
            case 3: {
                std::string u, v;
                unsigned long w;
                std::cout << "Enter first vertex label: ";
                std::cin >> u;
                std::cout << "Enter second vertex label: ";
                std::cin >> v;
                std::cout << "Enter edge weight: ";
                std::cin >> w;
                g.addEdge(u, v, w);
                break;
            }
            case 4: {
                std::string u, v;
                std::cout << "Enter first vertex label: ";
                std::cin >> u;
                std::cout << "Enter second vertex label: ";
                std::cin >> v;
                g.removeEdge(u, v);
                break;
            }
            case 5: {
                std::string s, t;
                std::cout << "Enter start vertex label: ";
                std::cin >> s;
                std::cout << "Enter end vertex label: ";
                std::cin >> t;
                unsigned long cost = g.shortestPath(s, t, path);
                if (cost == std::numeric_limits<unsigned long>::max()) {
                    std::cout << "No path exists from '" << s << "' to '" << t << "'.";
                } else {
                    std::cout << "Shortest path (Cost: " << cost << "): ";
                    for (size_t i = 0; i < path.size(); ++i) {
                        std::cout << path[i];
                        if (i + 1 < path.size()) std::cout << " -> ";
                    }
                    std::cout << "";
                }
                break;
            }
            case 6:
                g.printGraph();
                break;
            default:
                std::cout << "Invalid choice, try again.";
        }
    }

    return 0;
}