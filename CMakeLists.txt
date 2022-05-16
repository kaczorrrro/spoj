cmake_minimum_required(VERSION 3.10)
project(Algosy)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE CPP_FILES *.cpp )

#add_executable()

foreach(CPP_FILE ${CPP_FILES})
    get_filename_component(EXEC_NAME ${CPP_FILE} NAME_WE)
    add_executable(${EXEC_NAME}.x ${CPP_FILE})
    target_compile_options(${EXEC_NAME}.x PRIVATE -fsanitize=address)
    target_compile_options(${EXEC_NAME}.x PRIVATE -ggdb)
    target_link_options(${EXEC_NAME}.x PRIVATE -fsanitize=address)
endforeach()

add_library( algo OBJECT ${CPP_FILES} )


