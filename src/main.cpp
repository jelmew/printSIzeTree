//
// Created by jelmer on 31-3-18.
//


#include <iostream>
#include <src/file/File.h>
#include <src/file/Directory.h>
#include <src/file/FormatterInterfaceImpl.h>


int main(int argc, char **argv) {
    FormatterInterfaceImpl *anInterface = new FormatterInterfaceImpl();
    Directory(anInterface).print_size_tree();

    delete(anInterface);
    return 0;
};