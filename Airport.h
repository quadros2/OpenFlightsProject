#pragma once
#include <iostream>
#include <string>

class Airport {
    public:
        Airport(double setLatitude, double setLongitude, std::string setName);
        double latitude;
        double longitude;
        std::string name;
    private:
};