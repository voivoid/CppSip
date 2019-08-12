cmake_minimum_required(VERSION 3.15)

project(CppSip LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/thirdparties/boost.cmake)

add_subdirectory(lib)


option(CPPSIP_BUILD_APPS "Build applications" ON)
if(CPPSIP_BUILD_APPS)
  enable_testing()
  add_subdirectory(apps)
endif()

option(CPPSIP_BUILD_EXAMPLES "Build examples" ON)
if(CPPSIP_BUILD_EXAMPLES)
  enable_testing()
  add_subdirectory(examples)
endif()

option(CPPSIP_BUILD_TESTS "Build unit tests" ON)
if(CPPSIP_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()