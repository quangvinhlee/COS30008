#include "Vector3D.h" 

#include <sstream>
#include <iomanip>

std::string Vector3D::toString() const noexcept {
    std::stringstream stringStream;

    int xPrecision = 4;  

    if (std::abs(x() - std::round(x())) < 0.0001) {
        xPrecision = 0;  
    }
    else if (std::abs(x()) > 10000.0f) {
        xPrecision = 1;  
    }

    stringStream << "[" << std::setprecision(xPrecision) << std::fixed << x() << ", ";

    int yPrecision = 4;

    if (std::abs(y() - std::round(y())) < 0.0001) {
        yPrecision = 0;
    }
    else if (std::abs(y()) > 10000.0f) {
        yPrecision = 1;
    }

    stringStream << std::setprecision(yPrecision) << std::fixed << y() << ", ";

    int zPrecision = 4;

    if (std::abs(w() - std::round(w())) < 0.0001) {
        zPrecision = 0;
    }
    else if (std::abs(w()) > 10000.0f) {
        zPrecision = 1;
    }

    stringStream << std::setprecision(zPrecision) << std::fixed << w() << "]";

    return stringStream.str();
}

std::ostream& operator<<(std::ostream& oStream, const Vector3D& aVector) {
    return oStream << aVector.toString();
}
