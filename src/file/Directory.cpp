//
// Created by amenj on 12-4-18.
//

#include "Directory.h"

using std::string;

Directory::Directory(FormatterInterface *formatterInterface) {
    size_on_disk=4000;
    this->formatterInterface = formatterInterface;
    _path = fs::current_path();
    for (const fs::directory_entry &p: fs::directory_iterator(_path)) {
        if (fs::is_regular_file(p)) {
            const File &file = File(p.path());
            size_on_disk += file.size();
            _files.push_back(file);
        } else if (fs::is_directory(p)) {
            Directory directory = Directory(p.path());
            size_on_disk += directory.get_size();
            directories.push_back(directory);
        }
    }
}

file_size_in_bytes Directory::get_size() const {
    return size_on_disk;
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


Directory::Directory(boost::filesystem::path _path) {
    //The sie of an empty directory on disk
    this->size_on_disk=4000;
    this->formatterInterface = nullptr;
    this->_path = _path;
    try {
        for (fs::directory_entry p: fs::directory_iterator(_path)) {
            if (fs::is_regular_file(p)) {
                const File &file = File(p.path());
                size_on_disk += file.size();
                _files.push_back(file);
            } else if (fs::is_directory(p)) {
                const Directory &directory = Directory(p.path());
                size_on_disk += directory.get_size();
                directories.push_back(directory);
            }
        }
    } catch (const fs::filesystem_error &e) {
        std::cout << "Could not list" << _path << std::endl;
    }
}

std::string Directory::name() const {
    return _path.string();
}

