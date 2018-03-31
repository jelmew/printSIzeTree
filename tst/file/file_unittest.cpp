//
// Created by jelmer on 31-3-18.
//

#include "../../src/file/file.h"
#include "gtest/gtest.h"

namespace {
    TEST(filePresentTest, returnsfalse) {
        file f = file();

          ASSERT_FALSE(f.isFile());

    }
}

