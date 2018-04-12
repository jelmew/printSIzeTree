//
// Created by amenj on 12-4-18.
//

#include <iostream>
#include <cmath>
#include <iomanip>
#include <boost/algorithm/string/split.hpp>

#include <boost/filesystem.hpp>
#include "FormatterInterfaceImpl.h"

using std::string;
using std::cout;
using std::setw;
namespace fs=boost::filesystem;

FormatterInterfaceImpl::FormatterInterfaceImpl() {}

void FormatterInterfaceImpl::printSizeTree(std::vector<std::pair<std::string, file_size_in_bytes>> vector) {
    const std::vector<std::pair<string, file_size_in_bytes>> &sortedVector = get_vector_sorted_by_file_size_descending(
            vector);
    for (const std::pair<string, uintmax_t> &sorted_pair: sortedVector) {
        print_file_size_formatted(sorted_pair.second, sorted_pair.first);
    }
}

void FormatterInterfaceImpl::print_file_size_formatted(file_size_in_bytes size_in_bytes, std::string file_path) {
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

std::vector<std::string> FormatterInterfaceImpl::getSubPaths(const std::string &file_path) const {
    std::vector<std::__cxx11::string> file_path_splitted;
    boost::algorithm::split(file_path_splitted, file_path, [](char c) {
        return c == fs::path::preferred_separator;
    });
    return file_path_splitted;
}

bool sort_by_file_size_in_bytes_second_field_of_pair(const std::pair<string, file_size_in_bytes> &a,
                                                     const std::pair<string, file_size_in_bytes> &b) {
    return (a.second > b.second);
}

std::vector<std::pair<std::string, file_size_in_bytes>>
FormatterInterfaceImpl::get_vector_sorted_by_file_size_descending(
        std::vector<std::pair<std::string, file_size_in_bytes>> unsortedVector) const {
    sort(unsortedVector.begin(), unsortedVector.end(),
         sort_by_file_size_in_bytes_second_field_of_pair);
    return unsortedVector;
}


