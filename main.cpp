#include <iostream>
#include "graph.h"
#include "Airport.h"
#include <vector>
#include <string>
#include <unordered_map>

int main() {
    Graph a("data/airports.txt");
    std::cout << a.verticies.size() << std::endl;
    return 0;
}