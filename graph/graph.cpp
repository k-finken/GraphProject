#include "graph.h"

void Graph::insertEdge(std::string from, std::string to, int weight) {
    if (!graph[from].count(to)) {
        graph[from][to] = weight;
        count++;
    }
    if (!graph.count(to)) { //If adjacency list doesn't have To vertex, add it in
        std::map<std::string, int> list;
        graph[to] = list;
    }
}

bool Graph::isEdge(std::string from, std::string to) {
    return graph[from].count(to);
}

int Graph::getWeight(std::string from, std::string to) {
    return graph[from][to];
}

std::vector<std::string> Graph::getAdjacent(std::string name) {
    std::vector<std::string> adjacent;
    for (auto it = graph[name].begin(); it != graph[name].end(); ++it) {
        adjacent.push_back((*it).first); //Push back adjacent streamers to vector
    }
    return adjacent;
}

std::vector<std::pair<std::string, int>> Graph::dijkstra(std::string from, std::string to) {
    std::vector<std::pair<std::string, int>> path;
    std::map<std::string, std::pair<int, std::string>> distances; // Stores the target vertex first, and then stores a pair containing the total distance and the preceding node to achieve that distance.
    std::set<std::string> visited; // Set containing all completed/visited vertices
    std::queue<std::string> vertices; // Queue of vertices to visit
    
    distances[from] = std::make_pair(0, from);
    //int size = this->graph.size(); // Number of vertices

    for (auto iter = this->graph.begin(); iter != this->graph.end(); ++iter) {
        if (iter->first != from) { // If the vertex name != the starting vertex
            distances[iter->first] = std::make_pair(2147483647, "");
        }

    }

    return path;
}

std::vector<std::pair<std::string, int>> Graph::bellmanFord(std::string from, std::string to) {
    std::vector<std::pair<std::string, int>> path;

    return path;
}

