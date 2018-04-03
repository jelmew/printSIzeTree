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
    } if(fs::is_directory(_path)){
//       directory(_path);
    }
}

