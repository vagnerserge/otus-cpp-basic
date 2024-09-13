cmake_minimum_required(VERSION 3.5)

project(FileMonitor_projWork)

add_executable( FileMonitor
	FileMonitor.cpp )

set_target_properties(FileMonitor PROPERTIES
CXX_STANDARD 17
CXX_STANDARD_REQUIRED ON)