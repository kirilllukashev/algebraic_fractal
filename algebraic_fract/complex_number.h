#ifndef COMPLEX_NUMBER_H
#define COMPLEX_NUMBER_H

#include <cmath>

class Complex {
public:
    Complex(): rat_(0), com_(0) {}
    Complex(double rat): rat_(rat), com_(0) {}
    Complex(double rat, double com): rat_(rat), com_(com) {}
    ~Complex() {}
    double get_rat() const {
        return rat_;
    }
    double get_com() const {
        return com_;
    }
    Complex& operator=(const Complex& other) {
        rat_ = other.get_rat();
        com_ = other.get_com();
        return *this;
    }
    Complex operator+(const Complex& right) {
        return Complex(rat_ + right.get_rat(), com_ + right.get_com());
    }
    Complex operator-(const Complex& right) {
        return Complex(rat_ - right.get_rat(), com_ - right.get_com());
    }
    Complex operator*(const Complex& right) {
        return Complex(rat_ * right.get_rat() - com_ * right.get_com(), rat_ * right.get_com() + com_ * right.get_rat());
    }
    double abs() {
        return sqrt(rat_ * rat_ + com_ * com_);
    }
private:
    double rat_, com_;
};


#endif // COMPLEX_NUMBER_H
