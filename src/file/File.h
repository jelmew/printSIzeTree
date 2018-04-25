//
// Created by jelmer on 31-3-18.
//

#ifndef PRINTSIZETREE_FILE_H
#define PRINTSIZETREE_FILE_H

#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <boost/algorithm/string.hpp>
#include <sys/stat.h>

namespace fs=boost::filesystem;
typedef uintmax_t file_size_in_bytes;

class File {
private:
    fs::path _path;
    file_size_in_bytes file_size_in_bytes1;
    uintmax_t  size_on_disk;
public:
    File();

    File(fs::path _path);

    std::string name() const;

    uintmax_t size() const;

    bool isFile();
};


#endif //PRINTSIZETREE_FILE_H
