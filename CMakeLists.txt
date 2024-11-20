cmake_minimum_required(VERSION 3.27.2)

project(io_filter)

add_executable(io_filter 
    ip_filter.cpp
)

set_target_properties(io_filter PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)