#include "Matrix3x3.h"
#include "cassert"
#include "cmath"

Matrix3x3::Matrix3x3() noexcept 
{
	fRows[0] = Vector3D(1.0f, 0.0f, 0.0f);
	fRows[1] = Vector3D(0.0f, 1.0f, 0.0f);
	fRows[2] = Vector3D(0.0f, 0.0f, 1.0f);
};

Matrix3x3::Matrix3x3(const Vector3D& aRow1, const Vector3D& aRow2, const Vector3D&aRow3) noexcept
{
	fRows[0] = aRow1;
	fRows[1] = aRow2;
	fRows[2] = aRow3;

};

Matrix3x3 Matrix3x3::operator*(const float aScalar) const noexcept 
{
	Matrix3x3 result;
	for (int i = 0; i < 3; i++) {
		 result.fRows[i] = (fRows[i] * aScalar);
	}
	return result;
};

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& aOther) const noexcept {
	Matrix3x3 result;
	for (int i = 0; i < 3; i++) {
		result.fRows[i] = (fRows[i] + aOther.fRows[i]);
	}
	return result;
}

Vector3D Matrix3x3:: operator*(const Vector3D& aVector) const noexcept
{
	float x = fRows[0].dot(aVector);
	float y = fRows[1].dot(aVector);
	float z = fRows[2].dot(aVector);

	return Vector3D(x, y, z);
}

Matrix3x3 Matrix3x3::scale(const float aX, const float aY)
{
	return Matrix3x3(Vector3D(aX, 0.0f, 0.0f),
		Vector3D(0.0f, aY, 0.0f),
		Vector3D(0.0f, 0.0f, 1.0f));
};

Matrix3x3 Matrix3x3::translate(const float aX, const float aY)
{
	return Matrix3x3(Vector3D(1.0f, 0.0f, aX),
		Vector3D(0.0f, 1.0f, aY),
		Vector3D(0.0f, 0.0f, 1.0f));
};

Matrix3x3 Matrix3x3::rotate(const float aAngleInDegree)
{
	float angleInRadian = aAngleInDegree * (3.14159f / 180.0f);

	float sintheta = sin(angleInRadian);
	float costheta = cos(angleInRadian);

	return Matrix3x3(Vector3D(costheta, -sintheta, 0.0f),
		Vector3D(sintheta, costheta, 0.0f),
		Vector3D(0.0f, 0.0f, 1.0f));
};

 const Vector3D Matrix3x3::row(size_t aRowIndex) const
{
	 return fRows[aRowIndex];
};

const Vector3D Matrix3x3::column(size_t aColumnIndex) const
{
	return fRows[0][aColumnIndex], fRows[1][aColumnIndex], fRows[2][aColumnIndex];
};


