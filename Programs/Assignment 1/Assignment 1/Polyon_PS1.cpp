// Polygon_PS1.cpp

#include "Polygon.h"
#include <cmath>

float Polygon::getSignedArea() const noexcept {
    float area = 0.0f;
    for (size_t i = 0; i < fNumberOfVertices; ++i) {
        size_t j = (i + 1) % fNumberOfVertices;
        area += (fVertices[i].x() * fVertices[j].y() - fVertices[j].x() * fVertices[i].y());
    }
    return area / 2.0f;
}

Polygon Polygon::transform(const Matrix3x3& aMatrix) const noexcept {
    Polygon transformedPolygon;
    for (size_t i = 0; i < fNumberOfVertices; ++i) {
        Vector3D vertex3D(fVertices[i].x(), fVertices[i].y(), 1.0f);
        Vector3D transformedVertex = aMatrix * vertex3D;
        transformedPolygon.fVertices[i] = Vector2D(transformedVertex.x(), transformedVertex.y());
    }
    transformedPolygon.fNumberOfVertices = fNumberOfVertices;
    return transformedPolygon;
}
