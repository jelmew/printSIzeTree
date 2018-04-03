//
// Created by jelmer on 31-3-18.
//

#include "file.h"

bool file::isFile() {
    return false;
}

file::file() {

}

file::file(fs::path _path) : _path(_path) {

}

uintmax_t file::size() const {
    if (fs::is_regular_file(_path)) {
        return fs::file_size(_path);
    }
    if (fs::is_directory(_path)) {
        return directory(_path).get_size();
    }
}

std::string file::name() const {
    return _path.string();
}

directory::directory() {
    //Get current path
    fs::path current_path = fs::current_path();
    for (fs::directory_entry &p: fs::directory_iterator(current_path)) {
        _files.emplace_back(p.path());
    }
}

uintmax_t directory::get_size() {
    uintmax_t size = 0;
    for (const file &file1: _files) {
        size = size + file1.size();
    }
    return size;
}

void directory::print_size_of_files() {
    for (const file &file1: _files) {
        std::cout << "File: " << file1.name() << " size: " << file1.size() << std::endl;
    }
}

directory::directory(fs::path _path) {
    for (fs::directory_entry &p: fs::directory_iterator(_path)) {
        _files.emplace_back(p.path());
    }
}

