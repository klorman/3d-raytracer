#include "Vector.hpp"
#include <cmath>
#include <algorithm>

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

Vector Vector::operator  -  () const { 
	return { -x_, -y_, -z_ };
}

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
	return{ x_ - vec.x_, y_ - vec.y_, z_ - vec.z_ };
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

Vector& Vector::operator -= (const Vector& vec) {
	x_ -= vec.x_;
	y_ -= vec.y_;
	z_ -= vec.z_;
	return (*this);
}

Vector& Vector::operator *= (const Vector& vec) {
	x_ *= vec.x_;
	y_ *= vec.y_;
	z_ *= vec.z_;
	return (*this);
}

bool Vector::operator == (const Vector& vec) const {
	return vec.x_ == x_ && vec.y_ == y_ && vec.z_ == z_ ? true : false;
}

double Vector::length() const {
	return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

Vector& Vector::norm() {
	double len = length();

	if (len != 0) {
		x_ = x_ / len;
		y_ = y_ / len;
		z_ = z_ / len;
	}

	return (*this);
}

Vector& Vector::limit(double lim) {
	x_ = std::min(x_, lim);
	y_ = std::min(y_, lim);
	z_ = std::min(z_, lim);

	return (*this);
}

Vector& Vector::rot(const Vector& vec1, const Vector& vec2) { //пока костыльная функция, нужно переделать
	double  proj = sqrt(vec2.z_*vec2.z_ + vec2.x_*vec2.x_), cos = 0, sin = 0;

	if (proj > 0) {
		cos = vec2.z_ / proj,
		sin = vec2.x_ / proj;
		*this = {x_*cos + z_*sin, y_, -x_*sin + z_*cos};
	}

	return (*this);
}

Vector mix(const Vector& x, const Vector& y, double a) {
	return x * (1 - a) + y * a;
}