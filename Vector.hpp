#pragma once

class Vector
{
public:
	double x_, y_, z_;

	Vector(double x = 0, double y = 0, double z = 0);
	Vector(double num);

	Vector operator  *  (const Vector& vec) const;
	Vector operator  /  (const double& num) const;
	Vector operator  +  (const Vector& vec) const;
	Vector operator  -  (const Vector& vec) const;
	double operator  ^  (const Vector& vec) const;
	Vector& operator += (const Vector& vec);
};


