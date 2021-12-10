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
        graph.insertEdge(from, to, weight);
    }
}

void readFileMinimized(Graph& graph, std::string name) {
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
    if (path.size() == 0) {
        std::cout << "At least one of the streamers entered does not exist in the dataset, or there are no shared chatters between them" << std::endl;
    }
    for (int i = 0; i < path.size(); i++) {
        std::cout << path.at(i).first << std::endl;
    }

    if (path.size() > 0) {
        int degreesOfSeparation = path.size() - 1;
        std::cout <<"\nDegrees of separation: " << degreesOfSeparation << std::endl;
    }
    
    std::cout << "---------------------" << std::endl;
}



int main() {
    Graph streamers; //Graph with ~2.8k vertices and ~200k edges
    Graph streamers2; //Graph with ~2k vertices and ~5k edges
    readFile(streamers, "10.05.2021.13.04EDGELIST");
    readFile(streamers, "07.02.2021.02.40.42EDGELIST");

    //Uncomment to test smaller data set
    readFileMinimized(streamers2, "10.05.2021.13.04EDGELIST");
    readFileMinimized(streamers2, "07.02.2021.02.40.42EDGELIST");
    //std::cout << streamers.count << std::endl; //Number of edges
    //std::cout << streamers.graph.size() << std::endl; //Number of vertices
    //std::cout << streamers2.count << std::endl; //Number of edges
    //std::cout << streamers2.graph.size() << std::endl; //Number of vertices
    std::vector<std::pair<std::string, int>> path; // Debugging code
    bool running = true;
    std::cout << "Welcome to the Twitch.tv shortest path visualizer!" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "This application allows you to enter the name of two streamers\nand find the shortest path of shared chatters between them" << std::endl;
    while (running) {
        std::cout << "Choose which data set to use:" << std::endl;
        std::cout << "1. Full data set: ~2.8k vertices, ~250k edges" << std::endl;
        std::cout << "2. Small data set: ~2.5k vertices, ~5k edges" << std::endl;
        int choice;
        std::cin >> choice;
        std::string sourceStreamer;
        std::string targetStreamer;
        std::cout << "Menu option: " << std::endl;
        bool exit = false;
        if (choice == 1) {
            while (!exit) {
                std::cout << "1. Dijkstra's Algorithm" << std::endl;
                std::cout << "2. Bellman-Ford Algorithm" << std::endl;
                std::cout << "3. Choose Data Set" << std::endl;
                std::cout << "4. Quit application" << std::endl;
                std::cin >> choice;
                switch (choice) {
                    case 1:
                        std::cout << "Please enter the name of the first streamer you'd like as the source for the search" << std::endl;
                        std::cin >> sourceStreamer;
                        std::cout << "Please enter the name of the second streamer youd like as the target for the search" << std::endl;
                        std::cin >> targetStreamer;
                        path = streamers.dijkstra(sourceStreamer, targetStreamer);
                        //path = streamers2.bellmanFord(sourceStreamer, targetStreamer);
                        //output(streamers2, path);
                        output(streamers, path);
                        break;
                    case 2:
                        std::cout << "Disclaimer: Running the Bellman-Ford algorithm will take a extremely long time. Continue? (1:Y / 2:N)" << std::endl;
                        std::cin >> choice;
                        if (choice != 1)
                            continue;
                        std::cout << "Please enter the name of the first streamer you'd like as the source for the search" << std::endl;
                        std::cin >> sourceStreamer;
                        std::cout << "Please enter the name of the second streamer youd like as the target for the search" << std::endl;
                        std::cin >> targetStreamer;
                        path = streamers.bellmanFord(sourceStreamer, targetStreamer);
                        //path = streamers2.bellmanFord(sourceStreamer, targetStreamer);
                        //output(streamers2, path);
                        output(streamers, path);
                        break;
                    case 3:
                        exit = true;
                        break;
                    case 4:
                        std::cout << "Thanks for using the Twitch.tv shortest path visualizer!" << std::endl;
                        running = false;
                        exit = true;
                        break;
                    default:
                        std::cout << "Invalid entry! Please enter a valid menu option.\n" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        break;
                }
            }
        }
        else if (choice == 2) {
            while (!exit) {
                std::cout << "1. Dijkstra's Algorithm" << std::endl;
                std::cout << "2. Bellman-Ford Algorithm" << std::endl;
                std::cout << "3. Choose Data Set" << std::endl;
                std::cout << "4. Quit application" << std::endl;
                std::cin >> choice;
                switch (choice) {
                    case 1:
                        std::cout << "Please enter the name of the first streamer you'd like as the source for the search" << std::endl;
                        std::cin >> sourceStreamer;
                        std::cout << "Please enter the name of the second streamer youd like as the target for the search" << std::endl;
                        std::cin >> targetStreamer;
                        path = streamers2.dijkstra(sourceStreamer, targetStreamer);
                        output(streamers2, path);
                        break;
                    case 2:
                        std::cout << "Please enter the name of the first streamer you'd like as the source for the search" << std::endl;
                        std::cin >> sourceStreamer;
                        std::cout << "Please enter the name of the second streamer youd like as the target for the search" << std::endl;
                        std::cin >> targetStreamer;
                        path = streamers2.bellmanFord(sourceStreamer, targetStreamer);
                        output(streamers2, path);
                        break;
                    case 3:
                        exit = true;
                        break;
                    case 4:
                        std::cout << "Thanks for using the Twitch.tv shortest path visualizer!" << std::endl;
                        running = false;
                        exit = true;
                        break;
                    default:
                        std::cout << "Invalid entry! Please enter a valid menu option.\n" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        break;
                }
            }
        }
        else {
            std::cout << "Invalid entry! Please enter a valid menu option.\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
    }
    return 0;
}