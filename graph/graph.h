#include <string>
#include <map>
#include <vector>


class Graph {
    std::map<std::string, std::map<std::string, int>> graph; //Adjacency List: <streamer, list of adjacent streamers with weights>
public:
    void insertEdge(std::string from, std::string to, int weight);
    bool isEdge(std::string from, std::string to);
    int getWeight(std::string from, std::string to);
    std::vector<std::string> getAdjacent(std::string name);
}
