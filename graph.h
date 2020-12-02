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
        std::vector<Airport> incidentEdges(Airport & airport);
        bool areAdjacent(Airport one, Airport two);
        std::unordered_map<std::string, Airport> verticies;
        std::unordered_map<std::string, std::unordered_map<std::string, double>> adjacencyMatrix;
    private:     
};