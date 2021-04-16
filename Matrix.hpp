#pragma once

#include <cassert>

template <int rows, int cols>
class matrix {
public:
    double data_[rows][cols];
    int row_, col_;

    matrix(const matrix<rows, cols>& m) :
        data_(m.data_),
        row_ (rows),
        col_ (cols)
    {}

    matrix(double** data) :
        data_(data)
    {}

    ~matrix() {
        delete[] data_;
    }

    matrix<rows, cols>& operator= (const matrix<rows, cols>& m); //всё переделать
    matrix<rows, cols>& operator[](int row); //всё переделать
    matrix<rows, cols>  operator- (const matrix<rows, cols>& m) const;  //всё переделать
    matrix<rows, cols>  operator+ (const matrix<rows, cols>& m) const;  //всё переделать
    matrix<rows, cols>  operator* (const matrix<rows, cols>& m) const;  //всё переделать
};

template <int rows, int cols>
matrix<rows, cols>& matrix<rows, cols>::operator=(const matrix<rows, cols>& m) {
    if (this == &m) {
		return *this;
	}

    if (col_ < m.col_ || row_ < m.row_) {
        col_ = m.col_;
        row_ = m.row_;
        data_ = m.data_;

        return *this;
    }

    for(int i = 0; i < m.row_; i++) {
        for(int j = 0; j < m.col_; j++) {
            data_[i][j] = m.data_[i][j];
        }
    }

    return *this;
}

template <int rows, int cols>
matrix<rows, cols>& matrix<rows, cols>::operator[](int row) {
    return data_[row];
}

template <int rows, int cols>
matrix<rows, cols> matrix<rows, cols>::operator-(const matrix<rows, cols>& m) const {
    assert(col_ == m.col_ && row_ == m.row_);

    matrix<rows, cols> res;

    for (int i = 0; i < res.row_; i++) {
        for (int j = 0; j < res.col_; j++) {
            res[i][j] = data_[i][j] - m.data_[i][j];
        }
    }

    return res;
}

template <int rows, int cols>
matrix<rows, cols> matrix<rows, cols>::operator+(const matrix<rows, cols>& m) const {
    assert(col_ == m.col_ && row_ == m.row_);

    matrix<rows, cols> res(m.col_, m.row_);

    for (int i = 0; i < res.row_; i++) {
        for (int j = 0; j < res.col_; j++) {
            res[i][j] = data_[i][j] + m.data_[i][j];
        }
    }

    return res;
}

template <int rows1, int cols1, int rows2, int cols2>
matrix<rows1, cols2> matrix<rows1, cols1>::operator*(const matrix<rows2, cols2>& m) const {
    assert(col_ == m.row_);

    matrix<(rows1, cols2> res;
    
    for (int i = 0; i < row_; i++) {
        for (int j = 0; j < m.col_; j++) {
            for (int elem = 0; elem < col_; elem++) {
                res.data_[i][j] += data_[i][elem] * m.data_[elem][j];
            }
        }
    }

    return res;
}