#pragma once

#define NULLVEC Vector { 0, 0, 0 }
#define EVEC    Vector { 1, 1, 1 }
#define EPS     0.01

class Vector {
public:
	double x_, y_, z_;

	Vector();
	Vector(double x, double y, double z);
	Vector(double num);

	Vector operator  -  () const;

	Vector  operator *  (const Vector& vec) const;
	Vector  operator /  (const double& num) const;
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

Vector mix(const Vector& col1, const Vector& col2, double a);