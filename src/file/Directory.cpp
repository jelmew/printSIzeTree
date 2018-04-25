//
// Created by amenj on 12-4-18.
//

#include "Directory.h"

using std::string;

Directory::Directory(FormatterInterface *formatterInterface) {
    this->formatterInterface = formatterInterface;
    _path = fs::current_path();
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


Directory::Directory(boost::filesystem::path _path) {
    this->formatterInterface = nullptr;
    this->_path = _path;
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
}

std::string Directory::name() const {
    return _path.string();
}

