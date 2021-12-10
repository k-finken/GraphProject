#include "graph.h"

void Graph::insertEdge(std::string from, std::string to, int weight) {
    if (!graph[from].count(to)) { //Bidirectional weighted graph
        graph[from][to] = weight;
        graph[to][from] = weight;
        invertedGraph[from][to] = 1.0 / weight;
        invertedGraph[to][from] = 1.0 / weight;
        count++;
    }
}

void Graph::insertEdgeMinimized(std::string from, std::string to, int weight) {
    if (graph[from].size() < 3) {
        graph[from][to] = weight;
        graph[to][from] = weight;
        invertedGraph[from][to] = 1.0 / weight;
        invertedGraph[to][from] = 1.0 / weight;
        count++;
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

// Use invertedGraph so that a high number of chatters counts as the shorter path, and low chatters count as longer paths
std::vector<std::pair<std::string, int>> Graph::dijkstra(std::string from, std::string to) {
    std::vector<std::pair<std::string, int>> path; // Will store the final path between 'from' and 'to', with each int representing the weight required to reach the current node from the previous node (first element weight is 0)
    std::map<std::string, std::pair<double, std::string>> distances; // Stores the target vertex first, and then stores a pair containing the total distance and the preceding node to achieve that distance.
    std::set<std::string> visited; // Set containing all completed/visited vertices
    std::set<std::string> vertices; // Set of vertices to visit
    // Initialize the distance from 'from' to 'from' equal to 0, hence forcing it to to be the starting node for Dijkstra's
    distances[from] = std::make_pair(0, from);
    vertices.insert(from);

    // Add all other vertices (everything excluding 'from') with distance = infinity (using numeric_limits<double>::infinity()) to the set of vertices to be checked
    for (auto iter = this->invertedGraph.begin(); iter != this->invertedGraph.end(); ++iter) {
        if (iter->first != from) { // If the vertex name != the starting vertex
            distances[iter->first] = std::make_pair(std::numeric_limits<double>::infinity(), "");
            vertices.insert(iter->first);
        }
    }

    if (this->graph.count(from) == 0 || this->graph.count(to) == 0) { // If either vertex doesn't exist in the graph, return now with an empty path
        return path;
    }
    // Main Dijkstra's execution
    while (vertices.size() != 0) {
        //std::cout << vertices.size() << std::endl; //Remove if you get std::bad_alloc error
        // Select next vertex to visit by finding the vertex with the shortest distance to it
        double minimumDist = std::numeric_limits<double>::infinity();
        std::string vertex;
        for (auto iter = vertices.begin(); iter != vertices.end(); ++iter) { // Loop through all remaining vertices and find the vertex 
            std::string current = *iter;
            if (distances[current].first < minimumDist) {
                vertex = current;
                minimumDist = distances[current].first;
            }
        }

        // Iterate over all adjacents to the current vertex
        for (auto iter = this->invertedGraph[vertex].begin(); iter != this->invertedGraph[vertex].end(); ++iter) {
            if (visited.count(iter->first) != 0) { // If the current adjacent has already been visited/completed, skip to the next iteration
                continue;
            }

            double newDistance = distances[vertex].first + iter->second; // Distance to reach current vertex + distance to the adjacent vertex in question = newDistance
            if (newDistance < distances[iter->first].first) { // If the newDistance is less than 
                distances[iter->first].first = newDistance;
                distances[iter->first].second = vertex;
            }
        }
        
        vertices.erase(vertex); // Remove the current vertex from the list of vertices to be visited, since it has just been visited
        visited.insert(vertex); // Add the current vertex to the set of visited vertices
        if (vertex == "") { // Once there are no more connected vertices left, end main Dijkstra's execution (? not sure if this is necessary)
            break;
        }
    }

    // Trace path backwards from the end to the start, necessarily taking the shortest path in the process
    // Additionally, get weights from the original graph, not inverted weights, so the path makes sense when returned
    std::vector<std::pair<std::string, int>> pathInverted;
    std::string currentVertex = to;
    while (currentVertex != from) {
        // Get source vertex to reach current vertex on the shortest path
        std::string sourceVertex = distances[currentVertex].second;
        // Go to original graph and find the edge in question--the edge from a source vertex to currentVertex--and get the weight
        int weight = this->graph[sourceVertex][currentVertex];
        // Create pair containing the currentVertex and the weight/cost it takes to reach the current vertex from the previous/source vertex, and add this pair to the path vector
        pathInverted.push_back(std::make_pair(currentVertex, weight));
        // Set the currentVertex to the sourceVertex so that the shortest path can be traced backwards by another step
        currentVertex = sourceVertex;
    }
    pathInverted.push_back(std::make_pair(from, 0)); // Since the distance from any node to itself is zero, and 'from' is the starting node, just add 'from' with 0 weight

    //Invert path so path starts at 'from' and ends on 'to'
    int pathSize = pathInverted.size();
    for (int i = pathSize - 1; i >= 0; i--) {
        path.push_back(pathInverted.at(i));
    }

    return path;
}

std::vector<std::pair<std::string, int>> Graph::bellmanFord(std::string from, std::string to) {
    int vertices = invertedGraph.size();
    std::map<std::string, double> distances; //Distance from source vertex to all vertices
    std::map<std::string, std::string> previous; //Predecessor vertex in path
    distances[from] = 0; //Setting source vertex distance to 0
    previous[from] = "";
    std::vector<std::pair<std::string, int>> path;

    for (auto iter = invertedGraph.begin(); iter != invertedGraph.end(); ++iter) {
        if (iter->first != from) { // If the vertex name != the starting vertex
            distances[iter->first] = INT_MAX;
        }
    }

    //Bellman Ford Algorithm
    for (int i = 0; i < vertices - 1; i++) { //Do the below operations |V| - 1 times
        for (auto iter = invertedGraph.begin(); iter != invertedGraph.end(); ++iter) { //For every edge (U,V)
            for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2) {
                double tempDistance = distances[iter->first] + invertedGraph[iter->first][iter2->first]; //If distance(V) > distance(U) + weight(U,V), apply relaxaion
                if (tempDistance < distances[iter2->first]) {
                    distances[iter2->first] = tempDistance;
                    previous[iter2->first] = iter->first;
                }
            }
        }
    }

    //Testing for negative weights. No negative weights in data set, so code is unnecessary
    // for (auto iter = graph.begin(); iter != graph.end(); ++iter) { //Iterate through every edge
    //     for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2) {
    //         if ((distances[iter2->first] + getWeight(iter->first, iter2->first)) < distances[iter->first]) //If distance(U) + weight(U,V) < distance(V), there is a negative edge
    //             std::cout << "Negative Edge Cycle Exists" << std::endl;
    //     }
    // }

    //Find the path from source vertex to target vertex
    std::string current = to;
    while (current != "") {
        path.push_back(std::make_pair(current,getWeight(current,previous[current])));
        current = previous[current];
    }
    
    std::reverse(path.begin(), path.end());
    return path;
}

