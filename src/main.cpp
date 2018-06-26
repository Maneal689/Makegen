#include <iostream>
#include <string>
#include <vector>
#include "my.h"

int main(int argc, char **argv){
    std::vector<std::string>    files;
    std::string                 name;

    create_list(files, ".");
    name = (argc > 1) ? (std::string)argv[1] : "a.out";
    write_makefile(files, name);
    return (0);
}
