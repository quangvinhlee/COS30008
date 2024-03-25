#include "Vector3D.h"
#include <sstream>
#include <iomanip>

std::string Vector3D::toString() const noexcept {
    std::stringstream stringStream;

    // Set precision for x component
    int xPrecision;
    if (std::abs(x() - std::round(x())) < 0.1) {
        xPrecision = 1;
    } else {
        xPrecision = 4;
    }
    if (std::abs(x() - std::round(x())) == 0 ) {
        xPrecision = 0;
    }
    
    stringStream << "[" << std::setprecision(xPrecision) << std::fixed << x() << ", ";

    // Set precision for y component
    int yPrecision;
    if (std::abs(y() - std::round(y())) < 0.1) {
        yPrecision = 1;
    } else {
        yPrecision = 4;
    }
    if (std::abs(y() - std::round(y())) == 0) {
        yPrecision = 0;
    }
    stringStream << std::setprecision(yPrecision) << std::fixed << y() << ", ";

    // Set precision for fW component
    int wPrecision;
    if (std::abs(w() - std::round(w())) < 0.1) {
        wPrecision = 1;
    }
    else {
        wPrecision = 4;
    }
    if (std::abs(w() - std::round(w())) == 0) {
        wPrecision = 0;
    }
    
    stringStream << std::setprecision(wPrecision) << std::fixed << w() << "]";

    return stringStream.str();
}

std::ostream& operator<<(std::ostream& oStream, const Vector3D& aVector) {
    return oStream << "[" << aVector.x() << ", " << aVector.y() << ", " << aVector.w() << "]";
}