//
// Created by amenj on 12-4-18.
//

#include "Directory.h"

using std::string;

Directory::Directory(FormatterInterface *formatterInterface){
    //Get current path
    this->formatterInterface=formatterInterface;
    _path = fs::current_path();
    for (fs::directory_entry p: fs::directory_iterator(_path)) {
        if (fs::is_regular_file(p)) {
            _files.push_back(File(p));
        } else if (fs::is_directory(p)) {
            directories.push_back(Directory(p, formatterInterface));
        }
    }
}

file_size_in_bytes Directory::get_size() const {
    file_size_in_bytes size = 0;
    for (const auto &file1: _files) {
        size = size + file1.size();
    }
    for (const auto &directory: directories) {
        size += 4000;
        size += directory.get_size();
    }

    return size;
}

void Directory::print_size_tree() {
    //Get sorted vector
    std::vector<std::pair<string, file_size_in_bytes>> files_and_respective_sizes = get_vector();
    formatterInterface->printSizeTree(files_and_respective_sizes);

}

std::vector<std::pair<string, file_size_in_bytes>> Directory::get_vector() const {
    std::vector<std::pair<string, file_size_in_bytes >> file_or_directory_names_and_respective_sizes;
    //Make pairs to prevent asking size more than once, since this is an IO intensive operation
    for (const File &file1: _files) {
        file_or_directory_names_and_respective_sizes.push_back(std::make_pair(file1.name(), file1.size()));
    }
    for (auto &directory :directories) {
        file_or_directory_names_and_respective_sizes.push_back(std::make_pair(directory.name(), directory.get_size()));
    }
    return file_or_directory_names_and_respective_sizes;
}


Directory::Directory(const boost::filesystem::path _path, FormatterInterface *formatterInterface) {
    this->formatterInterface = formatterInterface;
    this->_path = _path;
    try {
        for (fs::directory_entry &p: fs::directory_iterator(_path)) {
            if (fs::is_regular_file(p)) {
                _files.push_back(File(p));
            } else if (fs::is_directory(p)) {
                directories.push_back(Directory(p, formatterInterface));
            }
        }
    } catch (const std::exception &e) {
        std::cout << "Could not access Directory: " << _path.string() << " due to " << e.what() << std::endl;
    }

}


std::string Directory::name() const {
    return _path.string();
}

