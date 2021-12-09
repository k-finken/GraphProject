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

std::vector<std::pair<std::string, int>> Graph::djikstra(std::string from, std::string to) {
    std::vector<std::pair<std::string, int>> path;

    return path;
}

std::vector<std::pair<std::string, int>> Graph::bellmanFord(std::string from, std::string to) {
    std::vector<std::pair<std::string, int>> path;

    return path;
}

