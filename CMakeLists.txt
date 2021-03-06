cmake_minimum_required(VERSION 3.9)
project(printSizeTree)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif ()


find_package(Boost COMPONENTS system thread filesystem  REQUIRED)
include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Boost_INCLUDE_DIRS}
)


# Now simply link against gtest or gtest_main as needed. Eg
add_executable(odu src/main.cpp src/file/File.cpp src/file/File.h src/main.cpp src/file/Directory.cpp src/file/Directory.h src/file/FormatterInterface.cpp src/file/FormatterInterface.h src/file/FormatterInterfaceImpl.cpp src/file/FormatterInterfaceImpl.h)
add_executable(printSizeTree_test tst/main.cpp src/file/File.cpp src/file/File.h)
target_link_libraries(odu
        ${Boost_LIBRARIES}
        )
target_link_libraries(printSizeTree_test
        gtest_main
        ${Boost_LIBRARIES}
        )
add_test(NAME example_test COMMAND printSizeTree_test)

install(TARGETS odu RUNTIME DESTINATION $ENV{HOME}/bin)