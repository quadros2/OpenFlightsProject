#include "Airport.h"
#include <iostream>
#include <string>

// Default constructor
Airport::Airport() {}

// Modified constructor
Airport::Airport(double setLatitude, double setLongitude, std::string setName) {
    latitude = setLatitude;
    longitude = setLongitude;
    name = setName;
}
