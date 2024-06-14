#include "Matrix3x3.h"
#include "Vector3D.h"
#include <sstream>
#include <iomanip>
#include <cmath>

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& aOther) const noexcept {
    return Matrix3x3(
        Vector3D(row(0).dot(aOther.column(0)), row(0).dot(aOther.column(1)), row(0).dot(aOther.column(2))),
        Vector3D(row(1).dot(aOther.column(0)), row(1).dot(aOther.column(1)), row(1).dot(aOther.column(2))),
        Vector3D(row(2).dot(aOther.column(0)), row(2).dot(aOther.column(1)), row(2).dot(aOther.column(2)))
    );
}

float Matrix3x3::det() const noexcept {
    return fRows[0][0] * (fRows[1][1] * fRows[2][2] - fRows[1][2] * fRows[2][1]) -
        fRows[0][1] * (fRows[1][0] * fRows[2][2] - fRows[1][2] * fRows[2][0]) +
        fRows[0][2] * (fRows[1][0] * fRows[2][1] - fRows[1][1] * fRows[2][0]);
}

Matrix3x3 Matrix3x3::transpose() const noexcept
{
    return Matrix3x3(Vector3D(fRows[0][0], fRows[1][0], fRows[2][0]),
        Vector3D(fRows[0][1], fRows[1][1], fRows[2][1]),
        Vector3D(fRows[0][2], fRows[1][1], fRows[2][2])
    );
};

bool Matrix3x3::hasInverse() const noexcept
{
    return det() != 0;
};

Matrix3x3 Matrix3x3::inverse() const {
    float determinant = det();
    if (determinant != 0)
    {
        float invDet = 1.0f / determinant;
        return Matrix3x3(
            Vector3D((fRows[1][1] * fRows[2][2] - fRows[1][2] * fRows[2][1]) * invDet,
                (fRows[0][2] * fRows[2][1] - fRows[0][1] * fRows[2][2]) * invDet,
                (fRows[0][1] * fRows[1][2] - fRows[0][2] * fRows[1][1]) * invDet),
            Vector3D((fRows[1][2] * fRows[2][0] - fRows[1][0] * fRows[2][2]) * invDet,
                (fRows[0][0] * fRows[2][2] - fRows[0][2] * fRows[2][0]) * invDet,
                (fRows[0][2] * fRows[1][0] - fRows[0][0] * fRows[1][2]) * invDet),
            Vector3D((fRows[1][0] * fRows[2][1] - fRows[1][1] * fRows[2][0]) * invDet,
                (fRows[0][1] * fRows[2][0] - fRows[0][0] * fRows[2][1]) * invDet,
                (fRows[0][0] * fRows[1][1] - fRows[0][1] * fRows[1][0]) * invDet)
        );
    };
};

std::ostream& operator<<(std::ostream& oStream, const Matrix3x3& aMatrix)
{
    std::stringstream stringStream;
    
    stringStream << "[" << aMatrix.row(0) << ", " << aMatrix.row(1) << ", " << aMatrix.row(2) << "]";

    return oStream << stringStream.str();

}