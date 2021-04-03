#include "Vector.hpp"

Vector::Vector(double x = 0, double y = 0, double z = 0) :
	x_(x),
	y_(y),
	z_(z)
{}

Vector::Vector(double num):
	x_(num),
	y_(num),
	z_(num)
{}


Vector Vector::operator  *  (const Vector& vec) const {
	return{ x_ * vec.x_, y_ * vec.y_, z_ * vec.z_ };
}

Vector Vector::operator  /  (const double& num) const {
	return{ x_ / num, y_ / num, z_ / num };
}

Vector Vector::operator  +  (const Vector& vec) const {
	return{ x_ + vec.x_, y_ + vec.y_, z_ + vec.z_ };
}

Vector Vector::operator  -  (const Vector& vec) const {
	return{ vec.x_ - x_, vec.y_ - y_, vec.z_ - z_ };
}

double Vector::operator  ^  (const Vector& vec) const {
	return x_ * vec.x_ + y_ * vec.y_ + z_ * vec.z_;
}

Vector& Vector::operator += (const Vector& vec) {
	x_ += vec.x_;
	y_ += vec.y_;
	z_ += vec.z_;
	return (*this);
}