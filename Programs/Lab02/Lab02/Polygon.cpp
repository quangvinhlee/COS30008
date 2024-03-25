#include "Polygon.h"

Polygon::Polygon() noexcept: 
  fNumberOfVertices(0)
{	
}
void Polygon::readData(std::istream& aIStream) {
	while (aIStream >> fVertices[fNumberOfVertices]) {
		fNumberOfVertices++;
	}
}

size_t Polygon::getNumberOfVertices() const noexcept
{
	return fNumberOfVertices;
}

const Vector2D& Polygon::getVertex(size_t aIndex) const {
	return fVertices[aIndex];
}

float Polygon::getPerimeter() const noexcept {
	float perimeter = 0;
	for (size_t i = 0; i < fNumberOfVertices; i++) {
		size_t nextIndex = i + 1 % fNumberOfVertices;
		perimeter += (fVertices[nextIndex] - fVertices[i]).length();
	}
	return perimeter;
}

Polygon Polygon::scale(float aScalar) const noexcept {
	Polygon Result = *this;
	for (size_t i = 0; i < fNumberOfVertices; i++) {
		Result.fVertices[i] = fVertices[i] * aScalar;
	}
	return Result;
}