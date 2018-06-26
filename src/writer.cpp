#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "my.h"

int         get_max_size(std::vector<std::string> files){
    int     max_size = 0;

    for (int i = 0; i < files.size(); i++){
        if (files[i].size() > max_size)
            max_size = files[i].size();
    }
    return (max_size);
}

int     get_nb_src(std::vector<std::string> files){
    int     cpt = 0;

    for (int i = 0; i < files.size(); i++)
        if (is_src(files[i]))
            cpt++;
    return (cpt);
}

std::string     get_language(std::vector<std::string> files){
    for (int i = 0; i < files.size(); i++){
        if (is_src(files[i])){
            if (files[i][files[i].size()] == 'c')
                return ("c");
            return ("cpp");
        }
    }
    return ("cpp");
}

void        write_srcs(std::vector<std::string> files, std::string name){
    int             i;
    int             j;
    int             cpt;
    int             size;
    int             nb_src = get_nb_src(files);
    int             max_size = get_max_size(files);
    std::string     language = get_language(files);
    std::ofstream   writer("Makefile");

    writer << "NAME\t=\t" << name << std::endl << std::endl;
    writer << "SRCS\t=";
    i = 0;
    cpt = 0;
    while (i < files.size()){
        if (is_src(files[i])){
            if (cpt == 0)
                writer << "\t";
            else
                writer << "\t\t\t";

            writer << files[i];

            //Number of tabs to make backslashs on the same width;
            if (cpt != nb_src - 1){
                size = (int)(max_size / 4) - ((int)(files[i].size() / 4)) + 1;
                for (int j = 0; j < size; j++)
                    writer << "\t";
                writer << "\\" << std::endl;
            }

            cpt++;
        }
        i++;
    }
    writer << "\n\nOBJS\t=\t$(SRCS:." << language << "=.o)\n" << std::endl;
    writer.close();
}

void write_flags(std::vector<std::string> files){
    int     i;
    std::vector<int>    header_folder;
    std::ofstream    writer("Makefile", std::ios::app);

    writer << "CFLAGS\t=\t-W -Wall -Wextra -Werror" << std::endl;
    i = 0;
    while (i < files.size()){
        if (!is_src(files[i]))
            header_folder.push_back(i);
        i++;
    }

    if (header_folder.size() > 0){
          writer << "CFLAGS\t+=\t-I";
          i = 0;
          while (i < header_folder.size()){
              writer << " " << files[header_folder[i]];
              i++;
          }
          writer << std::endl;
    }
    else
        writer << "#CFLAGS\t+=\t-I" << std::endl;
    writer << std::endl;
    writer.close();
}

void write_fnc(std::string compilator){
    std::ofstream    writer("Makefile", std::ios::app);

    writer << "all:\t$(NAME)\n" << std::endl;
    writer << "$(NAME):\n\t\t" << compilator << " -o $(NAME) $(OBJS) $(CFLAGS)\n" << std::endl;
    writer << "clean:\n\t\trm -f $(OBJS)\n" << std::endl;
    writer << "fclean:\tclean\n\t\trm -f $(NAME)\n" << std::endl;
    writer << "re:\tfclean all" << std::endl;
}

void write_makefile(std::vector<std::string> files, std::string name){
    write_srcs(files, name);
    write_flags(files);
    write_fnc(get_language(files) == "cpp" ? "g++" : "gcc");
}
