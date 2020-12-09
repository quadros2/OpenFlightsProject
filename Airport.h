#pragma once
#include <iostream>
#include <string>

/**
 * Airport object represents each key node/point in the OpenFlights dataset.
 * Attributes include latitude, longitude, and the airport's name.
 */
class Airport {
    public:
        // Default constructor
        Airport();
        // Constructor taking in latitude, longitude, and name
        Airport(double setLatitude, double setLongitude, std::string setName);

        // Instance variables listed below
        double latitude;
        double longitude;
        std::string name;
    private:
};