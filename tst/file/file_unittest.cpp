//
// Created by jelmer on 31-3-18.
//

#include "src/file/File.h"
#include "gtest/gtest.h"

namespace {
    TEST(filePresentTest, returnsfalse) {
        File f = File();

          ASSERT_FALSE(f.isFile());

    }
}

