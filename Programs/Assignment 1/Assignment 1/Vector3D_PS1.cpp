#include "Vector3D.h" 

#include <sstream>
#include <iomanip>

std::string Vector3D::toString() const noexcept {
    auto formatCoordinate = [](float coord) {
        int precision = (std::abs(coord - std::round(coord)) < 0.0001f) ? 0 : (std::abs(coord) > 10000.0f) ? 1 : 4;
        std::stringstream ss;
        ss << std::setprecision(precision) << std::fixed << coord;
        return ss.str();
        };

    return "[" + formatCoordinate(x()) + ", " + formatCoordinate(y()) + ", " + formatCoordinate(w()) + "]";
}

// Change the operator<< from Vctor3D.cpp file to this
std::ostream& operator<<(std::ostream& oStream, const Vector3D& aVector) {
    return oStream << aVector.toString();
}
