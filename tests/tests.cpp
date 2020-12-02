#include <iostream>
#include <vector>
#include <string>

#include "../tests/catch.hpp"
#include "../graph.h"
#include "../Airport.h"


TEST_CASE("Graph Properly parses full dataset") {
    Graph a = Graph("data/airports.txt");
    //make a graph of the data and see if it makes correct verticies.
    /**
    REQUIRE (a.verticies.at(200).name == "\"Southeast Texas Regional Airport\"");
    REQUIRE (a.verticies.at(347).name == "\"John Glenn Columbus International Airport\"");
    REQUIRE (a.verticies.at(418).name == "\"Chicago O'Hare International Airport\"");

    REQUIRE (a.verticies.at(167).latitude == 41.16350173950195);
    REQUIRE (a.verticies.at(419).latitude == 26.3784999847);
    REQUIRE (a.verticies.at(449).latitude == 29.99340057373047);

    REQUIRE (a.verticies.at(357).longitude == -80.6343994141);
    REQUIRE (a.verticies.at(470).longitude == -147.6139984);
    REQUIRE (a.verticies.at(125).longitude == -100.288002014);
    //makes sure every datapoint is converted to an airport vertex (473 datapoints in our dataset).
    REQUIRE (a.verticies.size() == 473);    
    **/
}
