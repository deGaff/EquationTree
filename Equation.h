//
// Created by d3Gaff on 24.03.2022.
//

#ifndef CALC_EQUATION_H
#define CALC_EQUATION_H
#include <string>
#include <istream>
#include <memory>
#include <type_traits>
#include <unordered_map>

#include "BinaryOperations.h"

namespace Equation {
    template <typename T>
    class Base {
    public:
        virtual T Evaluate() const = 0;
        virtual std::string ToString() const = 0;
    };

    template <typename T>
    using ExprPtr = std::shared_ptr<Base<T>>;

    template <typename L, typename R, typename Func>
    using ReturnType = typename std::result_of<Func(L,R)>::type;

    template <typename T>
    std::ostream& operator<<(std::ostream& str, ExprPtr<T> ptr) {
        str << ptr->ToString() << " = " << ptr->Evaluate();
        return str;
    }

    template <typename T>
    class Value : public Base<T> {
    private:
        T val;
    public:
        Value(const T& val) : val(val) {}
        T Evaluate() const override {
            return val;
        }
        std::string ToString() const override {
            using namespace std;
            return to_string(val);
        }
    };


    template <typename L, typename R, typename Func>
    class Binary : public Base<ReturnType<L, R, Func>> {
        const char symbol;
    private:
        ExprPtr<L> lhs; ExprPtr<R> rhs;
    public:
        Binary(const char symbol,  ExprPtr<L> lhs, ExprPtr<R> rhs)
        : symbol(symbol), lhs(lhs), rhs(rhs) {}

        ExprPtr<L> GetLhs() const { return lhs; }
        ExprPtr<R> GetRhs() const { return rhs; }
        ReturnType<L, R, Func> Evaluate() const override {
            return Func()(lhs->Evaluate(), rhs->Evaluate());
        }
        std::string ToString() const override {
            return "(" + lhs->ToString() + ")" + symbol + "(" + rhs->ToString() + ")";
        }
    };

    template <typename T>
    ExprPtr<T> MakeVal(const T& val) {
        return std::make_shared<Value<T>>(val);
    }

    template <typename L, typename R>
    ExprPtr<ReturnType<L, R, SUM<L,R>>> MakeSum(ExprPtr<L> lhs, ExprPtr<R> rhs) {
        return std::make_shared<Binary<L,R,SUM<L,R>>>
                ('+', lhs, rhs);
    }

    template <typename L, typename R>
    ExprPtr<ReturnType<L, R, SUBTR<L,R>>> MakeSubtr(ExprPtr<L> lhs, ExprPtr<R> rhs) {
        return std::make_shared<Binary<L,R,SUBTR<L,R>>>
                ('-', lhs, rhs);
    }

    template <typename L, typename R>
    ExprPtr<ReturnType<L, R, MULT<L,R>>> MakeMult(ExprPtr<L> lhs, ExprPtr<R> rhs) {
        return std::make_shared<Binary<L,R,MULT<L,R>>>
                ('*', lhs, rhs);
    }

    template <typename L, typename R>
    ExprPtr<ReturnType<L, R, DIV<L,R>>> MakeDiv(ExprPtr<L> lhs, ExprPtr<R> rhs) {
        return std::make_shared<Binary<L,R,DIV<L,R>>>
                ('/', lhs, rhs);
    }

    template <typename L, typename R>
    ExprPtr<ReturnType<L, R, DEG<L,R>>> MakeDeg(ExprPtr<L> lhs, ExprPtr<R> rhs) {
        return std::make_shared<Binary<L, R, DEG<L, R>>>
                ('^', lhs, rhs);
    }

    const static std::unordered_map<char, char> priorities = {
            {'+', 0}, {'-', 0}, {'*', 1}, {'/', 1}, {'^', 2}
        }; //TODO mb add brackets here
}


#endif //CALC_EQUATION_H
