// Zichen Shi (zshi34)

#include <string>
#include <sstream>
#include <memory>
#include "exception.h"
#include "expr.h"
#include "expr_parser.h"

ExprParser::ExprParser() {
}

ExprParser::~ExprParser() {
}


// recursively parses the tokens by calling parse_tokens and return a pointer to Expr object
Expr *ExprParser::parse(std::istream &in) {

    std::vector<std::string> tokens;
    std::string token;

    // a variable used to check if the left and right parentheses are balanced
    int dep = 0;

    //read the token from the input stream
    while (in >> token) {
        tokens.push_back(token);
        if (token == "(") {
            ++dep;
        }
        else if (token == ")") {
            --dep;
            if (dep == 0) {
                break;
            }
        }
        // if the function is "x"
        else if (tokens.size() == 1){
            break;
        }
        if (in.eof()) {
            break;
        }
    }

    size_t ind = 0;
    Expr *res;
    try {
        res = parse_tokens(tokens, ind);
        if (ind != tokens.size()) {
            throw PlotException("parsing incomplete");
        }
    } catch (const PlotException &e) {
        // error message
        std::string msg =
                "invalid expression tokens: (error " + std::string(e.what()) + " at " + std::to_string(ind) + "): [";
        for (size_t i = 0; i < tokens.size(); ++i) {
            if (i != 0) {
                msg += ", ";
            }
            msg += std::to_string(i) + ":" + tokens[i];

        }
        msg += "]";
        throw PlotException(msg);
    }
    return res;
}

// if parse beyond the end of file
void ExprParser::check_tokens_index(const std::vector<std::string>& tokens, size_t &ind) {
    if (ind >= tokens.size()) {
        throw PlotException("Error: reached end of file while parsing");
    }
}

// check function name and num of args
void ExprParser::check_func_expr(const std::string &func_name, const std::vector<Expr *>& args) {
    // a variable representing num of args passed to a function
    size_t arg_in;

    // sin and cos functions should have exactly one argument expression
    if (func_name == "sin" || func_name == "cos") {
        arg_in = 1;
    }
    // - and / functions should have exactly two argument expressions
    else if (func_name == "-" || func_name == "/") {
        arg_in = 2;
    }
    // + and * functions may have any number (0 or more) of argument expressions
    else if (func_name == "+" || func_name == "*") {
        arg_in = 0;
    }
    else {
        throw PlotException("invalid function name: " + func_name);
    }

    if (arg_in > 0 && args.size() != arg_in) {
        throw PlotException(
                "function " + func_name + " needs " + std::to_string(arg_in)
                + " argument expression(s) but gets " + std::to_string(args.size()));
    }
}

// a helper method to evaluate and parse the tokens
Expr *ExprParser::parse_tokens(const std::vector<std::string>& tokens, size_t &ind) {
    check_tokens_index(tokens, ind);
    // function
    if (tokens[ind] == "(") {
        check_tokens_index(tokens, ++ind);
        const std::string& func_name = tokens[ind];
        check_tokens_index(tokens, ++ind);
        std::vector<Expr *> args;
        while (tokens[ind] != ")") {
            args.push_back(parse_tokens(tokens, ind));
        }
        check_func_expr(func_name, args);
        ++ind;
        if (func_name == "sin") {
            return new ExprSin(args);
        }
        else if (func_name == "cos") {
            return new ExprCos(args);
        }
        else if (func_name == "+") {
            return new ExprPlus(args);
        }
        else if (func_name == "-") {
            return new ExprSub(args);
        }
        else if (func_name == "*") {
            return new ExprMul(args);
        }
        else if (func_name == "/") {
            return new ExprDiv(args);
        }
        throw PlotException("invalid function name: " + func_name);
    }

    // x
    else if (tokens[ind] == "x") {
        ++ind;
        return new ExprX();
    }
    // pi
    else if (tokens[ind] == "pi") {
        ++ind;
        return new ExprPi();
    }
    // number
    else {
        double val;
        try {
            val = std::stod(tokens[ind]);
        } catch (...) {
            throw PlotException("unparseable number error: " + tokens[ind]);
        }
        ++ind;
        return new ExprLiteral(val);
    }
}