#include "Vector.hpp"

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

Vector Vector::operator  /  (const Vector& vec) const {
	//assert(vec.x_ == 0 || vec.y_ == 0 || vec.z_ == 0);

	return{ vec.x_ == 0 ? INF : x_ / vec.x_, vec.y_ == 0 ? INF : y_ / vec.y_, vec.z_ == 0 ? INF : z_ / vec.z_ }; //надо придумать, как обрабатывать деление на 0
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

bool Vector::operator != (const Vector& vec) const {
	return !(vec == *this);
}

double Vector::length() const {
	return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

Vector& Vector::norm() {
	double len = length();

	if (len > 0) {
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

Vector& Vector::rot(const Vector& r) {
	double cx = cos(r.x_),
		   sx = sin(r.x_),
		   cy = cos(r.y_),
		   sy = sin(r.y_),
		   d = z_ * cy - y_ * sy;

	Vector res = {
		x_ * cx + d * sx,
		z_ * sy + y_ * cy,
		-x_ * sx + d * cx
	};

	*this = res;

	return (*this);
}

Vector mix(const Vector& x, const Vector& y, double a) {
	return x * (1 - a) + y * a;
}

Vector abs(const Vector& vec) {
	return { (double)abs(vec.x_), (double)abs(vec.y_), (double)abs(vec.z_) };
}

double sign(double x) {
	return x < 0 ? -1 : x > 0;
}

Vector sign(const Vector& vec) {
	return { sign(vec.x_), sign(vec.y_), sign(vec.z_) };
}

double step(double edge, double x) {
	return x < edge ? 0 : 1;
}

Vector step(const Vector& edge, const Vector& vec) {
	return { step(edge.x_, vec.x_), step(edge.y_, vec.y_), step(edge.z_, vec.z_) };
}