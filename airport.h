#ifndef AIRPORT_H
#define AIRPORT_H
#include <string>
#include <vector> 
using std::string; 
using std::vector;

struct route {
    string airport;
    vector<string> airlines;
};
class airport {
    public: 
    airport(int);
   
    int id;
    string IATA,ICAO, name, city, country;
    double latitude, longitude;

     
};
#endif // AIRPORT_H