#include "graph.h"
#include "Airport.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>

Graph::Graph() {
    
}

Graph::Graph(std::string fileName) {
    
    //this part reads each line and stores each line of the data in a vector of strings.
    std::vector<std::string> vecOfStrs;
    // Open the File
    std::ifstream in(fileName.c_str());
    // Check if object is valid
    if(!in)
    {
        std::cerr << "Cannot open the File : "<< fileName << std::endl;
    }
    std::string str;
    // Read the next line from File untill it reaches the end.
    while (std::getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
        if(str.size() > 0)
            vecOfStrs.push_back(str);
    }
    //Close The File
    //airportsAsStrings = vecOfStrs;
    in.close();

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

        //creates airport and puts it in a verticies vector.
        Airport airport = Airport(latitude, longitude, name);
        verticies.push_back(airport);
    }

}


