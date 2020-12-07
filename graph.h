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
        std::unordered_map<std::string, std::pair<std::string, double>> Dijkstra(std::string source);
        std::string landmarkPathAlgorithm(std::string start, std::string landmark, std::string destination);
        std::unordered_map<std::string, Airport> verticies;
        void DFS(std::string start);
        std::unordered_map<std::string, std::unordered_map<std::string, double>> adjacencyMatrix;
    private:     
};