#pragma once
#include "Airport.h"
#include <string>
#include <vector>
#include <unordered_map>
using std::string;

/**
 * Graph class is the data structure used to connect and parse OpenFlights dataset.
 * 
 */
class Graph {
    public:
        // Default constructor
        Graph();
        // Modified constructor that takes in a name
        Graph(std::string fileName);
        // Creates an Airport object and adds it to the graph
        void insertVertex(double latitude, double longit, string name);
        // Removes an Airport object from the graph data structure
        void removeVertex(string airportName);
        // Returns a vector of airport names in the order they were traversed using breadth-first.
        std::vector<std::string> BFS(std::string start);
        // Returns an unordered map with key as the destination, and pair as value. 
        // First value in pair is the path, second is distance.
        std::unordered_map<std::string, std::pair<std::string, double>> Dijkstra(std::string source);
        // Returns the shortest distance from one airport to another through a third distinct location.
        std::string landmarkPathAlgorithm(std::string start, std::string landmark, std::string destination);

        // Stores all the vertices, which are Airport objects and their names
        std::unordered_map<std::string, Airport> verticies;
        // Stores the Airports and the edges between various airports.
        std::unordered_map<std::string, std::unordered_map<std::string, double>> adjacencyMatrix;
        
    private:     
};