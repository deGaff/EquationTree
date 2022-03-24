//
// Created by d3Gaff on 24.03.2022.
//

#ifndef CALC_EQUATION_H
#define CALC_EQUATION_H
#include <string>
#include <memory>
#include <cmath>

namespace Equation {
    template <typename T>
    class Base {
    public:
        virtual T Evaluate() const = 0;
        virtual std::string ToString() const = 0;
    };

    template <typename T>
    using ExprPtr = std::shared_ptr<Base<T>>;

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
            return std::to_string(val);
        }
    };

    template <typename T>
    class Binary : public Base<T> {
    private:
        const char symbol;
        ExprPtr<T> lhs, rhs;
    public:
        Binary(const char symbol, ExprPtr<T> lhs, ExprPtr<T> rhs) : symbol(symbol), lhs(lhs), rhs(rhs) {}
        ExprPtr<T> GetLhs() const { return lhs; }
        ExprPtr<T> GetRhs() const { return rhs; }
        std::string ToString() const override {
            return "(" + lhs->ToString() + ")" + symbol + "(" + rhs->ToString() + ")";
        }
    };

    template <typename T>
    class Sum : public Binary<T> {
    public:
        Sum(ExprPtr<T> lhs, ExprPtr<T> rhs) : Binary<T>('+', lhs, rhs) {}
        T Evaluate() const override {
            return Binary<T>::GetLhs()->Evaluate() + Binary<T>::GetRhs()->Evaluate();
        }
    };

    template <typename T>
    class Subtr : public Binary<T> {
    public:
        Subtr(ExprPtr<T> lhs, ExprPtr<T> rhs) : Binary<T>('-', lhs, rhs) {}
        T Evaluate() const override {
            return Binary<T>::GetLhs()->Evaluate() - Binary<T>::GetRhs()->Evaluate();
        }
    };

    template <typename T>
    class Mult : public Binary<T> {
    public:
        Mult(ExprPtr<T> lhs, ExprPtr<T> rhs) : Binary<T>('*', lhs, rhs) {}
        T Evaluate() const override {
            return Binary<T>::GetLhs()->Evaluate() * Binary<T>::GetRhs()->Evaluate();
        }
    };

    template <typename T>
    class Div : public Binary<T> {
    public:
        Div(ExprPtr<T> lhs, ExprPtr<T> rhs) : Binary<T>('/', lhs, rhs) {}
        T Evaluate() const override {
            return Binary<T>::GetLhs()->Evaluate() / Binary<T>::GetRhs()->Evaluate();
        }
    };

    template <typename T>
    class Deg : public Binary<T> {
    public:
        Deg(ExprPtr<T> lhs, ExprPtr<T> rhs) : Binary<T>('^', lhs, rhs) {}
        T Evaluate() const override {
            return pow(Binary<T>::GetLhs()->Evaluate(), Binary<T>::GetRhs()->Evaluate());
        }
    };

    template <typename T>
    ExprPtr<T> MakeVal(const T& val) {
        return std::make_shared<Value<T>>(val);
    }

    template <typename T>
    ExprPtr<T> MakeSum(ExprPtr<T> lhs, ExprPtr<T> rhs) {
        return std::make_shared<Sum<T>>(lhs, rhs);
    }

    template <typename T>
    ExprPtr<T> MakeSubtr(ExprPtr<T> lhs, ExprPtr<T> rhs) {
        return std::make_shared<Subtr<T>>(lhs, rhs);
    }

    template <typename T>
    ExprPtr<T> MakeMult(ExprPtr<T> lhs, ExprPtr<T> rhs) {
        return std::make_shared<Mult<T>>(lhs, rhs);
    }

    template <typename T>
    ExprPtr<T> MakeDiv(ExprPtr<T> lhs, ExprPtr<T> rhs) {
        return std::make_shared<Div<T>>(lhs, rhs);
    }

    template <typename T>
    ExprPtr<T> MakeDeg(ExprPtr<T> lhs, ExprPtr<T> rhs) {
        return std::make_shared<Deg<T>>(lhs, rhs);
    }

    template <typename T>
    ExprPtr<T> ParseExpression(std::istream& str) {
        //TODO MAKE ParseUtil (string_view)
    }
}


#endif //CALC_EQUATION_H
