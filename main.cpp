#include <iostream>
#include "Equation.h"

/*
 *        *
 *      4   +
 *        1   2
 */

int main() {
    using namespace Equation;
    auto ptr = MakeSum(MakeVal(1.), MakeVal(2.));
    auto mult_ptr = MakeMult(ptr, MakeVal(4.));
    auto dib_ptr = MakeDiv(ptr, MakeVal(3.));
    auto substr_ptr = MakeSubtr(ptr, MakeVal(3.));
    auto deg_ptr = MakeDeg(ptr, MakeVal(3.));

    std::cout << ptr << '\n'
                << mult_ptr << '\n'
                << dib_ptr << '\n'
                << substr_ptr << '\n'
                << deg_ptr << '\n';
    std::cout << mult_ptr->ToString() << " = " << mult_ptr->Evaluate() << '\n';
    return 0;
}
