//
// Created by amenj on 12-4-18.
//

#include "Directory.h"

using std::string;

Directory::Directory() {
    //Get current path
    _path = fs::current_path();
    for (fs::directory_entry p: fs::directory_iterator(_path)) {
        if (fs::is_regular_file(p)) {
            _files.push_back(file(p));
        } else if (fs::is_directory(p)) {
            directories.push_back(Directory(p));
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

// Driver function to sort the vector elements
// by second element of pairs
bool sort_by_file_size_in_bytes_second_field_of_pair(const std::pair<string, file_size_in_bytes> &a,
                                                     const std::pair<string, file_size_in_bytes> &b) {
    return (a.second > b.second);
}

void Directory::print_size_tree() {
    //Get sorted vector
    std::vector<std::pair<string, file_size_in_bytes>> files_and_respective_sizes = get_vector_sorted_by_file_size_descending();
    for (const std::pair<string, uintmax_t> &sorted_pair: files_and_respective_sizes) {
        print_file_size_formatted(sorted_pair.second, sorted_pair.first);
    }
}

std::vector<std::pair<string, file_size_in_bytes>> Directory::get_vector_sorted_by_file_size_descending() const {
    std::vector<std::pair<string, file_size_in_bytes >> file_or_directory_names_and_respective_sizes;
    //Make pairs to prevent asking size more than once, since this is an IO intensive operation
    for (const file &file1: _files) {
        file_or_directory_names_and_respective_sizes.push_back(std::make_pair(file1.name(), file1.size()));
    }
    for (auto &directory :directories) {
        file_or_directory_names_and_respective_sizes.push_back(std::make_pair(directory.name(), directory.get_size()));
    }
    sort(file_or_directory_names_and_respective_sizes.begin(), file_or_directory_names_and_respective_sizes.end(),
         sort_by_file_size_in_bytes_second_field_of_pair);
    return file_or_directory_names_and_respective_sizes;
}

Directory::Directory(fs::path _path) {
    this->_path = _path;
    try {
        for (fs::directory_entry &p: fs::directory_iterator(_path)) {
            if (fs::is_regular_file(p)) {
                _files.push_back(file(p));
            } else if (fs::is_directory(p)) {
                directories.push_back(Directory(p));
            }
        }
    } catch (const std::exception &e) {
        std::vector<string> path_split = getSubPaths(_path.string());
        std::cout << "Could not access Directory: " << _path.string() << " due to " << e.what() << std::endl;
    }

}

void Directory::print_file_size_formatted(file_size_in_bytes size_in_bytes, string file_path) {
    std::vector<string> file_path_splitted = getSubPaths(file_path);

    int number_of_digits = static_cast<int>(std::log10(size_in_bytes));
    if (number_of_digits >= 9) {
        std::cout << std::setw(0) << round(float(size_in_bytes) / 10e8) << "GB" << std::setw(20 - number_of_digits + 9)
                  << "  "
                  << file_path_splitted[file_path_splitted.size() - 1]
                  << std::endl;
    } else if (number_of_digits >= 6) {
        std::cout << std::setw(0) << round(float(size_in_bytes) / 10e5) << "MB" << std::setw(20 - number_of_digits + 6)
                  << "  "
                  << file_path_splitted[file_path_splitted.size() - 1]
                  << std::endl;
    } else if (number_of_digits >= 3) {
        std::cout << std::setw(0) << round(float(size_in_bytes) / 10e2) << "KB" << std::setw(20 - number_of_digits + 3)
                  << "  "
                  << file_path_splitted[file_path_splitted.size() - 1]
                  << std::endl;
    } else {
        std::cout << std::setw(0) << size_in_bytes << "b" << std::setw(20 - number_of_digits + 1) << "  "
                  << file_path_splitted[file_path_splitted.size() - 1]
                  << std::endl;
    }
}

std::vector<string> Directory::getSubPaths(const string &file_path) const {
    std::vector<std::__cxx11::string> file_path_splitted;
    boost::algorithm::split(file_path_splitted, file_path, [](char c) {
        return c == fs::path::preferred_separator;
    });
    return file_path_splitted;
}

std::string Directory::name() const {
    return _path.string();
}
