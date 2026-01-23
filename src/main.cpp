#include <iostream>
#include <string>
#include "runtime.hpp"
#include <iostream>

Runtime runtime;
Runtime *g_runtime = &runtime;

extern FILE* yyin;
int yyparse();

int check_extension(std::string file) {
    int size = file.length();
    return file.substr(size - 3, size).compare(".ch");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./chronos <file>.ch\n";
        return 1;
    }

    std::string filename(argv[1]);

    if (check_extension(filename)) {
        std::cerr << "Wrong extension : .ch needed !";
        return 1;
    }

    yyin = fopen(filename.c_str(), "r");
    if (!yyin) {
        std::cerr << "Cannot open file\n";
        return 1;
    }

    int result = yyparse();

    if (result != 0) std::cerr << "Parse errors found\n";

    fclose(yyin);
    return 0;
}
