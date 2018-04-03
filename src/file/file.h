//
// Created by jelmer on 31-3-18.
//

#ifndef PRINTSIZETREE_FILE_H
#define PRINTSIZETREE_FILE_H

#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
//#include "directory.h"

namespace fs=boost::filesystem;

class file {
private:
    fs::path _path;
public:
    file();

    file(fs::path _path);
    std::string name()const;
    uintmax_t size() const;

    bool isFile();
};

class directory {
private:
    std::vector<file> _files;
public:
    directory();

    directory(fs::path _path);

    uintmax_t get_size();

    void print_size_of_files(bool sorted=false);
};

#endif //PRINTSIZETREE_FILE_H
