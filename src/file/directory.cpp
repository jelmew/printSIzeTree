//
// Created by jelmer on 31-3-18.
//

#include "directory.h"


directory::directory() {
    //Get current path
    fs::path current_path = fs::current_path();
    for (fs::directory_entry &p: fs::directory_iterator(current_path)) {
        _files.emplace_back(p.path());
/*        if(fs::is_directory(p)){
            directory(p.path());
        } else {
            std::cout << p << std::endl;
            std::cout << fs::file_size(p.path()) << std::endl;
        }*/
    }
}

uintmax_t directory::get_size() {
    uintmax_t size = 0;
    for (const file &file1: _files) {
        size += file1.size();
    }
}

void directory::print_size_of_files() {
    for (const file &file1: _files) {
        std::cout << file1.size();
    }
}

directory::directory(fs::path _path) {
    for (fs::directory_entry &p: fs::directory_iterator(_path)) {
        _files.emplace_back(p.path());
    }
}
