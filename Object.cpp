#include "Object.hpp"

Object::Object(const Material& mat, const Vector& size, const Vector& center, const Vector& color, const Vector& rotatio) :
    mat_     (mat),
    size_    (size),
    center_  (center),
    color_   (color),
    rotation_(rotatio),
    //txx      (),
    //txi      (),
    type     (-1),
    status_  (false)
{
    //mat4 rot = rotation(Vector {0,1,0}.norm(), 30);
    //mat4 tra = translate(center_);
    //txi = tra * rot;
    //txx = inverse(txi);
}

std::vector<double> sortFour(double a, double b, double c, double d) {
    double low1 = 0, high1 = 0, low2 = 0, high2 = 0, lowest = 0, middle1 = 0, middle2 = 0, highest = 0;

    if (a < b) { low1 = a; high1 = b; }
    else       { low1 = b; high1 = a; }

    if (c < d) { low2 = c; high2 = d; }
    else       { low2 = d; high2 = c; }

    if (low1 < low2) { lowest = low1; middle1 = low2; }
    else             { lowest = low2, middle1 = low1; }

    if (high1 > high2) { highest = high1; middle2 = high2; }
    else               { highest = high2; middle2 = high1; }

    if (middle1 < middle2) return { lowest, middle1, middle2, highest };
    else                   return { lowest, middle2, middle1, highest };
}