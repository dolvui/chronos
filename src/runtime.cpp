#include "runtime.hpp"
#include <iostream>

void Runtime::create_variable(const std::string& name, const std::string& value){
    std::cout << "[runtime] create " << name << " = " << value << "\n";
}

void Runtime::save_state(const std::string &name) {
    std::cout << "[runtime] save_state " << name << "\n";
}

void Runtime::choose_state(const std::vector<std::string>& list) {
  for (auto e : list)
      std::cout << "[runtime] choose_state " << e << "\n";
}

void Runtime::retro(const std::string& name) {
    std::cout << "[runtime] retro " << name << "\n";
}

void Runtime::undo(int n, const std::vector<std::string>* vars) {
  std::cout << "[runtime] undo " << n << "\n";

  if (!vars)
      return;
  for (auto e : *vars)
      std::cout << "[runtime] choose_state " << e << "\n";
}

void Runtime::jump(int n) {
    std::cout << "[runtime] jump " << n << "\n";
}
