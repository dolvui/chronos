#include <iostream>

#include "runtime.hpp"
#include "types/int_ch.hpp"

void Runtime::create_variable(type_ch& name, type_ch& value) {
    std::cout << "[runtime] create " << name.to_string() << " = " << value.to_string() << "\n";
}

void Runtime::save_state(type_ch& name) {
    std::cout << "[runtime] save_state " << name.to_string() << "\n";
}

void Runtime::choose_state(const std::vector<type_ch>& list) {
    (void)list;
    std::cout << "[runtime] choose_state \n";
}

void Runtime::retro(type_ch& name) {
    std::cout << "[runtime] retro " << name.to_string() << "\n";
}

void Runtime::undo(int n, const std::vector<type_ch>* vars) {
  std::cout << "[runtime] undo " << n << "\n";
  (void)vars;
  if (!vars)
      return;
  std::cout << "[runtime] choose_state \n";
}

void Runtime::jump(int n) {
    std::cout << "[runtime] jump " << n << "\n";
}
