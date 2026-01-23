#include <cmath>
#include <stdexcept>

#include <iostream>

#include "int_ch.hpp"


type_ch *var_expr::eval(Runtime &rt) const {
    auto v = rt.get(name);

    if (auto* i = dynamic_cast<int_ch*>(v))
        return new int_ch(i->data);

    if (auto* f = dynamic_cast<float_ch*>(v))
        return new float_ch(f->data);

    if (auto* b = dynamic_cast<bool_ch*>(v))
        return new bool_ch(b->data);

    throw std::runtime_error("Unknown variable type");
}

type_ch *add_expr::eval(Runtime &rt) const {
    auto* l = lhs->eval(rt);
    auto* r = rhs->eval(rt);

    auto* li = dynamic_cast<int_ch*>(l);
    auto* ri = dynamic_cast<int_ch*>(r);

    if (!li || !ri)
        throw std::runtime_error("Type error in +");

    int result = li->data + ri->data;

    delete l;
    delete r;

    return new int_ch(result);
}

type_ch *minus_expr::eval(Runtime &rt) const {
    auto* l = lhs->eval(rt);
    auto* r = rhs->eval(rt);

    auto* li = dynamic_cast<int_ch*>(l);
    auto* ri = dynamic_cast<int_ch*>(r);

    if (!li || !ri)
        throw std::runtime_error("Type error in -");

    int result = li->data - ri->data;

    delete l;
    delete r;

    return new int_ch(result);
}

type_ch *times_expr::eval(Runtime &rt) const {
    auto* l = lhs->eval(rt);
    auto* r = rhs->eval(rt);

    auto* li = dynamic_cast<int_ch*>(l);
    auto* ri = dynamic_cast<int_ch*>(r);

    if (!li || !ri)
        throw std::runtime_error("Type error in *");

    int result = li->data * ri->data;

    delete l;
    delete r;

    return new int_ch(result);
}

type_ch *divide_expr::eval(Runtime &rt) const {
    auto* l = lhs->eval(rt);
    auto* r = rhs->eval(rt);

    auto* li = dynamic_cast<int_ch*>(l);
    auto* ri = dynamic_cast<int_ch*>(r);

    if (!li || !ri)
        throw std::runtime_error("Type error in /");

    if (ri->data == 0)
        throw std::runtime_error("divison by 0");

    int result = li->data / ri->data;

    delete l;
    delete r;

    return new int_ch(result);
}

type_ch *power_expr::eval(Runtime &rt) const {
    auto* l = lhs->eval(rt);
    auto* r = rhs->eval(rt);

    auto* li = dynamic_cast<int_ch*>(l);
    auto* ri = dynamic_cast<int_ch*>(r);

    if (!li || !ri)
        throw std::runtime_error("Type error in /");

    if (ri->data == 0)
        throw std::runtime_error("divison by 0");

    int result = std::pow(li->data,ri->data);

    delete l;
    delete r;

    return new int_ch(result);
}

// type_ch *parenthesis_expr::eval(Runtime &rt) const {
//     (void)rt;return nullptr;
// }
