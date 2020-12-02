#include "Airport.h"
#include <iostream>
#include <string>

Airport::Airport() {}

Airport::Airport(double setLatitude, double setLongitude, std::string setName) {
    latitude = setLatitude;
    longitude = setLongitude;
    name = setName;
}
