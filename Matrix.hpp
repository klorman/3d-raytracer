#include "Vector.hpp"

struct RECT {
    int row1, col1, row2, col2;
};

struct mat4 {
    const int SIZE = 4;

    double** data_;

    mat4();
    mat4(const mat4& m);
    ~mat4();

    mat4&   operator =  (const mat4& m);
    double* operator [] (int row);
    mat4    operator -  (const mat4& m) const;
    mat4    operator +  (const mat4& m) const;
    mat4    operator *  (const mat4& m) const;
};