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
            std::cout << distance << std::endl;
            //only adding edges between airports that are within 800 nautical miles
            if (distance < 800) {
                adjacencyMatrix[airportOne.name][airportTwo.name] = distance;
            } else {
                adjacencyMatrix[airportOne.name][airportTwo.name] = 0;
            }
        }
    }



}


