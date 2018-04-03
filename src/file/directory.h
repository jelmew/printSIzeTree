//
// Created by jelmer on 31-3-18.
//

#ifndef PRINTSIZETREE_FILES_H
#define PRINTSIZETREE_FILES_H


#include <vector>
#include "file.h"
#include <boost/filesystem.hpp>
#include <iostream>

namespace fs=boost::filesystem;

class directory {

private:
    std::vector<file> _files ;
public:
    directory();
    directory(fs::path _path);
    uintmax_t get_size();
    void print_size_of_files();
};


#endif //PRINTSIZETREE_FILES_H
