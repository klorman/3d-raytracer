#include "Vector.hpp"
#include <cmath>

Vector::Vector() :
	x_(0),
	y_(0),
	z_(0)
{}

Vector::Vector(double x, double y, double z) :
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

double Vector::length() {
	return sqrt((*this) ^ (*this));
}

Vector& Vector::norm() {
	(*this) = (*this) / length();
	return (*this);
}