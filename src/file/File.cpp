//
// Created by jelmer on 31-3-18.
//

#include "File.h"


File::File() {

}

File::File(fs::path _path) : _path(std::move(_path)) {

}

file_size_in_bytes File::size() const {
    if (fs::is_regular_file(_path)) {
        struct stat statbuf;
        if(stat(_path.string().c_str(),&statbuf)==-1) {

            throw std::runtime_error(_path.string() + ":Not an File");
        }
        return static_cast<file_size_in_bytes>(statbuf.st_size);
    }
    throw std::runtime_error(_path.string() + ":Not an File");
}

std::string File::name() const {
    return _path.string();
}

bool File::isFile() {
    return false;
}



