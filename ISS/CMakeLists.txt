cmake_minimum_required(VERSION 3.10)
project(zimji LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/inc)

add_subdirectory(src)