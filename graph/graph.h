#include <string>
#include <map>
#include <vector>
#include <utility>

struct Graph {
    std::map<std::string, std::map<std::string, int>> graph; //Adjacency List: <streamer, list of adjacent streamers with weights>
    void insertEdge(std::string from, std::string to, int weight);
    bool isEdge(std::string from, std::string to);
    int getWeight(std::string from, std::string to);
    std::vector<std::string> getAdjacent(std::string name);
    std::vector<std::pair<std::string, int>> djikstra(std::string from, std::string to);
    std::vector<std::pair<std::string, int>> bellmanFord(std::string from, std::string to);
};
