#pragma once

#include <cmath>
#include <algorithm>
#include <cassert>

#define NULLVEC Vector { 0, 0, 0 }
#define EVEC    Vector { 1, 1, 1 }
#define EPS     0.01

#define VEC2RGB(vec) ((COLORREF)(((BYTE)(vec.x_)|((WORD)((BYTE)(vec.y_))<<8))|(((DWORD)(BYTE)(vec.z_))<<16)))

class Vector {
public:
	double x_, y_, z_;

	Vector();
	Vector(double x, double y, double z);
	Vector(double num);

	Vector operator  -  () const;

	Vector  operator *  (const Vector& vec) const;
	Vector  operator /  (const Vector& vec) const;
	Vector  operator +  (const Vector& vec) const;
	Vector  operator -  (const Vector& vec) const;
	double  operator ^  (const Vector& vec) const;
	Vector& operator += (const Vector& vec);
	Vector& operator -= (const Vector& vec);
	Vector& operator *= (const Vector& vec);

	bool operator == (const Vector& vec) const;

	double  length() const;
	Vector& norm();
	Vector& limit(double lim);
	Vector& rot(const Vector& vec1, const Vector& vec2);
};

double sign(double x);
double step(double edge, double x);

Vector mix (const Vector& col1, const Vector& col2, double a);
Vector abs (const Vector& vec);
Vector sign(const Vector& vec);
Vector step(const Vector& edge, const Vector& vec);