//
// Created by jelmer on 31-3-18.
//

#include "file.h"


file::file() {

}

file::file(fs::path _path) : _path(std::move(_path)) {

}

file_size_in_bytes file::size() const {
    if (fs::is_regular_file(_path)) {
        return fs::file_size(_path);
    }
    throw std::runtime_error(_path.string() + ":Not an file");
}

std::string file::name() const {
    return _path.string();
}

bool file::isFile() {
    return false;
}



