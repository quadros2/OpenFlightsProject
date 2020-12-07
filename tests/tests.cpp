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

TEST_CASE("Dijikstras algorithm works") {
    Graph a = Graph("data/airports.txt");

   //Checks invalid input
   REQUIRE(a.Dijkstra("auhrfauf") == std::unordered_map<std::string, std::pair<std::string, double>>());

   //check that airports within 800 miles have path of length 1;
   std::string airportName = "Chicago O'Hare International Airport";
   std::unordered_map<std::string, std::pair<std::string, double>> pathstest1 = a.Dijkstra(airportName);
   bool testOnePassed = true;
   for (auto elems : pathstest1) {
       if (elems.second.second < 800 && elems.second.second > 0) {
           if (elems.second.first != airportName + " -> " + elems.first) {
               testOnePassed = false;
           }
       }
   }
   REQUIRE (testOnePassed == true);
   //check that airports within 800 miles have path of length 1 (second test);
   airportName = "Nogales International Airport";
   std::unordered_map<std::string, std::pair<std::string, double>> pathstest2 = a.Dijkstra(airportName);
   bool testtwoPassed = true;
   for (auto elems : pathstest2) {
       if (elems.second.second < 800 && elems.second.second > 0) {
           if (elems.second.first != airportName + " -> " + elems.first) {
               testtwoPassed = false;
           }
       }
   }
   REQUIRE (testtwoPassed == true);
   //check that airports within 800 miles have path of length 1 (third test);
   airportName = "John F Kennedy International Airport";
   std::unordered_map<std::string, std::pair<std::string, double>> pathstest3 = a.Dijkstra(airportName);
   bool testThreePassed = true;
   for (auto elems : pathstest3) {
       if (elems.second.second < 800 && elems.second.second > 0) {
           if (elems.second.first != airportName + " -> " + elems.first) {
               testThreePassed = false;
           }
       }
   }
   REQUIRE (testOnePassed == true);
   
   //test self routes
   std::unordered_map<std::string, std::pair<std::string, double>> pathstest4 = a.Dijkstra(airportName);
   REQUIRE(pathstest4[airportName].first == "Path to " + airportName + " is a self-route!");
   airportName = "Phoenix Sky Harbor International Airport";
   std::unordered_map<std::string, std::pair<std::string, double>> pathstest5 = a.Dijkstra(airportName);
   REQUIRE(pathstest5[airportName].first == "Path to " + airportName + " is a self-route!");
   airportName = "San Francisco International Airport";
   std::unordered_map<std::string, std::pair<std::string, double>> pathstest6 = a.Dijkstra(airportName);
   REQUIRE(pathstest6[airportName].first == "Path to " + airportName + " is a self-route!");
   
   //test routes from bottom 48 states to Hawaii or Pacific islands do not work
   airportName = "Fort Lauderdale Executive Airport";
   std::unordered_map<std::string, std::pair<std::string, double>> pathstest7 = a.Dijkstra(airportName);
   REQUIRE(pathstest7["Kahului Airport"].first == 
        "Path to Kahului Airport cannot be made! (Not possible to fly Cessna from continental US to Hawaii or Pacific territories)");
    REQUIRE(pathstest7["Kaneohe Bay MCAS (Marion E. Carl Field) Airport"].first == 
        "Path to Kaneohe Bay MCAS (Marion E. Carl Field) Airport cannot be made! (Not possible to fly Cessna from continental US to Hawaii or Pacific territories)");
    REQUIRE(pathstest7["Lanai Airport"].first == 
        "Path to Lanai Airport cannot be made! (Not possible to fly Cessna from continental US to Hawaii or Pacific territories)");
}

TEST_CASE("Landmark Path Algorithm works") {
    Graph a = Graph("data/airports.txt");
    //testing invalid inputs:

    //testing that a path from origin to landmark can be made
    REQUIRE(a.landmarkPathAlgorithm("Baton Rouge Metropolitan Airport", "Lanai Airport", "Tulsa International Airport") ==
        "landmark path not possible, no path can be made from origin to landmark airport");
    REQUIRE(a.landmarkPathAlgorithm("Baton Rouge Metropolitan Airport", "Tulsa International Airport", "Lanai Airport") ==
        "landmark path not possible, no path can be made from landmark to destination airport");
    
}
