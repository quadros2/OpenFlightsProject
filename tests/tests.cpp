#include <iostream>
#include <vector>
#include <string>

#include "../tests/catch.hpp"
#include "../graph.h"
#include "../Airport.h"


TEST_CASE("Graph Properly parses full dataset") {
    Graph a = Graph("data/airports.txt");

   //Checks for correct size.
   REQUIRE (a.verticies.size() == 473);
   //Checks for adjecency functionality. 
   REQUIRE ( a.adjacencyMatrix["St Paul Island Airport"].size() == 472);
   a.insertVertex(35.0, -116.0, "my airport");
   //Checks if vertex properties are working.
   REQUIRE (a.verticies.size() == 474);
   REQUIRE ( a.adjacencyMatrix["St Paul Island Airport"].size() == 473);
   REQUIRE (a.verticies["my airport"].latitude == 35);
   REQUIRE (a.verticies["my airport"].longitude == -116);
   a.removeVertex("my airport");
   //Checking if remove reduces size of the vertex vector.
   REQUIRE(a.verticies.size() == 473);
   //Making sure the adjacency for the removed vertex is empty.
   REQUIRE(a.adjacencyMatrix["my airport"].size() == 0);
   //Checking if the adjacency for a different vertex is modified after removal. 
   REQUIRE ( a.adjacencyMatrix["St Paul Island Airport"].size() == 472);

}
