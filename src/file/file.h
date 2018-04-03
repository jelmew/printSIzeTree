//
// Created by jelmer on 31-3-18.
//

#ifndef PRINTSIZETREE_FILE_H
#define PRINTSIZETREE_FILE_H

#include <boost/filesystem.hpp>
#include <iostream>
//#include "directory.h"

namespace fs=boost::filesystem;

class file {
private:
    fs::path _path;
public:
    file();

    file(fs::path _path);

    uintmax_t size() const;

    bool isFile();
};


#endif //PRINTSIZETREE_FILE_H
