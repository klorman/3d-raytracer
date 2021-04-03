#pragma once

class Vector
{
public:
	double x_, y_, z_;

	Vector();
	Vector(double x, double y, double z);
	Vector(double num);

	Vector operator  *  (const Vector& vec) const;
	Vector operator  /  (const double& num) const;
	Vector operator  +  (const Vector& vec) const;
	Vector operator  -  (const Vector& vec) const;
	double operator  ^  (const Vector& vec) const;
	Vector& operator += (const Vector& vec);
};


