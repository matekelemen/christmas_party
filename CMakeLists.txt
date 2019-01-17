cmake_minimum_required( VERSION 3.4.3 )

# Project name and programming language
project( christmas_party CXX )

# Gather files and store paths in CMake variables
file( GLOB HEADER_FILES libs/inc/*.h* )
file( GLOB SOURCE_FILES libs/src/*.cpp )

# Specify the folders with header files, otherwise our includes are not found
include_directories( libs/inc )

# Changes the default install path to build/install, assuming build is the project directory
if ( CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT )
    set ( CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/install" CACHE PATH "default install path" FORCE )
endif( )

# This will add the install path to the rpath of the installed binaries to make dynamic linking work
SET( CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}" )

# When compiling with gcc we need to compile libraries with fPIC (stands for position independent code).
if( CMAKE_COMPILER_IS_GNUCXX )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -pedantic -Wall -Werror -std=c++11" )
endif( CMAKE_COMPILER_IS_GNUCXX )


# Add executables
add_executable( main ${SOURCE_FILES} ${HEADER_FILES} )

install( TARGETS main RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX} )