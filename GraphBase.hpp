#ifndef GRAPHBASE_H
#define GRAPHBASE_H

#include <vector>
#include <string>

class GraphBase {
public:
    // Virtual destructor to ensure correct destruction of derived classes
    virtual ~GraphBase() = default;

    // Add a vertex with the given label to the graph
    virtual void addVertex(std::string label) = 0;

    // Remove the vertex with the given label and all its incident edges
    virtual void removeVertex(std::string label) = 0;

    // Add a weighted edge between the two vertices with the given labels
    virtual void addEdge(std::string label1, std::string label2, unsigned long weight) = 0;

    // Remove the edge between the two vertices with the given labels
    virtual void removeEdge(std::string label1, std::string label2) = 0;

    // Find the shortest path between the two vertices with the given labels and
    // store it in the given vector. The path is returned as a vector of vertex
    // labels. The weight of the path is returned as an unsigned long.
    virtual unsigned long shortestPath(std::string startLabel,
                                      std::string endLabel,
                                      std::vector<std::string> &path) = 0;
};

#endif // GRAPHBASE_H