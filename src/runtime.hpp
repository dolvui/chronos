#pragma once

#include <string>
#include <vector>
#include <unordered_map>

// foward declaration
struct type_ch;

class Runtime {
private:
    std::unordered_map<std::string, type_ch*> vars;

public:
    type_ch* get(const std::string& name) const;
    void set(const std::string &name, type_ch *value);

    void create_variable(type_ch&, type_ch& value);
    void save_state(type_ch&);
    void choose_state(const std::vector<type_ch>& list);
    void retro(type_ch& var);
    void undo(int n, const std::vector<type_ch>* vars);
    void jump(int n);
};
