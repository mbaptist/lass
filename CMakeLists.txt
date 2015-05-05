project(lass CXX Fortran)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

#Set local paths of third-party libraries
#cat++
set(CAT_INCLUDE_DIRS ${CAT_INCLUDE_DIRS} $ENV{HOME}/fcup/projects/cat/install/include/cat)
set(CAT_LIBRARY_DIRS ${CAT_LIBRARY_DIRS} $ENV{HOME}/fcup/projects/cat/install/lib)
#lass
set(LASS_INCLUDE_DIRS ${LASS_INCLUDE_DIRS} $ENV{HOME}/fcup/projects/lass/install/include/lass)
set(LASS_LIBRARY_DIRS ${LASS_LIBRARY_DIRS} $ENV{HOME}/fcup/projects/lass/install/lib)


#enable_testing()

add_subdirectory(src)
#add_subdirectory(test)

