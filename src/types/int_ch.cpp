#include "int_ch.hpp"

// type_ch& type_ch::operator+(type_ch& type) {
//     return type;
// }

// std::ostream &type_ch::operator<<(std::ostream &os) {
//   os << "type_ch data" << std::endl;
//   return os;
// }

// int int_ch::operator+(int_ch& idx) {
//     return idx.data + data;
// }

type_ch* var_expr::eval(Runtime &rt) const {
    (void)rt;return nullptr;
}

type_ch *add_expr::eval(Runtime &rt) const {
    (void)rt;return nullptr;
}

type_ch *minus_expr::eval(Runtime &rt) const {
    (void)rt;return nullptr;
}

type_ch *times_expr::eval(Runtime &rt) const {
    (void)rt;return nullptr;
}

type_ch *divide_expr::eval(Runtime &rt) const {
    (void)rt;return nullptr;
}

type_ch *power_expr::eval(Runtime &rt) const {
    (void)rt;return nullptr;
}

// type_ch *parenthesis_expr::eval(Runtime &rt) const {
//     (void)rt;return nullptr;
// }
