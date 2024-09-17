cmake_minimum_required(VERSION 3.5)

project(FileMonitor_projWork)

add_executable( FileMonitor
	FileMonitor.cpp
    EventHandler.h
	FileEvent.cpp
	FileEvent.h
	FileMonitor.cpp
	FileMonitor.h
	FileSystemMonitor.cpp
	FileSystemMonitor.h
	LogFileHandler.cpp
	LogFileHandler.h )

set_target_properties(FileMonitor PROPERTIES
CXX_STANDARD 17
CXX_STANDARD_REQUIRED ON)