#include "graph.h"
#include "Airport.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <stack>
#include <queue>

Graph::Graph() {
    
}

Graph::Graph(std::string fileName) {
    
    // This part reads each line and stores each line of the data in a vector of strings.
    // Reading txt file line by line from 
    // https://thispointer.com/c-how-to-read-a-file-line-by-line-into-a-vector/
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<std::string> vecOfStrs;
    std::ifstream in(fileName.c_str());
    if(!in) 
    {
        std::cerr << "Cannot open the File : "<< fileName << std::endl;
    }
    std::string str;
    while (std::getline(in, str))
    {
        if(str.size() > 0)
            vecOfStrs.push_back(str);
    }
    in.close();
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<Airport> tempVerticies;
    // This part converts the vector of string lines into airport objects and stores it in the 
    // verticies vector.
    for (unsigned i = 0; i < vecOfStrs.size(); i++) {
        // Grab the string at index i
        std::string data = vecOfStrs.at(i);
        // Find the first and second comma
        std::vector<std::string> result;

        // Code used to split a string from the commas is borrowed from 
        // https://www.tutorialspoint.com/parsing-a-comma-delimited-std-string-in-cplusplus
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::stringstream s_stream(data); // Create string stream from the string
        while(s_stream.good()) {
            std::string substr;
            getline(s_stream, substr, ','); // Get first string delimited by comma
            result.push_back(substr);
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // The important information is being pulled out of each line, converted into airport objects.
        double latitude = std::stod(result.at(result.size() - 8));
        double longitude = std::stod(result.at(result.size() - 7));
        std::string name = result.at(1);
        // Removing quotation mark characters
        name.erase(name.size() - 1);
        name.erase(name.begin());

        // Creates an airport and puts it in a verticies unordered map.
        Airport airport = Airport(latitude, longitude, name);
        verticies[name] = airport;
        
        tempVerticies.push_back(airport);

    }

    // Code for creating edges
    for (unsigned i = 0; i < tempVerticies.size(); i++) {
        for (unsigned j = 0; j < tempVerticies.size(); j++) {
            // Avoiding self edges
            if (j == i) {
                continue;
            }

            Airport airportOne = tempVerticies.at(i);
            Airport airportTwo = tempVerticies.at(j);
            // According to usgs.gov, one degree of latitude is ~69 miles, one degree of longitude 
            // is ~54.6 miles
            double distance = sqrt(pow((airportOne.longitude - airportTwo.longitude) * 54.6, 2) 
                + pow((airportOne.latitude - airportTwo.latitude) * 69, 2));
            // Only adding edges between airports that are within 800 nautical miles
            if (distance < 800) {
                adjacencyMatrix[airportOne.name][airportTwo.name] = distance;
            } else {
                adjacencyMatrix[airportOne.name][airportTwo.name] = 0;
            }
        }
    }
}

void Graph::insertVertex(double latitude, double longitude, std::string airportName) {
    Airport airport = Airport(latitude, longitude, airportName);
    // If vertex does not exist already, add it and make empty entry in adjancy matrix.
    if (verticies.find(airportName) == verticies.end()) {
        verticies[airportName] = airport;
        adjacencyMatrix[airportName] = std::unordered_map<std::string, double>();
    }
    // Insert edges that can be made by new vertex
    for (auto i = verticies.begin(); i != verticies.end(); i++) {
        Airport airportTwo = i->second;
        if (airportTwo.name == airport.name) {
            continue;
        }
        double distance = sqrt(pow((airport.longitude - airportTwo.longitude) * 54.6, 2) 
            + pow((airport.latitude - airportTwo.latitude) * 69, 2));
        if (distance < 800) {
            adjacencyMatrix[airport.name][airportTwo.name] = distance;
            adjacencyMatrix[airportTwo.name][airport.name] = distance;
        } else {
            adjacencyMatrix[airport.name][airportTwo.name] = 0;
            adjacencyMatrix[airportTwo.name][airport.name] = 0;
        }
    }

}

// Logic borrowed from graph.h in lab_ml
void Graph::removeVertex(std::string airportName) {
    if (adjacencyMatrix.find(airportName) != adjacencyMatrix.end()) {
        for (auto it = adjacencyMatrix[airportName].begin(); it != adjacencyMatrix[airportName].end(); it++) {
            std::string u = it->first;
            adjacencyMatrix[u].erase(airportName); 
        }
        
        adjacencyMatrix.erase(airportName);
        for(auto it2 = adjacencyMatrix.begin(); it2 != adjacencyMatrix.end(); it2++) {
            std::string u = it2->first;
            if (it2->second.find(airportName) != it2->second.end()) {
                it2->second.erase(airportName);
            }
        }

        verticies.erase(airportName);
    }
}

// Pseudocode used to develope Dijkstra's algorithm: https://courses.cs.washington.edu/courses/cse326/00wi/handouts/lecture22/sld014.htm

std::unordered_map<std::string, std::pair<std::string, double>> Graph::Dijkstra(std::string source) {
    std::unordered_map<std::string, double> distanceFromSource;
    std::unordered_map<std::string, bool> visited; 
    // Look at mp_mazes and create up tree of verticies to track paths                           
    std::unordered_map<std::string, std::string> parent;
    // Source vertex doesn't exist
    if (verticies.find(source) == verticies.end()) {
        return std::unordered_map<std::string, std::pair<std::string, double>>();
    }
    // Set up all possible verticies and paths with default values
    for (auto elem : verticies) {
        distanceFromSource[elem.first] = 9999999; // 9999999 = infinity in this case
        visited[elem.first] = false;
        parent[elem.first] = "Unavailable"; 
    }
    // Initializing the cost of the source node to zero
    distanceFromSource[source] = 0;
    // Iterating through every unknown node in the graph            
    for (auto elem : verticies) {
        // Set min to infinite until node with lower cost is found
        double min = 9999999; 
        std::string airportName;
        // Finding node that hasn't been visited and is at the lowest cost, and lower than current min  
        for (auto elem : distanceFromSource) {
            if (visited[elem.first] == false && distanceFromSource[elem.first] <= min) {
                min = distanceFromSource[elem.first];
                airportName = elem.first;
            }
        }
        // Marking current node as known
        visited[airportName] = true;
        // For each node elems which is adjacent to airport name...
        for (auto elems : verticies) {
            // Checking that elems is adjacent to airportname and hasn't been visited
            if(!visited[elems.first] && adjacencyMatrix[airportName][elems.first]) {
                // Adjacent vertex cost will remain the same or be change to (adjacent node's cost) 
                // + (cost of adjacencyMatrix[airportName][elems.first])
                if (distanceFromSource[airportName] + adjacencyMatrix[airportName][elems.first] < 
                    distanceFromSource[elems.first]) {
                    // Treat like a disjoint set-vector without path compression
                    parent[elems.first] = airportName;
                    distanceFromSource[elems.first] = distanceFromSource[airportName] + 
                        adjacencyMatrix[airportName][elems.first];
                }
            }
        }
    }
    std::unordered_map<std::string, std::pair<std::string, double>> paths;
    // Printing paths
    for (auto elem : verticies) {
        paths[elem.first].second = distanceFromSource[elem.first];
        std::string airp = elem.first;
        std::string arrow = " -> ";
        std::stack<std::string> stack;
        stack.push(airp);
        while (parent[airp] != "Unavailable") {
            stack.push(parent[airp]);
            airp = parent[airp];
        }
        std::string path = "";
        while (!stack.empty()) {
            path += stack.top();
            if (stack.size() != 1) {
                path += arrow;
            }
            stack.pop();
        }
        paths[elem.first].first = path;
        if (paths[elem.first].second == 9999999) {
            paths[elem.first].first = "Path to " + elem.first +
            " cannot be made! (Cessna can't fly from continental US to Hawaii or Pacific territories)";
        }
        if (paths[elem.first].second == 0) {
            paths[elem.first].first = "Path to " + elem.first +
            " is a self-route!";
        }
    }
    std::ofstream outputfile;
    outputfile.open("Dijkstra's Algorithm Output");
    for (auto elems : paths) {
        outputfile << "Path: " + elems.second.first << std::endl;
        outputfile << "Distance: " << elems.second.second << std::endl;
        outputfile << " " << std::endl;
    }
    return paths;
}

// No psuedocode used to develop algorithm
std::string Graph::landmarkPathAlgorithm(std::string start, std::string landmark, std::string destination) {
    if (verticies.find(start) == verticies.end()) {
        return "Origin airport does not exist.";
    }
    if (verticies.find(landmark) == verticies.end()) {
        return "Landmark airport does not exist.";
    } 
    if (verticies.find(destination) == verticies.end()) {
        return "Destination airport does not exist.";
    }  
    // Find shortest path from start to landmark
    std::unordered_map<std::string, std::pair<std::string, double>> pathsFromOrigin = Dijkstra(start);
    // Find shortest path from landmark to destination
    std::unordered_map<std::string, std::pair<std::string, double>> pathsFromLandmark = Dijkstra(landmark);
    if (pathsFromOrigin[landmark].second == 9999999) {
        return "Landmark path not possible, no path can be made from origin to landmark airport.";
    }
    if (pathsFromLandmark[destination].second == 9999999) {
        return "Landmark path not possible, no path can be made from landmark to destination airport.";
    }
    std::ofstream outputfile;
    outputfile.open("Landmark Path Algorithm Output");
    outputfile << "Origin Airport to Landmark: " + pathsFromOrigin[landmark].first + "\n" + 
        "Landmark Airport to Destination: " + pathsFromLandmark[destination].first << std::endl;
    return "Origin Airport to Landmark: " + pathsFromOrigin[landmark].first + "\n" + 
        "Landmark Airport to Destination: " + pathsFromLandmark[destination].first;
}

// Pseudocode found on the CS225 website
std::vector<std::string> Graph::BFS(std::string startAirport) {
    std::vector<std::string> order;
    if (verticies.find(startAirport) == verticies.end()) {
        order.push_back("Origin airport does not exist.");
        return order;
    }
    std::unordered_map<std::string, bool> visited;
    // Keeping track of all visited verticies;
    for (auto elem : verticies) {
        visited[elem.first] = false;
    }
    // Vector to keep track of the traversal order
    std::queue<std::string> processor;
    processor.push(startAirport);
    visited[startAirport] = true;
    order.push_back(startAirport);
    // int sum = 1;
    while (!processor.empty()) {
        startAirport = processor.front();
        processor.pop();
        // int count = 0;
        for (auto elem : adjacencyMatrix[startAirport]) {
            if (!visited[elem.first] && elem.second != 0) {
                visited[elem.first] = true;
                order.push_back(elem.first);
                processor.push(elem.first);
                //count++;
            }
        }
        // sum += count;
    }
    std::ofstream outputfile;
    outputfile.open("BFS Algorithm Output");
    outputfile << "NODES VISITED IN ORDER:" << std::endl;
    for (unsigned i = 0; i < order.size(); i++) {
        outputfile << i << ". " << order.at(i) << std::endl;
    }
    return order;
    // std::cout << sum << std::endl;
}