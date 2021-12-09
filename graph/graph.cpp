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

// Change all weights from the original graph to be 1/weight so that a high number of chatters counts as the shorter path, and low chatters count as longer paths
std::vector<std::pair<std::string, int>> Graph::dijkstra(std::string from, std::string to) {
    // Generate inverted version of the graph with new weight = 1 /original weight so that a path between two streamers is "shorter" if they have more shared viewers
    // *** Optimization: May want to store an inverted copy of the graph in the Graph object itself, so this doesn't have to be recalculated for every search
    std::map<std::string, std::map<std::string, double>> invertedGraph;
    for (auto iter = this->graph.begin(); iter != this->graph.end(); ++iter) {
        std::map<std::string, double> temp;
        for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2) {
            temp[iter2->first] = 1 / iter2->second;
        }
        invertedGraph[iter->first] = temp;
    }

    std::vector<std::pair<std::string, int>> path; // Will store the final path between 'from' and 'to', with each int representing the weight required to reach the current node from the previous node (first element weight is 0)
    std::map<std::string, std::pair<double, std::string>> distances; // Stores the target vertex first, and then stores a pair containing the total distance and the preceding node to achieve that distance.
    std::set<std::string> visited; // Set containing all completed/visited vertices
    std::set<std::string> vertices; // Set of vertices to visit
    // Initialize the distance from 'from' to 'from' equal to 0, hence forcing it to to be the starting node for Dijkstra's
    distances[from] = std::make_pair(0, from);
    vertices.insert(from);

    // Add all other vertices (everything excluding 'from') with distance = infinity (using numeric_limits<double>::infinity()) to the set of vertices to be checked
    for (auto iter = invertedGraph.begin(); iter != invertedGraph.end(); ++iter) {
        if (iter->first != from) { // If the vertex name != the starting vertex
            distances[iter->first] = std::make_pair(std::numeric_limits<double>::infinity(), "");
            vertices.insert(iter->first);
        }
    }

    // Main Dijkstra's execution
    while (vertices.size() != 0) {
        std::cout << vertices.size() << std::endl;
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
        for (auto iter = invertedGraph[vertex].begin(); iter != invertedGraph[vertex].end(); ++iter) {
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
    std::vector<std::pair<std::string, int>> path;

    return path;
}

