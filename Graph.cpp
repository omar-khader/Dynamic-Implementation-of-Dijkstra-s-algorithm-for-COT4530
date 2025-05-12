// Graph.cpp

#include "Graph.hpp"
#include <iostream>
#include <limits>
#include <algorithm>

/**
 * \brief Adds a new vertex to the graph
 * \param label The unique label for the vertex
 * \return void
 */
void Graph::addVertex(std::string label) {
    // Check if the vertex already exists in the graph
    // If it does, just print a message and return
    if (getVertexIndex(label) != -1) {
        // Print a message if the vertex already exists and return
        std::cout << "Vertex \"" << label << "\" already exists.\n";
        return;
    }

    // Create a new Vertex object to store the vertex data
    Vertex v;

    // Set the label of the new vertex
    // This is the unique identifier for the vertex
    v.label = label;

    // Initialize the edges of the new vertex to an empty vector
    // This vector will store all the edges connected to the vertex
    v.edges = {};

    // Add the new vertex to the list of vertices
    // This list stores all the vertices in the graph
    vertices.push_back(v);

    // Print a message indicating the vertex was added
    std::cout << "Added vertex \"" << label << "\".\n";
}

/**
 * \brief Removes a vertex from the graph
 * \param label The label of the vertex to remove
 * \return void
 */
void Graph::removeVertex(std::string label) {
    int idx = getVertexIndex(label);
    if (idx == -1) {
        std::cout << "Vertex \"" << label << "\" does not exist.\n";
        return;
    }
    // Remove all edges pointing to this vertex
    for (auto &v : vertices) {
        if (v.label != label) {
            // Remove all edges pointing to the vertex to be removed
            // This is because the vertex is going to be removed
            // so we don't want any edges pointing to it
            removeEdgeFromList(v.edges, label);
        }
    }
    // Erase the vertex
    vertices.erase(vertices.begin() + idx);
    std::cout << "Removed vertex \"" << label << "\" and its incident edges.\n";
}

/**
 * \brief Adds an edge between two vertices
 * \param label1 The label of the source vertex
 * \param label2 The label of the destination vertex
 * \param weight The weight of the edge
 * \return void
 *
 * This function adds an edge between two specified vertices.  If the
 * vertices do not exist, or if an edge between them already exists,
 * the function does nothing and prints an error message.
 */
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    if (label1 == label2) {
        std::cout << "Cannot add a self‑loop on \"" << label1 << "\".\n";
        return;
    }
    int i1 = getVertexIndex(label1);
    int i2 = getVertexIndex(label2);
    if (i1 < 0 || i2 < 0) {
        std::cout << "One or both vertices do not exist.\n";
        return;
    }
    if (edgeExists(vertices[i1].edges, label2)) {
        std::cout << "Edge between \"" << label1 << "\" and \"" << label2 << "\" already exists.\n";
        return;
    }
    // Add undirected edge
    vertices[i1].edges.push_back(Edge{label2, weight});
    vertices[i2].edges.push_back(Edge{label1, weight});
    std::cout << "Added edge (" << label1 << "–" << label2 << ", weight=" << weight << ").\n";
}

/**
 * \brief Removes an edge between two vertices
 * \param label1 The label of the source vertex
 * \param label2 The label of the destination vertex
 * \return void
 *
 * This function removes an edge between two specified vertices.  If the
 * vertices do not exist, or if no edge exists between them, the function
 * does nothing and prints an error message.
 */
void Graph::removeEdge(std::string label1, std::string label2) {
    int i1 = getVertexIndex(label1);
    int i2 = getVertexIndex(label2);
    if (i1 < 0 || i2 < 0) {
        std::cout << "One or both vertices do not exist.\n";
        return;
    }
    if (!edgeExists(vertices[i1].edges, label2)) {
        std::cout << "No edge exists between \"" << label1 << "\" and \"" << label2 << "\".\n";
        return;
    }
    // Remove undirected edge
    removeEdgeFromList(vertices[i1].edges, label2);
    removeEdgeFromList(vertices[i2].edges, label1);
    std::cout << "Removed edge between \"" << label1 << "\" and \"" << label2 << "\".\n";
}

/**
 * \brief Calculates the shortest path from a start vertex to an end vertex
 * \param startLabel The label of the start vertex
 * \param endLabel The label of the end vertex
 * \param path The path from the start vertex to the end vertex
 * \return The length of the shortest path
 *
 * This function calculates the shortest path from a start vertex to an end
 * vertex using Dijkstra's algorithm.  If no path exists, the function prints an
 * error message and returns a value of std::numeric_limits<unsigned long>::max().
 */
