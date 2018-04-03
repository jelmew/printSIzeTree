//
// Created by jelmer on 31-3-18.
//

#include "files.h"


files::files() {
    //Get current path
    fs::path current_path = fs::current_path();
    for (fs::directory_entry &p: fs::directory_iterator(current_path)) {
        std::cout << p << std::endl;
        std::cout << fs::file_size(p.path()) << std::endl;
    }
}
