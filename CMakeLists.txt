cmake_minimum_required(VERSION 3.10)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

ExternalProject_Add(jsoncpp
    TMP_DIR build/jsoncpp
    DOWNLOAD_DIR third_party
    GIT_REPOSITORY "https://github.com/open-source-parsers/jsoncpp.git"
)

PROJECT(iex_cpp_api C CXX)
set (CMAKE_CXX_STANDARD 17)

set(LIB_SOURCES 
    IEX.cpp
)

add_library(iex_api SHARED ${LIB_SOURCES})

