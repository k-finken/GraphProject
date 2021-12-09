#include <string>
#include <map>
#include <vector>
#include <utility>
#include <set>
#include <queue>
#include <iostream>
#include <limits>

struct Graph {
    int count = 0; //For debugging
    std::map<std::string, std::map<std::string, int>> graph; //Adjacency List: <streamer, list of adjacent streamers with weights>

    void insertEdge(std::string from, std::string to, int weight);
    bool isEdge(std::string from, std::string to);
    int getWeight(std::string from, std::string to);
    std::vector<std::string> getAdjacent(std::string name);
    std::vector<std::pair<std::string, int>> dijkstra(std::string from, std::string to);
    std::vector<std::pair<std::string, int>> bellmanFord(std::string from, std::string to);
};
