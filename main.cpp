#include <iostream>
#include <vector>
#include "Equation.h"

/*
 *        *
 *      4   +
 *        1   2
 */

template <typename T>
class matrix{
public:
    matrix(size_t m, size_t n) : m(m), n(n), data(m, std::vector<T>(n)) {}
    const matrix operator * (int k) const {
        matrix<T> ans(m,n);
        for (auto& lines : ans) {
            for (auto& cell : lines) {
                cell *= k;
            }
        }
        return ans;
    }
private:
    const size_t m, n;
    std::vector<std::vector<T>> data;
};

int main() {
    using namespace Equation;
    auto ptr = MakeSum(MakeVal(1.), MakeVal(2));
    auto mult_ptr = MakeMult(ptr, MakeVal(4.));
//    auto dib_ptr = MakeDiv(ptr, MakeVal(3.));
//    auto substr_ptr = MakeSubtr(ptr, MakeVal(3.));
//    auto deg_ptr = MakeDeg(ptr, MakeVal(3.));

    std::cout << ptr << '\n'
                << mult_ptr << '\n';
//                << dib_ptr << '\n'
//                << substr_ptr << '\n'
//                << deg_ptr << '\n';
    return 0;
}
