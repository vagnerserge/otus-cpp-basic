cmake_minimum_required(VERSION 3.2)

project(GTestFromSources)

if (MSVC)
    # @see https://github.com/google/googletest/blob/master/googletest/README.md
    # Visual Studio Dynamic vs Static Runtimes
    #By default, new Visual Studio projects link the C runtimes dynamically
    #but GoogleTest links them statically. This will generate an error
    #Enabling this option will make gtest link the runtimes dynamically too
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
# Build googletest
add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest" 
    "googletest"
)

# Test target
add_executable(
    listTest
    test/listTest.cpp)
    
add_executable(
    vectorTest
    test/vectorTest.cpp)

# Link test target against gtest libraries
target_link_libraries(
    listTest PRIVATE
    gtest gtest_main
)
target_link_libraries(
    vectorTest PRIVATE
    gtest gtest_main
)
set_target_properties(listTest PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(vectorTest PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
if (MSVC)
    target_compile_options(
        listTest PRIVATE
        /W4
    )
    target_compile_options(
        vectorTest PRIVATE
        /W4
    )
else ()
    target_compile_options(
        listTest  PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
     target_compile_options(
        vectorTest PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()
