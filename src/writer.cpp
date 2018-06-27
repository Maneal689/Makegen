#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "my.h"

int         get_max_size(std::vector<std::string> files){
    unsigned int     max_size = 0;

    for (unsigned int i = 0; i < files.size(); i++){
        if (files[i].size() > max_size)
            max_size = files[i].size();
    }
    return (max_size);
}

int     get_nb_src(std::vector<std::string> files){
    int     cpt = 0;

    for (unsigned int i = 0; i < files.size(); i++)
        if (is_src(files[i]))
            cpt++;
    return (cpt);
}

std::string     get_language(std::vector<std::string> files){
    for (unsigned int i = 0; i < files.size(); i++){
        if (is_src(files[i])){
            if (files[i][files[i].size()] == 'c')
                return ("c");
            return ("cpp");
        }
    }
    return ("cpp");
}

void        write_srcs(std::vector<std::string> files, std::string EXEC){
    unsigned int    i;
    int             cpt;
    int             size;
    int             nb_src = get_nb_src(files);
    int    max_size = get_max_size(files);
    std::string     language = get_language(files);
    std::ofstream   writer("Makefile");

    writer << "CC\t\t=\t" << (std::string)(language == "cpp" ? "g++" : "gcc") << "\n" << std::endl;
    writer << "EXEC\t=\t" << EXEC << std::endl << std::endl;
    writer << "SRC\t\t=";
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
    writer << "\n\nOBJ\t\t=\t$(SRC:." << language << "=.o)\n" << std::endl;
    writer.close();
}

void write_flags(std::vector<std::string> files){
    unsigned int        i;
    std::vector<int>    header_folder;
    std::ofstream       writer("Makefile", std::ios::app);

    writer << "LDFLAGS\t=\t\n" << std::endl;
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

    writer << "all:\t$(EXEC)\n" << std::endl;
    writer << "$(EXEC):\t$(OBJ)\n\t\t" << "$(CC) -o $(EXEC) $(OBJ)\n" << std::endl;
    writer << "%.o:\t%." << (std::string)(compilator == "g++" ? "cpp" : "c") << "\n\t\t$(CC) -o $@ -c $< $(CFLAGS)\n" << std::endl;
    writer << "clean:\n\t\trm -f $(OBJ)\n" << std::endl;
    writer << "mrproper:\tclean\n\t\trm -f $(EXEC)\n" << std::endl;
    writer << "re:\tmrproper all\n" << std::endl;
    writer << ".PHONY: clean mrproper" << std::endl;
    writer.close();
}

void write_makefile(std::vector<std::string> files, std::string EXEC){
    write_srcs(files, EXEC);
    write_flags(files);
    write_fnc(get_language(files) == "cpp" ? "g++" : "gcc");
}
