#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "GraphBase.hpp"
#include <string>
#include <vector>

class Graph : public GraphBase {
public:
    Graph() = default;
    ~Graph() override = default;

    // Abstract‐class methods
    void addVertex(std::string label) override;
    void removeVertex(std::string label) override;
    void addEdge(std::string label1, std::string label2, unsigned long weight) override;
    void removeEdge(std::string label1, std::string label2) override;
    unsigned long shortestPath(std::string startLabel,
                               std::string endLabel,
                               std::vector<std::string> &path) override;

    // Utility method for debugging / demo
    void printGraph() const;

private:
    struct Edge {
        std::string dest;
        unsigned long weight;
    };

    struct Vertex {
        std::string label;
        std::vector<Edge> edges;
    };

    std::vector<Vertex> vertices;

    // Helpers
    int getVertexIndex(const std::string &label) const;
    bool edgeExists(const std::vector<Edge> &edges, const std::string &destLabel) const;
    void removeEdgeFromList(std::vector<Edge> &edges, const std::string &destLabel);
};

#endif // GRAPH_HPP
