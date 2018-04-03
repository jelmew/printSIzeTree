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
class files {

private:
    std::vector<file> _files;
public:
    files();
};


#endif //PRINTSIZETREE_FILES_H
