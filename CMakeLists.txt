cmake_minimum_required(VERSION 3.27)
project(pbnano C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

add_library(pbnano STATIC pbnano.h pbnano.c pbnano_detail.h pbnano_detail.c)
target_compile_options(pbnano PRIVATE -Wall -Wextra)

add_executable(pbnano-util main.cc)
target_link_libraries(pbnano-util PRIVATE pbnano)
target_compile_options(pbnano-util PRIVATE -Wall -Wextra)
