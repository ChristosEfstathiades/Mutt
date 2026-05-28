cmake_minimum_required(VERSION 3.20)
project(Mutt)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wpedantic)

add_subdirectory(src)

add_executable(mutt main.cpp)
target_include_directories(mutt PRIVATE include)
target_link_libraries(mutt PRIVATE mutt_lib)
