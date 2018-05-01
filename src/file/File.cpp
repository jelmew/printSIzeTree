//
// Created by jelmer on 31-3-18.
//

#include "File.h"


File::File() : file_size_in_bytes1{0} {
}

File::File(fs::path _path1) : _path{_path1} {
    //file_size_in_bytes1 = fs::file_size(_path);
    if (fs::is_regular_file(_path)) {
        struct stat statbuf{};
        if (stat(_path.string().c_str(), &statbuf) == -1) {
            std::cout<<"Size on disk error"<<std::endl;
            throw std::runtime_error(_path.string() + ":Not an File");
        }
        size_on_disk = static_cast<file_size_in_bytes>(statbuf.st_blocks*512);
        return;
    }
    throw std::runtime_error(_path.string() + ":Not an File");
}

file_size_in_bytes File::size() const {
    if (fs::is_regular_file(_path)) {
        return size_on_disk;
    }
    throw std::runtime_error(_path.string() + ":Not an File");
}

std::string File::name() const {
    return _path.string();
}

bool File::isFile() {
    return false;
}



