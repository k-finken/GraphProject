#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>

void readFile(Graph& graph) {
    std::ifstream file("../10.05.2021.13.04EDGELIST.csv");
    std::string line;
    std::getline(file, line); //Header info
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string from, to, weightStr;
        int weight;

        std::getline(stream, from, ',');
        std::getline(stream, to, ',');
        std::getline(stream, weightStr);
        //Converting to int weight
        weight = std::stoi(weightStr);
        //Inserting into graph
        graph.insertEdge(from, to, weight);
    }
}

int main() {
    Graph streamers;
    readFile(streamers);
    std::cout << streamers.graph["GUANYAR"]["Llobeti4"] << std::endl; //Test
    return 0;
}