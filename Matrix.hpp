#pragma once

#include "Vector.hpp"

#include <cassert>
#include <iostream>

template <int rows, int cols>
class matrix {
public:
    double data_[rows][cols];

    matrix() {
        memset(data_, 0, sizeof(data_));
    }

    matrix(double* data) {
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                data_[row][col] = data[row * cols + col];
            }
        }
    }

    matrix<rows, cols>& operator= (const matrix<rows, cols>& m);
    double* operator[](int row);
    matrix<rows, cols>  operator- (const matrix<rows, cols>& m) const;
    matrix<rows, cols>  operator+ (const matrix<rows, cols>& m) const;

    operator Vector() const;

    void print() {
        std::cout << std::endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << data_[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

typedef matrix<4,4> mat4;
typedef matrix<1,4> vec4;

mat4 inverse(mat4& m);
mat4 rotation(const Vector& v, double angle);
mat4 translate(const Vector& v);

template <int rows, int cols>
matrix<rows, cols>::operator Vector() const {
    return {data_[0][0], data_[0][1], data_[0][2]};
}

template <int rows, int cols>
matrix<rows, cols>& matrix<rows, cols>::operator=(const matrix<rows, cols>& m) {
    if (this == &m) {
		return *this;
	}

    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            data_[i][j] = m.data_[i][j];
        }
    }

    return *this;
}

template <int rows, int cols>
double* matrix<rows, cols>::operator[](int row) {
    return data_[row];
}

template <int rows, int cols>
matrix<rows, cols> matrix<rows, cols>::operator-(const matrix<rows, cols>& m) const {
    matrix<rows, cols> res;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            res[i][j] = data_[i][j] - m.data_[i][j];
        }
    }

    return res;
}

template <int rows, int cols>
matrix<rows, cols> matrix<rows, cols>::operator+(const matrix<rows, cols>& m) const {
    matrix<rows, cols> res;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            res[i][j] = data_[i][j] + m.data_[i][j];
        }
    }

    return res;
}

template <int rows1, int cols1, int rows2, int cols2>
matrix<rows1, cols2> operator*(const matrix<rows1, cols1>& a, const matrix<rows2, cols2>& b) {
    assert(cols1 == rows2);

    matrix<rows1, cols2> res;
    
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int elem = 0; elem < cols1; elem++) {
                res.data_[i][j] += a.data_[i][elem] * b.data_[elem][j];
            }
        }
    }

    return res;
}