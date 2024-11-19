//Zichen Shi (zshi34)

#include <cmath>
#include "exception.h"
#include "expr.h"
#include <iostream>
#include <sstream>

// Expr (base class)
Expr::Expr() { }

Expr::~Expr() { };

// Derived classes
double ExprX::eval(double x) const {
    return x;
}

std::string ExprX::to_prefix_string() const {
    return "x";
}

std::string ExprX::to_common_string() const {
    return "x";
}


// expr pi
double ExprPi::eval(double /* x */) const {
    const static double Pi = acos(-1);
    return Pi;
}

std::string ExprPi::to_prefix_string() const {
    return "pi";
}

std::string ExprPi::to_common_string() const {
    return "pi";
}

// expr literal number
ExprLiteral::ExprLiteral(double val) : value(val) {
}

double ExprLiteral::eval(double /* x */) const {
    return value;
}

std::string ExprLiteral::to_prefix_string() const {
    std::ostringstream str_stream;
    str_stream << value;
    return str_stream.str();
}

std::string ExprLiteral::to_common_string() const {
    std::ostringstream str_stream;
    str_stream << value;
    return str_stream.str();
}

// expr func
ExprFunc::ExprFunc(const std::vector<Expr *> &args) : args(args) {
}

bool ExprFunc::is_operator() const {
    return false;
}

std::string ExprFunc::to_prefix_string() const {
    std::string res;
    res += "( ";
    res += get_function_name() + " ";
    for (const Expr *p_arg: args) {
        res += p_arg->to_prefix_string();
        res += " ";
    }
    res += ")";
    return res;
}

std::string ExprFunc::to_common_string() const {
    std::string res;
    if (!is_operator()) {
        res += get_function_name();
    }
    res += "(";
    bool is_first = true;
    for (const Expr *p_arg: args) {
        if (!is_first) {
            if (!is_operator()) {
                res += ",";
            } 
            else {
                res += get_function_name();
            }
        }
        is_first = false;
        res += p_arg->to_common_string();
    }
    res += ")";
    return res;
}

ExprFunc::~ExprFunc() {
    for (const Expr *p_arg: args) {
        delete p_arg;
    }
}

// add +
bool ExprPlus::is_operator() const {
    return true;
}

ExprPlus::ExprPlus(const std::vector<Expr *> &args) : ExprFunc(args) {

}

std::string ExprPlus::get_function_name() const {
    return "+";
}

double ExprPlus::eval(double x) const {
    double res = 0;
    for (const Expr *p_arg: args) {
        res += p_arg->eval(x);
    }
    return res;
}

// minus -
bool ExprSub::is_operator() const {
    return true;
}

ExprSub::ExprSub(const std::vector<Expr *> &args) : ExprFunc(args) {

}

std::string ExprSub::get_function_name() const {
    return "-";
}

double ExprSub::eval(double x) const {
    return args[0]->eval(x) - args[1]->eval(x);
}

// product *
bool ExprMul::is_operator() const {
    return true;
}

ExprMul::ExprMul(const std::vector<Expr *> &args) : ExprFunc(args) {

}

std::string ExprMul::get_function_name() const {
    return "*";
}

double ExprMul::eval(double x) const {
    double res = 1;
    for (const Expr *p_arg: args) {
        res *= p_arg->eval(x);
    }
    return res;
}

// division /
bool ExprDiv::is_operator() const {
    return true;
}

ExprDiv::ExprDiv(const std::vector<Expr *> &args) : ExprFunc(args) {

}

std::string ExprDiv::get_function_name() const {
    return "/";
}

double ExprDiv::eval(double x) const {
    double denom = args[1]->eval(x);
    // check if the denominator is 0
    if (denom == 0) {
        throw PlotException("division by 0 detected") ;
    }
    return args[0]->eval(x) / denom;
}

// sine
ExprSin::ExprSin(const std::vector<Expr *> &args) : ExprFunc(args) {

}

std::string ExprSin::get_function_name() const {
    return "sin";
}

double ExprSin::eval(double x) const {
    return sin(args[0]->eval(x));
}

// cosine
ExprCos::ExprCos(const std::vector<Expr *> &args) : ExprFunc(args) {

}

std::string ExprCos::get_function_name() const {
    return "cos";
}

double ExprCos::eval(double x) const {
    return cos(args[0]->eval(x));
}
