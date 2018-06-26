#include <string>
#include <iostream>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>

bool is_dir(std::string path){
    struct stat     buffer;

    if (lstat(path.c_str(), &buffer) == -1)
        return (false);
    else if ((buffer.st_mode & S_IFMT) == S_IFDIR)
        return (true);
    return (false);
}

bool is_src(std::string path){
    if (path[path.size() - 1] == 'p' &&
            path[path.size() - 2] == 'p' &&
            path[path.size() - 3] == 'c' &&
            path[path.size() - 4] == '.' )
        return (true);
    else if (path[path.size() - 1] == 'c' &&
            path[path.size() - 2] == '.')
        return (true);
    return (false);
}

bool is_header(std::string path){
    if (path[path.size() - 1] == 'h' &&
            path[path.size() - 2] == '.')
        return (true);
    return (false);
}
