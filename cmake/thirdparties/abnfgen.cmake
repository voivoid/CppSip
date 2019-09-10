include(ExternalProject)

find_program(make REQUIRED)

set(ABNFGenVersion 0.20)

ExternalProject_Add(
  get_ABNFGen
  PREFIX thirdparties
  URL http://www.quut.com/abnfgen/abnfgen-${ABNFGenVersion}.tar.gz
  URL_HASH SHA256=73ce23ab8f95d649ab9402632af977e11666c825b3020eb8c7d03fa4ca3e7514
  BUILD_IN_SOURCE TRUE
  CONFIGURE_COMMAND ./configure
  BUILD_COMMAND make
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""
  )

add_executable(ABNFGen IMPORTED)

ExternalProject_Get_Property(get_ABNFGen SOURCE_DIR)
set_target_properties(ABNFGen PROPERTIES IMPORTED_LOCATION ${SOURCE_DIR}/abnfgen)

add_dependencies(ABNFGen get_ABNFGen)