unsigned long Graph::shortestPath(std::string startLabel,
                                  std::string endLabel,
                                  std::vector<std::string> &path) {
    const unsigned long INF = std::numeric_limits<unsigned long>::max();
    int start = getVertexIndex(startLabel);
    int end = getVertexIndex(endLabel);
    if (start < 0 || end < 0) {
        std::cout << "Start or end vertex does not exist.\n";
        return INF;
    }

    // Create a copy of the graph
    size_t n = vertices.size();
    std::vector<unsigned long> dist(n, INF);
    std::vector<int> prev(n, -1);
    std::vector<bool> used(n, false);

    // Initialize distances
    dist[start] = 0;

    // Iterate through all vertices
    for (size_t iter = 0; iter < n; ++iter) {
        int u = -1;
        unsigned long best = INF;
        // Find the vertex with the shortest distance
        for (size_t i = 0; i < n; ++i) {
            if (!used[i] && dist[i] < best) {
                best = dist[i];
                u = int(i);
            }
        }
        // If no vertex is found, break
        if (u < 0) break;
        // Mark the vertex as used
        used[u] = true;
        // If the end vertex is found, break
        if (u == end) break;

        // Iterate through all edges of the current vertex
        for (auto &e : vertices[u].edges) {
            int v = getVertexIndex(e.dest);
            // If the edge is not used and the distance is shorter than the current distance,
            // update the distance
            if (v >= 0 && !used[v] && dist[u] + e.weight < dist[v]) {
                dist[v] = dist[u] + e.weight;
                prev[v] = u;
            }
        }
    }

    // If no path is found, print an error message and return INF
    if (dist[end] == INF) {
        std::cout << "No path exists from \"" << startLabel << "\" to \"" << endLabel << "\".\n";
        return INF;
    }

    // Reconstruct path
    path.clear();
    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(vertices[at].label);
    }
    std::reverse(path.begin(), path.end());
    return dist[end];
}

/**
 * \brief Prints the current graph in a human-readable format
 *
 * Prints out the entire graph, showing each vertex and its edges
 */
void Graph::printGraph() const {
    std::cout << "Current Graph:\n";
    for (auto &v : vertices) {
        std::cout << v.label << ": ";
        // Print out all edges connected to the current vertex
        for (auto &e : v.edges) {
            // Print out the destination vertex and edge weight
            std::cout << "(" << e.dest << ", " << e.weight << ") ";
        }
        // Print a newline after each vertex
        std::cout << "\n";
    }
}

/**
 * \brief Gets the index of a vertex in the graph
 * \param label The label of the vertex to find
 * \return The index of the vertex, or -1 if not found
 *
 * This function iterates through the list of vertices and returns the index of
 * the vertex with the given label.  If no vertex is found with the given label,
 * the function returns -1.
 */
int Graph::getVertexIndex(const std::string &label) const {
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (vertices[i].label == label) return int(i);
    }
    return -1;
}


/**
 * \brief Checks if an edge exists to a specified destination label
 * \param edges The list of edges to search
 * \param destLabel The label of the destination vertex to find
 * \return True if an edge exists to the destination label, false otherwise
 *
 * This function iterates through a list of edges and checks if any edge
 * has a destination matching the specified label.
 */
bool Graph::edgeExists(const std::vector<Edge> &edges,
                       const std::string &destLabel) const {
    // Iterate through each edge in the list
    for (auto &e : edges) {
        // Check if the destination matches the specified label
        if (e.dest == destLabel) return true;
    }
    // Return false if no matching edge is found
    return false;
}

/**
 * \brief Removes an edge from a list of edges
 * \param edges The list of edges to remove from
 * \param destLabel The label of the destination vertex to remove
 *
 * This function uses the remove-erase idiom to remove all edges from the list
 * that have a destination matching the specified label.
 */
void Graph::removeEdgeFromList(std::vector<Edge> &edges,
                               const std::string &destLabel) {
    // Use the remove-erase idiom to remove all edges from the list
    // that have a destination matching the specified label
    edges.erase(
      std::remove_if(edges.begin(), edges.end(),
                     // Use a lambda to check if the edge's destination matches
                     // the specified label
                     [&](const Edge &e){ return e.dest == destLabel; }),
      edges.end());
}
