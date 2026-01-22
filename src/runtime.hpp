#pragma once
#include <string>
#include <vector>

class Runtime {
private:
public:
    void create_variable(const std::string&, const std::string&);
    void save_state(const std::string&);
    void choose_state(const std::vector<std::string>& list);
    void retro(const std::string& var);
    void undo(int n, const std::vector<std::string>* vars);
    void jump(int n);
};
