#include <iostream>
#include "graph.h"
#include "Airport.h"
#include <vector>
#include <string>
#include <unordered_map>

int main() {
    
    Graph a("data/airports.txt");
    std::cout << a.verticies.size() << std::endl;
    a.insertVertex(35.0, -116.0, "my airport");
    std::cout << a.verticies["my airport"].latitude << std::endl;
    std::cout << a.verticies.size() << std::endl;
    std::cout << a.adjacencyMatrix["St Paul Island Airport"].size() << std::endl;
    a.removeVertex("my airport");
    std::cout << a.verticies.size() << std::endl;
    std::cout << a.adjacencyMatrix["my airport"].size() << std::endl;
    std::cout << a.adjacencyMatrix["St Paul Island Airport"].size() << std::endl;

    return 0;
    
}
