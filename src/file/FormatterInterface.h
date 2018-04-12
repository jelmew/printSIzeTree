//
// Created by amenj on 12-4-18.
//

#ifndef PRINTSIZETREE_FORMATTERINTERFACE_H
#define PRINTSIZETREE_FORMATTERINTERFACE_H


#include <string>
#include <vector>

using file_size_in_bytes = uintmax_t;

class FormatterInterface {
public:
    virtual void printSizeTree(std::vector<std::pair<std::string, file_size_in_bytes>>  vector)= 0;

};


#endif //PRINTSIZETREE_FORMATTERINTERFACE_H
