#include "Matrix.hpp"

mat4 inverse(mat4& m) {
    double data[] {
        m[0][0], m[1][0], m[2][0], 0.0,
        m[0][1], m[1][1], m[2][1], 0.0,
        m[0][2], m[1][2], m[2][2], 0.0,
        -(m[0][0] * m[3][0] + m[0][1] * m[3][1] + m[0][2] * m[3][2]),
        -(m[1][0] * m[3][0] + m[1][1] * m[3][1] + m[1][2] * m[3][2]),
        -(m[2][0] * m[3][0] + m[2][1] * m[3][1] + m[2][2] * m[3][2]),
        1.0
    };

    return data;
}

mat4 rotation(const Vector& v, double angle) {
	double s = sin(angle),
		   c = cos(angle),
		   ic = 1 - c;

	double data[] = {v.x_ * v.x_ * ic + c       , v.y_ * v.x_ * ic - s * v.z_, v.z_ * v.x_ * ic + s * v.y_, 0.0,
					 v.x_ * v.y_ * ic + s * v.z_, v.y_ * v.y_ * ic + c       , v.z_ * v.y_ * ic - s * v.x_, 0.0,
					 v.x_ * v.z_ * ic - s * v.y_, v.y_ * v.z_ * ic + s * v.x_, v.z_ * v.z_ * ic + c       , 0.0,
					 0.0,                   0.0,                   0.0,                   1.0};

	return data;
}

mat4 translate(const Vector& v) {
	double data[] = {
		1.0,  0.0,  0.0,  0.0,
		0.0,  1.0,  0.0,  0.0,
		0.0,  0.0,  1.0,  0.0,
		v.x_, v.y_, v.z_, 1.0
	};

	return data;
}