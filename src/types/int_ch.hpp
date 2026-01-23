#pragma once

#include "../runtime.hpp"

struct type_ch {
    virtual ~type_ch() = default;
    virtual std::string to_string() const = 0;
};

////////////////////////////////////////////////////////////
//                      VALUE CLASSES (type_ch)
////////////////////////////////////////////////////////////

struct int_ch : type_ch {
    int data;
    explicit int_ch(int v) : data(v) {}

    std::string to_string() const override {
        return std::to_string(data);
    }
};

struct float_ch : type_ch {
    double data;
    explicit float_ch(double v) : data(v) {}

    std::string to_string() const override {
        return std::to_string(data);
    }
};

struct bool_ch : type_ch {
    bool data;
    explicit bool_ch(bool v) : data(v) {}

    std::string to_string() const override {
        return data ? "true" : "false";
    }
};

////////////////////////////////////////////////////////////
//                      EXPRESSION CLASSES (expr_ch)
////////////////////////////////////////////////////////////

struct expr_ch {
    virtual ~expr_ch() = default;
    virtual type_ch *eval(Runtime &) const = 0;
};

// Literal expressions - wrap values into expressions
struct int_literal : expr_ch {
    int value;

    explicit int_literal(int v) : value(v) {}

    type_ch* eval(Runtime&) const override {
        return new int_ch(value);
    }
};

struct float_literal : expr_ch {
    double value;

    explicit float_literal(double v) : value(v) {}

    type_ch* eval(Runtime&) const override {
        return new float_ch(value);
    }
};

struct bool_literal : expr_ch {
    bool value;

    explicit bool_literal(bool v) : value(v) {}

    type_ch* eval(Runtime&) const override {
        return new bool_ch(value);
    }
};

// Variable reference expression
struct var_expr : expr_ch {
    std::string name;

    explicit var_expr(const std::string& n) : name(n) {}

    type_ch* eval(Runtime& rt) const override;
};

// Binary expression base class
struct binary_expr : expr_ch {
    expr_ch* lhs;
    expr_ch* rhs;

    binary_expr(expr_ch* l, expr_ch* r) : lhs(l), rhs(r) {}

    virtual ~binary_expr() {
        delete lhs;
        delete rhs;
    }
};

struct add_expr : binary_expr {
    using binary_expr::binary_expr;
    type_ch* eval(Runtime& rt) const override;
};

struct minus_expr : binary_expr {
    using binary_expr::binary_expr;
    type_ch* eval(Runtime& rt) const override;
};

struct times_expr : binary_expr {
    using binary_expr::binary_expr;
    type_ch* eval(Runtime& rt) const override;
};

struct divide_expr : binary_expr {
    using binary_expr::binary_expr;
    type_ch* eval(Runtime& rt) const override;
};

struct power_expr : binary_expr {
    using binary_expr::binary_expr;
    type_ch* eval(Runtime& rt) const override;
};

struct parenthesis_expr : expr_ch {
    expr_ch* inner;

    explicit parenthesis_expr(expr_ch* e) : inner(e) {}

    ~parenthesis_expr() {
        delete inner;
    }

    type_ch* eval(Runtime& rt) const override {
        return inner->eval(rt);
    }
};
