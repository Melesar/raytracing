#include "matrix4x4.h"

Matrix4x4 operator-(Matrix4x4 left, const Matrix4x4 & right)
{
	Matrix4x4 res;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			res.matrix[i][j] = left.matrix[i][j] - right.matrix[i][j];
		}
	}

	return res;
}

Matrix4x4 operator*(Matrix4x4 left, const Matrix4x4 & right)
{
	Matrix4x4 result;

	for (int i = 0; i < 4; i++)	{
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				result.matrix[i][j] += left.matrix[i][k] * right.matrix[k][j];
			}
		}
	}

	return result;
}

std::ostream & operator<<(std::ostream & stream, const Matrix4x4 & matrix)
{
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			stream << matrix.matrix[i][j] << " ";
		}
		stream << std::endl;
	}

	return stream;
}

Matrix4x4::Matrix4x4()
{
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			matrix[i][j] = 0;
		}
	}
}

double Matrix4x4::trace() const
{
	double res = 1;

	for (int i = 0; i < 4; ++i) {
		res *= matrix[i][i];
	}

	return res;
}

Matrix4x4 Matrix4x4::inverse()
{
	Matrix4x4 res;
	Matrix4x4 lu = decomposeLU();

	for (int l = 0; l < 4; ++l) {
		Vector4 d, b(l, 1);
		for (int i = 0; i < 4; ++i) {
			double num = b.getIndex(i);
			for (int j = 0; j < i; ++j) {
				num -= lu.matrix[i][j] * d.getIndex(j);
			}
			d.setIndex(i, num / lu.matrix[i][i]);
		}

		Vector4 x;
		for (int i = 3; i >= 0; --i) {
			double num = d.getIndex(i);
			for (int j = i + 1; j < 4; ++j) {
				num -= lu.matrix[i][j] * x.getIndex(j);
			}
			x.setIndex(i, num);
		}

		for (int i = 0; i < 4; ++i) {
			res.matrix[i][l] = x.getIndex(i);
		}
	}

	return res;
}

Matrix4x4 Matrix4x4::decomposeLU() const
{
	Matrix4x4 result;

	result.matrix[0][0] = matrix[0][0];
	for (int i = 1; i < 4; ++i) {
		result.matrix[i][0] = matrix[i][0];
		result.matrix[0][i] = matrix[0][i] / matrix[0][0];
	}

	for (int j = 1; j < 3; ++j) {
		for (int i = j; i < 4; ++i) {
			result.matrix[i][j] = matrix[i][j];
			for (int k = 0; k < j; ++k) {
				result.matrix[i][j] -= result.matrix[i][k] * result.matrix[k][j];
			}
		}

		for (int k = j + 1; k < 4; ++k) {
			double num = matrix[j][k];
			for (int i = 0; i < j; ++i) {
				num -= result.matrix[j][i] * result.matrix[i][k];
			}
			result.matrix[j][k] = num / result.matrix[j][j];
		}
	}

	result.matrix[3][3]  = matrix[3][3];
	for (int k = 0; k < 3; ++k) {
		result.matrix[3][3] -= result.matrix[3][k] * result.matrix[k][3];
	}

	return result;
}

Matrix4x4 Matrix4x4::operator*(double value) const
{
	Matrix4x4 res;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			res.matrix[i][j] = matrix[i][j] * value;
		}
	}

	return res;
}

Vector4 Matrix4x4::operator*(const Vector4 & vect) const
{
	Vector4 result;

	result.x = matrix[0][0] * vect.x + matrix[0][1] * vect.y + matrix[0][2] * vect.z + matrix[0][3] * vect.w;
	result.y = matrix[1][0] * vect.x + matrix[1][1] * vect.y + matrix[1][2] * vect.z + matrix[1][3] * vect.w;
	result.z = matrix[2][0] * vect.x + matrix[2][1] * vect.y + matrix[2][2] * vect.z + matrix[2][3] * vect.w;
	result.w = matrix[3][0] * vect.x + matrix[3][1] * vect.y + matrix[3][2] * vect.z + matrix[3][3] * vect.w;

	return result;
}




