cmake_minimum_required (VERSION 2.8.11)
project (RAILS)

include(CheckCCompilerFlag)
check_c_compiler_flag("-std=c99" COMPLIER.SUPPORTS_C99)
SET(CMAKE_CXX_FLAGS "-std=c99 -fPIC -O0 -g")
SET(CMAKE_C_FLAGS "-std=c99 -fPIC -O0 -g")

enable_testing()
add_definitions(-std=c99)
include_directories(${CMAKE_SOURCE_DIR}/src/include)
include_directories(${CMAKE_SOURCE_DIR}/tests/include)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_C_FLAGS_DEBUG "-O0 -g -Wall")

#check the test covering
include (CTest)
set(CMAKE_BUILD_TYPE COVER)
set(CMAKE_C_FlAGS_COVER "-g -O0 --coverage -ftest-coverage -fprofile-arcs")
#to be compilated
#cmake [path] -DCMAKE_BUILD_TYPE=[mode]
#make
#make test
#make ExperimentalCoverage           (if use COVER)

add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(tests)
