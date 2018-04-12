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

namespace fs=boost::filesystem;
typedef  uintmax_t file_size_in_bytes;
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



#endif //PRINTSIZETREE_FILE_H
