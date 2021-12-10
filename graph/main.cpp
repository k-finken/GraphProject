#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>

//comment

void readFile(Graph& graph, std::string name) {
    std::ifstream file("../" + name + ".csv");
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
        graph.insertEdgeMinimized(from, to, weight);
    }
}

void output(Graph& graph, std::vector<std::pair<std::string, int>> path) {
    // Output
    std::cout << "Printing path:" << std::endl;
    int cost = 0;
    for (int i = 0; i < path.size(); i++) {
        std::cout << path.at(i).first << std::endl;
        cost += path[i].second;
    }
    std::cout <<"\nTotal Cost: " << cost << std::endl;
    std::cout << "---------------------" << std::endl;
}



int main() {
    Graph streamers;
    readFile(streamers, "10.05.2021.13.04EDGELIST");
    readFile(streamers, "07.02.2021.02.40.42EDGELIST");
    //std::cout << streamers.count << std::endl; //Number of edges
    std::vector<std::pair<std::string, int>> path; // Debugging code
    bool running = true;
    while (running) {
        std::cout << "Welcome to the Twitch.tv shortest path visualizer!" << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "This application allows you to enter the name of two streamers\nand find the shortest path of shared chatters between them" << std::endl;
        std::cout << "Menu options: " << std::endl;
        std::cout << "1. Dijkstra's Algorithm" << std::endl;
        std::cout << "2. Bellman-Ford Algorithm" << std::endl;
        std::cout << "3. Quit application" << std::endl;
        int choice;
        std::cin >> choice;
        std::string sourceStreamer;
        std::string targetStreamer;
        switch (choice) {
        case 1:
            std::cout << "Please enter the name of the first streamer you'd like as the source for the search" << std::endl;
            std::cin >> sourceStreamer;
            std::cout << "Please enter the name of the second streamer youd like as the target for the search" << std::endl;
            std::cin >> targetStreamer;
            path = streamers.dijkstra(sourceStreamer, targetStreamer);
            output(streamers, path);
            break;
        case 2:
            std::cout << "Please enter the name of the first streamer you'd like as the source for the search" << std::endl;
            std::cin >> sourceStreamer;
            std::cout << "Please enter the name of the second streamer youd like as the target for the search" << std::endl;
            std::cin >> targetStreamer;
            path = streamers.bellmanFord(sourceStreamer, targetStreamer);
            output(streamers, path);
            break;
        case 3:
            std::cout << "Thanks for using the Twitch.tv shortest path visualizer!" << std::endl;
            running = false;
            break;
        default:
            std::cout << "Invalid entry! Please enter a valid menu option between 1-3" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            break;
        }
    }
    return 0;
}