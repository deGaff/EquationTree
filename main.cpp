#include <iostream>
#include <sstream>
#include "Equation.h"
#include "Matrix.h"

/*
 *        *
 *      4   +
 *        1   2
 */

int main() {
    using namespace Equation;
    auto ptr = MakeSum(MakeVal(1.), MakeVal(2));
    auto mult_ptr = MakeMult(ptr, MakeVal(4.));
    auto dib_ptr = MakeDiv(ptr, MakeVal(3.));
    auto substr_ptr = MakeSubtr(ptr, MakeVal(3.));
    auto deg_ptr = MakeDeg(ptr, MakeVal(3.));


    std::cout << ptr << '\n'
                << mult_ptr << '\n'
                << dib_ptr << '\n'
                << substr_ptr << '\n'
                << deg_ptr << '\n';

    Matrix<int> matrix(2, 2);
    std::cin >> matrix;
    auto matr_ptr = MakeMult(MakeVal(matrix), MakeVal(4));
    std::cout << matr_ptr << '\n';
    auto matr_ptr2 = MakeMult(MakeVal(5), matr_ptr);
    std::cout << matr_ptr2 << '\n';
    return 0;
}
