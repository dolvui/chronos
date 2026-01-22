#pragma once
#include <string>
#include <vector>

// foward declaration
struct type_ch;

class Runtime {
private:
public:
    void create_variable(type_ch&, type_ch& value);
    void save_state(type_ch&);
    void choose_state(const std::vector<type_ch>& list);
    void retro(type_ch& var);
    void undo(int n, const std::vector<type_ch>* vars);
    void jump(int n);
};
