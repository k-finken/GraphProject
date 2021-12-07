#include "graph.h"

void Graph::insertEdge(std::string from, std::string to, int weight) {
    graph[from][to] = weight;
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




