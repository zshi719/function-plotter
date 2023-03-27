//Zichen Shi (zshi34)

#ifndef EXPR_H
#define EXPR_H

#include <vector>
#include <string>

// Base expression class, where expr is a prefix expression
class Expr {
private:
    // value semantics are prohibited
    Expr(const Expr &);

    Expr &operator=(const Expr &);

public:
    Expr();

    virtual ~Expr();

    virtual double eval(double x) const = 0;

    virtual std::string to_prefix_string() const = 0;

    virtual std::string to_common_string() const = 0;
};

// Derived expression classes
// "X" as the prefix expression 
class ExprX : public Expr {
public:
    double eval(double x) const override;

    std::string to_prefix_string() const override;

    std::string to_common_string() const override;
};

// "pi" as the prefix expression 
class ExprPi : public Expr {
public:
    double eval(double x) const override;

    std::string to_prefix_string() const override;

    std::string to_common_string() const override;
};

// a literal numeric as the prefix expression 
class ExprLiteral : public Expr {
private:
    double value;
public:
    explicit ExprLiteral(double val);

    double eval(double x) const override;

    std::string to_prefix_string() const override;

    std::string to_common_string() const override;
};

// function_name arguments as the prefix expression 
class ExprFunc : public Expr {
protected:
    std::vector<Expr *> args;

    virtual std::string get_function_name() const = 0;

    virtual bool is_operator() const;

public:
    explicit ExprFunc(const std::vector<Expr *> &args);

    double eval(double x) const override = 0;

    std::string to_prefix_string() const override;

    std::string to_common_string() const override;

    ~ExprFunc() override;
};

class ExprPlus : public ExprFunc {
private:
    std::string get_function_name() const override;

    bool is_operator() const override;

public:
    explicit ExprPlus(const std::vector<Expr *> &args);

    double eval(double x) const override;
};

class ExprSub : public ExprFunc {
private:
    std::string get_function_name() const override;

    bool is_operator() const override;

public:
    explicit ExprSub(const std::vector<Expr *> &args);

    double eval(double x) const override;
};

class ExprMul : public ExprFunc {
private:
    std::string get_function_name() const override;

    bool is_operator() const override;

public:
    explicit ExprMul(const std::vector<Expr *> &args);

    double eval(double x) const override;
};

class ExprDiv : public ExprFunc {
private:
    std::string get_function_name() const override;

    bool is_operator() const override;

public:
    explicit ExprDiv(const std::vector<Expr *> &args);

    double eval(double x) const override;
};

class ExprSin : public ExprFunc {
private:
    std::string get_function_name() const override;

public:
    explicit ExprSin(const std::vector<Expr *> &args);

    double eval(double x) const override;
};

class ExprCos : public ExprFunc {
private:
    std::string get_function_name() const override;

public:
    explicit ExprCos(const std::vector<Expr *> &args);

    double eval(double x) const override;
};

#endif // EXPR_H
