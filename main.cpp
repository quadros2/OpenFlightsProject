#include <iostream>
#include "graph.h"
#include "Airport.h"
#include <vector>
#include <string>

int main() {
    Graph a = Graph("data/airports.txt");
    std::cout << a.verticies.size() << std::endl;
    std::cout << a.verticies.at(200).name << std::endl;
    std::cout << a.verticies.at(167).latitude << std::endl;
    std::cout << a.verticies.at(357).longitude << std::endl;
}