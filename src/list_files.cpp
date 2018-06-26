#include <string>
#include <iostream>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <my.h>

std::string create_n_path(std::string c_path, std::string to_add){
    if (c_path[c_path.size() - 1] != '/')
        c_path += "/";
    c_path += to_add;
    return (c_path);
}

void create_list(std::vector<std::string> &files, std::string dir){
    std::string     n_path;
    struct dirent   *ent;
    DIR             *rep = opendir(dir.c_str());

    if (rep != NULL){
        while ((ent = readdir(rep)) != NULL)
            if ((std::string)ent->d_name != "." && (std::string)ent->d_name != "..")
            {
                n_path = create_n_path(dir, ent->d_name);
                if (is_dir(n_path))
                    create_list(files, n_path);
                else if (is_src(n_path))
                    files.push_back(n_path);
                else if (is_header(n_path))
                    files.push_back(dir);
            }
        closedir(rep);
    }
}
