cmake_minimum_required (VERSION 3.13.3)

include_directories(include)

project(bstartree)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
# for main.cpp
file(GLOB SOURCES src/bstartree.cpp src/floorplaner.cpp src/fileparser.cpp src/sequencepair.cpp src/size.cpp src/slicingnode.cpp src/polish.cpp src/slicingtree.cpp src/common.cpp src/main.cpp)
add_executable(solution ${SOURCES})
target_link_libraries(solution libgtest.a libgtest_main.a pthread)

# for test.cpp
# file(GLOB SOURCES src/bstartree.cpp src/floorplaner.cpp src/test.cpp)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GTEST")
# add_executable(gtest ${SOURCES})
# target_link_libraries(gtest libgtest.a libgtest_main.a pthread)
