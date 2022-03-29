//
// Created by d3Gaff on 29.03.2022.
//

#ifndef CALC_MATRIX_H
#define CALC_MATRIX_H
#include <vector>
#include <iostream>

template <typename T>
class Matrix;

template <typename T>
std::istream& operator >> (std::istream& str, Matrix<T>& matrix);

template <typename T>
std::ostream& operator << (std::ostream& str, const Matrix<T>& matrix);

template <typename T>
std::string to_string(const Matrix<T>& matrix);

template <typename T>
class Matrix{
public:
    Matrix(std::size_t m, std::size_t n) : m(m), n(n), data(m, std::vector<T>(n)) {}
    Matrix<T> operator * (int k) const;
    friend Matrix operator * (int k, Matrix<T> matrix) {
        return matrix * k;
    }
    friend std::istream& operator >> <T>  (std::istream& str, Matrix<T>& matrix);
    friend std::ostream& operator << <T> (std::ostream& str, const Matrix<T>& matrix);
    friend std::string to_string<T> (const Matrix<T>& matrix);

private:
    const size_t m, n;
    std::vector<std::vector<T>> data;
};

template <typename T>
Matrix<T> Matrix<T>::operator*(int k) const {
    Matrix<T> ans(m, n);
    for (std::size_t i = 0; i < m; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            ans.data[i][j] = k*data[i][j];
        }
    }
    return ans;
}


template <typename T>
std::istream& operator >> (std::istream& str, Matrix<T>& matrix) {
    for (auto& lines : matrix.data) {
        for (auto &cell: lines) {
            str >> cell;
        }
    }
    return str;
}

template <typename T>
std::ostream& operator << (std::ostream& str, const Matrix<T>& matrix) {
    for (std::size_t i = 0; i < matrix.m; ++i) {
        for (std::size_t j = 0; j < matrix.n; ++j) {
            str << matrix.data[i][j];
            if(j!=matrix.n-1) str  << ' ';
        }
        if(i!=matrix.m-1) str << '|';
    }
    return str;
}

template <typename T>
std::string to_string(const Matrix<T>& matrix) {
    std::string ans;
    for (std::size_t i = 0; i < matrix.m; ++i) {
        for (std::size_t j = 0; j < matrix.n; ++j) {
            ans += std::to_string(matrix.data[i][j]);
            if(j!=matrix.n-1) ans += ' ';
        }
        if(i!=matrix.m-1) ans += '|';
    }
    return ans;
}
#endif //CALC_MATRIX_H
