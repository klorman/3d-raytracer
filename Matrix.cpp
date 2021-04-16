#include "Matrix.hpp"

mat4::mat4() {
    data_ = new double * [SIZE];

    for (int i = 0; i < SIZE; ++i) {
        data_[i] = new double [SIZE];
    }
}

mat4::mat4(const mat4& m) :
    data_(m.data_)
{}

mat4::~mat4() {
    for (int i = 0; i < SIZE; ++i) {
        delete[] data_[i];
    }

    delete[] data_;
}

mat4& mat4::operator=(const mat4& m) {
    if (this == &m) {
		return *this;
	}

    for(int i = 0; i < SIZE; ++i) {
        for(int j = 0; j < SIZE; ++j) {
            data_[i][j] = m.data_[i][j];
        }
    }

    return *this;
}

double* mat4::operator[](int row) {
    return data_[row];
}

mat4 mat4::operator-(const mat4& m) const {
    mat4 res;

    for (int i = 0; i < res.SIZE; ++i) {
        for (int j = 0; j < res.SIZE; ++j) {
            res[i][j] = (*this).data_[i][j] - m.data_[i][j];
        }
    }

    return res;
}

mat4 mat4::operator+(const mat4& m) const {
    mat4 res;

    for (int i = 0; i < res.SIZE; ++i) {
        for (int j = 0; j < res.SIZE; ++j) {
            res[i][j] = (*this).data_[i][j] + m.data_[i][j];
        }
    }

    return res;
}

mat4 mat4::operator*(const mat4& m) const {
    mat4 res;
    
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < m.SIZE; ++j) {
            for (int elem = 0; elem < SIZE; elem++) {
                res.data_[i][j] += data_[i][elem] * m.data_[elem][j];
            }
        }
    }

    return res;
}