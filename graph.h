#pragma once
#include "Airport.h"
#include <string>
#include <vector>

class Graph {
    public:
        Graph();
        Graph(std::string fileName);
        void insertVertex(Airport airport);
        void insertEdge(Airport origin, Airport destination);
        void removeVertex(Airport airport);
        void removeEdge(Airport origin, Airport destination);
        std::vector<Airport> incidentEdges(Airport & airport);
        bool areAdjacent(Airport one, Airport two);
        std::vector<Airport> verticies;
    private:     
};