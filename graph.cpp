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

Graph::Graph() {
    
}

Graph::Graph(std::string fileName) {
    
    //this part reads each line and stores each line of the data in a vector of strings.
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

    std::vector<Airport> tempVerticies;
    //This part converts the vector of string lines into airport objects and stores it in the veticies vector.
    for (unsigned i = 0; i < vecOfStrs.size(); i++) {
        //grab the string at index i
        std::string data = vecOfStrs.at(i);
        //find the first and second comma
        std::vector<std::string> result;
        std::stringstream s_stream(data); //create string stream from the string
        while(s_stream.good()) {
            std::string substr;
            getline(s_stream, substr, ','); //get first string delimited by comma
            result.push_back(substr);
        }

        //The important information is being pulled out of each line, converted into airport objects.
        double latitude = std::stod(result.at(result.size() - 8));
        double longitude = std::stod(result.at(result.size() - 7));
        std::string name = result.at(1);
        name.erase(name.size() - 1);
        name.erase(name.begin());

        //creates airport and puts it in a verticies unordered map.
        Airport airport = Airport(latitude, longitude, name);
        verticies[name] = airport;
        
        tempVerticies.push_back(airport);

    }

    //code for creating edges
    for (unsigned i = 0; i < tempVerticies.size(); i++) {
        for (unsigned j = 0; j < tempVerticies.size(); j++) {
            //avoiding self edges
            if (j == i) {
                continue;
            }

            Airport airportOne = tempVerticies.at(i);
            Airport airportTwo = tempVerticies.at(j);
            //according to usgs.gov, one degree of latitude is ~69 miles, one degree of longitude is ~54.6 miles
            double distance = sqrt(pow((airportOne.longitude - airportTwo.longitude) * 54.6, 2) 
                + pow((airportOne.latitude - airportTwo.latitude) * 69, 2));
            //only adding edges between airports that are within 800 nautical miles
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
    //if vertex does not exist already, add it and make empty entry in adjancy matrix.
    if (verticies.find(airportName) == verticies.end()) {
        verticies[airportName] = airport;
        adjacencyMatrix[airportName] = std::unordered_map<std::string, double>();
    }
    //insert edges that can be made by new vertex
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

//logic borrowed from graph.h in lab_ml
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


