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

// Driver function to sort the vector elements
// by second element of pairs
bool sortbysec(const std::pair<file, uintmax_t> &a,
               const std::pair<file, uintmax_t> &b) {
    return (a.second < b.second);
}

void directory::print_size_of_files(bool sorted) {
    if (sorted) {
        std::vector<std::pair<file, uintmax_t >> files_and_respective_sizes;
        for (const file &file1: _files) {
            files_and_respective_sizes.push_back(std::make_pair(file1,file1.size()));
        }
        std::sort(files_and_respective_sizes.begin(), files_and_respective_sizes.end(),sortbysec);
        std::reverse(files_and_respective_sizes.begin(), files_and_respective_sizes.end());
        for (const std::pair<file, uintmax_t> &sorted_pair: files_and_respective_sizes) {
            std::cout << "File: " << sorted_pair.first.name() << " size: " << sorted_pair.second << std::endl;
        }
    } else {
        for (const file &file1: _files) {
            std::cout << "File: " << file1.name() << " size: " << file1.size() << std::endl;
        }
    }
}

directory::directory(fs::path _path) {
    for (fs::directory_entry &p: fs::directory_iterator(_path)) {
        _files.emplace_back(p.path());
    }
}

