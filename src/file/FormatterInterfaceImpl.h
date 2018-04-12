// // Created by amenj on 12-4-18.
//

#ifndef PRINTSIZETREE_FORMATTERINTERFACEIMPL_H
#define PRINTSIZETREE_FORMATTERINTERFACEIMPL_H


#include "FormatterInterface.h"

class FormatterInterfaceImpl : public FormatterInterface {

private:
    void print_file_size_formatted(file_size_in_bytes size_in_bytes, std::string file_path);
    std::vector<std::pair<std::string, file_size_in_bytes>> get_vector_sorted_by_file_size_descending(std::vector<std::pair<std::string,file_size_in_bytes>> unsortedVector) const;
    std::vector<std::string> getSubPaths(const std::string &file_path) const;

public:
    FormatterInterfaceImpl();
    void printSizeTree(std::vector<std::pair<std::string, file_size_in_bytes>>  vector);



};


#endif //PRINTSIZETREE_FORMATTERINTERFACEIMPL_H
