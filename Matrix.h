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
    for (const auto& lines : matrix.data) {
        for(const auto& cell : lines) {
            str << cell << ' ';
        }
        str << '\n';
    }
    return str;
}

template <typename T>
std::string to_string(const Matrix<T>& matrix) {
    std::string ans;
    for (const auto& lines : matrix.data) {
        for(const auto& cell : lines) {
            ans += std::to_string(cell) + ' ';
        }
        ans += '\n';
    }
    return ans;
}
#endif //CALC_MATRIX_H
