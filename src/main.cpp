//
// Created by jelmer on 31-3-18.
//


#include <iostream>
#include <src/file/file.h>


int main(int argc, char **argv) {


    std::cout << "Hello World" << std::endl;
    //std::cout << "Total size directory is: " << directory().get_size() << std::endl;
    directory().print_size_of_files();
    return 0;
};