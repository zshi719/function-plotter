// Zichen Shi (zshi34)

#ifndef FN_PARSER_H
#define FN_PARSER_H

#include <iostream>
#include "expr.h"

class ExprParser {
private:
    // value semantics are prohibited
    ExprParser(const ExprParser &);

    ExprParser &operator=(const ExprParser &);

    // private helper function to parses the tokens and return a pointer to Expr
    Expr *parse_tokens(const std::vector<std::string>& tokens, size_t &ind);

    // if parse beyond the end of file
    static void check_tokens_index(const std::vector<std::string>& tokens, size_t &ind);

    // check both the function name and the number of arguments
    static void check_func_expr(const std::string &func_name, const std::vector<Expr *>& args);

public:
    ExprParser();

    ~ExprParser();

    // calls on parse_tokens to recursively parse and evaluate the tokens; store the parsed object
    Expr *parse(std::istream &in);

};

#endif // FN_PARSER_H