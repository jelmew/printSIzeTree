//
// Created by amenj on 12-4-18.
//

#ifndef PRINTSIZETREE_DIRECTORY_H
#define PRINTSIZETREE_DIRECTORY_H

#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <boost/algorithm/string.hpp>
#include "file.h"

class Directory {
private:
    std::vector<file> _files;
    std::vector<Directory> directories;
    fs::path _path;

    void print_file_size_formatted(file_size_in_bytes size_in_bytes, std::string file_path);

public:
    Directory();

    Directory(fs::path _path);

    file_size_in_bytes get_size() const;

    void print_size_tree();

    std::vector<std::pair<std::string, file_size_in_bytes>> get_vector_sorted_by_file_size_descending() const;

    std::vector<std::string> getSubPaths(const std::string &file_path) const;

    std::string name() const;
};


#endif //PRINTSIZETREE_DIRECTORY_H
