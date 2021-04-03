#include "Ray.hpp"
#include "Vector.hpp"

Ray::Ray(Vector start, Vector dir) :
    start_(start),
    dir_  (dir)
{}