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
#include "File.h"
#include "FormatterInterface.h"

class Directory {
private:


    std::vector<File> _files;
    std::vector<Directory> directories;
    fs::path _path;
    FormatterInterface *formatterInterface;
    file_size_in_bytes size_on_disk;

public:
    Directory(FormatterInterface *formatterInterface);

    explicit Directory(boost::filesystem::path _path);

    //Directory(fs::path _path, FormatterInterface *formatterInterface);

    file_size_in_bytes get_size() const;

    void print_size_tree();

    std::vector<std::pair<std::string, file_size_in_bytes>> get_vector() const;

    std::string name() const;
};


#endif //PRINTSIZETREE_DIRECTORY_H
