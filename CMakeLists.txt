cmake_minimum_required(VERSION 3.18)
project(cext VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(Python COMPONENTS Interpreter Development.Module Development.Embed)

# for msvc set output path
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${LIBRARY_OUTPUT_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${LIBRARY_OUTPUT_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH})

if(NOT Python_FOUND)
    message(FATAL_ERROR "Python not found!")
endif()

if(NOT Python_Development.Module_FOUND OR NOT Python_Development.Embed_FOUND)
    message(FATAL_ERROR "Python_Development not found!")
endif()

# get python SOABI
execute_process(
    COMMAND
    "${Python_EXECUTABLE}" "-c"
    "import sys, importlib; s = importlib.import_module('distutils.sysconfig' if sys.version_info < (3, 10) else 'sysconfig'); print(s.get_config_var('EXT_SUFFIX') or s.get_config_var('SO'))"
    OUTPUT_VARIABLE Python_SOABI
    ERROR_VARIABLE Python_SOABI_ERR
    OUTPUT_STRIP_TRAILING_WHITESPACE)

if(NOT DEFINED Python_SOABI)
    message(FATAL_ERROR "Python_SOABI not define")
endif()

# Python C Extension target
add_library(cAdd SHARED add.c bind.c)
target_link_libraries(cAdd Python::Module)
message(STATUS Python_SOABI => ${Python_SOABI})
set_target_properties(cAdd PROPERTIES SUFFIX ${Python_SOABI})

# Python C Embed target
add_executable(loadcAdd loadcAdd.c)
target_link_libraries(loadcAdd Python::Python)
target_compile_definitions(loadcAdd PRIVATE MYLIBPATH="${LIBRARY_OUTPUT_PATH}"
    Python_SOABI="${Python_SOABI}")
