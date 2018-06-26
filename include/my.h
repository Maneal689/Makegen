#ifndef MY_H_
#define MY_H_

#include <vector>

void create_list(std::vector<std::string> &, std::string);
bool is_dir(std::string);
bool is_src(std::string);
bool is_header(std::string);
void write_makefile(std::vector<std::string>, std::string);

#endif // MY_H_
