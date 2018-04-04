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

class directory {
private:
    std::vector<file> _files;
    void print_file_size_formatted(file_size_in_bytes size_in_bytes, std::string file_path);
public:
    directory();
    directory(fs::path _path);
    file_size_in_bytes get_size();
    void print_size_of_files();

    std::vector<std::pair<file, file_size_in_bytes>> get_vector_sorted_by_file_size_descending() const;
};

#endif //PRINTSIZETREE_FILE_H
