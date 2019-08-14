cmake_minimum_required(VERSION 3.15)

project(CppSip LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/thirdparties/boost.cmake)

add_subdirectory(libs)


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

find_program(ClangFormat clang-format)
if(ClangFormat)
  set(Targets CppSipCommon CppSipParser CppSipTests)
  foreach(Target ${Targets})
    get_target_property(TargetSources ${Target} SOURCES)
    get_target_property(TargetDir ${Target} SOURCE_DIR)
    foreach(Src ${TargetSources})
      list(APPEND Sources "${TargetDir}/${Src}")
    endforeach()
  endforeach()

  add_custom_target(clangformat
    COMMAND clang-format -style=file -i ${Sources}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()
