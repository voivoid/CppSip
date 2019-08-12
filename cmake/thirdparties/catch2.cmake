include(ExternalProject)

find_package(Git REQUIRED)

set(Catch2Ver v2.9.2)

ExternalProject_Add(
  get_catch2
  PREFIX thirdparties
  URL https://github.com/catchorg/Catch2/archive/${Catch2Ver}.zip
  URL_HASH SHA256=dc486300de22b0d36ddba1705abb07b9e5780639d824ba172ddf7062b2a1bf8f
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""
  )

add_library(catch2 INTERFACE)
add_library(Catch2::Catch2 ALIAS catch2)

ExternalProject_Get_Property(get_catch2 SOURCE_DIR)
set_target_properties(catch2 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${SOURCE_DIR}/single_include)
set_target_properties(catch2 PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ${SOURCE_DIR}/single_include)

add_dependencies(catch2 get_catch2)