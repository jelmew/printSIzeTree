//
// Created by jelmer on 31-3-18.
//

#include "file.h"

bool file::isFile() {
    return false;
}

file::file() {

}

file::file(fs::path _path) : _path(std::move(_path)) {

}

file_size_in_bytes file::size() const {
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

file_size_in_bytes directory::get_size() {
    file_size_in_bytes size = 0;
    for (const file &file1: _files) {
        size = size + file1.size();
    }
    return size;
}

// Driver function to sort the vector elements
// by second element of pairs
bool sort_by_file_size_in_bytes_second_field_of_pair(const std::pair<file, file_size_in_bytes> &a,
                                                     const std::pair<file, file_size_in_bytes> &b) {
    return (a.second > b.second);
}

void directory::print_size_of_files() {
    //Get sorted vector
    std::vector<std::pair<file, file_size_in_bytes>> files_and_respective_sizes = get_vector_sorted_by_file_size_descending();
    for (const std::pair<file, uintmax_t> &sorted_pair: files_and_respective_sizes) {
        print_file_size_formatted(sorted_pair.second, sorted_pair.first.name());
    }
}

std::vector<std::pair<file, file_size_in_bytes>> directory::get_vector_sorted_by_file_size_descending() const {
    std::vector<std::pair<file, file_size_in_bytes >> files_and_respective_sizes;
    //Make pairs to prevent asking size more than once, since this is an IO intensive operation
    for (const file &file1: _files) {
        files_and_respective_sizes.push_back(std::make_pair(file1, file1.size()));
    }
    sort(files_and_respective_sizes.begin(), files_and_respective_sizes.end(),
         sort_by_file_size_in_bytes_second_field_of_pair);
    return files_and_respective_sizes;
}

directory::directory(fs::path _path) {
    try {
        for (fs::directory_entry &p: fs::directory_iterator(_path)) {
            _files.emplace_back(p.path());
        }
    } catch (const std::exception &e) {
        std::vector<std::string> path_split = getSubPaths(_path.string());
        std::cout << "Could not access directory: " << _path.string() << " due to " << e.what() << std::endl;
    }

}

void directory::print_file_size_formatted(file_size_in_bytes size_in_bytes, std::string file_path) {
    std::vector<std::string> file_path_splitted = getSubPaths(file_path);

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

std::vector<std::string> directory::getSubPaths(const std::string &file_path) const {
    std::vector<std::__cxx11::string> file_path_splitted;
    boost::algorithm::split(file_path_splitted, file_path, [](char c) {
        return c == '/';
    });
    return file_path_splitted;
}

