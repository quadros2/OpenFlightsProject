#pragma once
#include "Airport.h"
#include <string>
#include <vector>
#include <unordered_map>
using std::string;
class Graph {
    public:
        Graph();
        Graph(std::string fileName);
        void insertVertex(double latitude, double longit, string name);
        void removeVertex(string airportName);
        //returns a vector of airport names the traversal visited in order.
        std::vector<std::string> BFS(std::string start);
        //returns an unordered map with key as the destination, and pair as value. first value in pair is the path, second is distance.
        std::unordered_map<std::string, std::pair<std::string, double>> Dijkstra(std::string source);
        //returns the shortest distance from one airport to another through a third distinct location.
        std::string landmarkPathAlgorithm(std::string start, std::string landmark, std::string destination);
        std::unordered_map<std::string, Airport> verticies;
        std::unordered_map<std::string, std::unordered_map<std::string, double>> adjacencyMatrix;
    private:     
};