include(ExternalProject)

set(BoostVersion "1.73.0")
set(BoostLibs log test program_options)
set(BoostSHA256 9995e192e68528793755692917f9eb6422f3052a53c5e13ba278a228af6c7acf)


if(WIN32)
  set(BoostBootstrapCmd cmd /C "<SOURCE_DIR>/bootstrap.bat")
  set(BoostB2 "<SOURCE_DIR>/b2.exe")
else()
  set(BoostBootstrapCmd $ENV{SHELL} "<SOURCE_DIR>/bootstrap.sh")
  set(BoostB2 "<SOURCE_DIR>/b2")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(BoostToolset "gcc")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(BoostToolset "clang")
endif()

if(BoostToolset)
  set(BoostBootstrapToolset "--with-toolset=${BoostToolset}")
  set(BoostB2Toolset "toolset=${BoostToolset}")
endif()

if(UNIX AND NOT "${CMAKE_BUILD_TYPE}" STREQUAL "RELEASE")
  set(BoostBuildVariant "variant=debug")
endif()

if(MSVC)
  if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
    set(BoostAddressModel "address-model=64")
    set(BoostAddressModelTag "-x64")
  else()
    set(BoostAddressModel "address-model=32")
    set(BoostAddressModelTag "-x32")
  endif()

  set(BoostLayout "--layout=tagged")
  set(BoostAsmFlags "asmflags=\\safeseh")
endif()

foreach(BoostLib ${BoostLibs})
  list(APPEND BoostLibsCmdLine "--with-${BoostLib}")
endforeach()

list(TRANSFORM BoostLibs REPLACE test unit_test_framework)

set(BoostByproducts ${BoostLibs})
list(TRANSFORM BoostByproducts PREPEND <SOURCE_DIR>/stage/lib/libboost_)

if(MSVC)
  set(BoostByproductsMt ${BoostByproducts})
  set(BoostByproductsMtGd ${BoostByproducts})
  list(TRANSFORM BoostByproductsMt APPEND -mt${BoostAddressModelTag}.lib)
  list(TRANSFORM BoostByproductsMtGd APPEND -mt-gd${BoostAddressModelTag}.lib)
  set(BoostByproducts ${BoostByproductsMt} ${BoostByproductsMtGd})
else()
  list(TRANSFORM BoostByproducts APPEND .a)
endif()


string(REPLACE . _ BoostVersionUnderscored ${BoostVersion})
ExternalProject_Add(
  get_boost
  PREFIX thirdparties
  URL "https://dl.bintray.com/boostorg/release/${BoostVersion}/source/boost_${BoostVersionUnderscored}.tar.gz"
  URL_HASH SHA256=${BoostSHA256}
  CONFIGURE_COMMAND ${BoostBootstrapCmd} ${BoostBootstrapToolset}
  BUILD_COMMAND ${BoostB2} ${BoostB2Toolset} link=static threading=multi runtime-link=shared ${BoostLayout} ${BoostAddressModel} ${BoostBuildVariant} ${BoostLibsCmdLine} ${BoostAsmFlags} -j 4
  BUILD_IN_SOURCE TRUE
  INSTALL_COMMAND ""
  BUILD_BYPRODUCTS ${BoostByproducts}
)


ExternalProject_Get_Property(get_boost SOURCE_DIR)
set(BoostSrcDir ${SOURCE_DIR})
set(BoostLibDir ${BoostSrcDir}/stage/lib)

add_library(boost_headers INTERFACE)
add_library(Boost::boost ALIAS boost_headers)
set_target_properties(boost_headers PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${BoostSrcDir})
set_target_properties(boost_headers PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ${BoostSrcDir})

if(MSVC)
  set_property(TARGET boost_headers PROPERTY INTERFACE_COMPILE_DEFINITIONS BOOST_ALL_NO_LIB)
endif()

macro(set_boost_libs_location Component)
  if(MSVC)
    set_property(TARGET Boost::${Component} APPEND PROPERTY
      IMPORTED_CONFIGURATIONS RELEASE)
    set_target_properties(Boost::${Component} PROPERTIES
      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
      IMPORTED_LOCATION_RELEASE "${BoostLibDir}/libboost_${Component}-mt${BoostAddressModelTag}.lib")
    set_property(TARGET Boost::${Component} APPEND PROPERTY
      IMPORTED_CONFIGURATIONS DEBUG)
    set_target_properties(Boost::${Component} PROPERTIES
      IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
      IMPORTED_LOCATION_DEBUG "${BoostLibDir}/libboost_${Component}-mt-gd${BoostAddressModelTag}.lib")
  else()
    set_target_properties(Boost::${Component} PROPERTIES
      IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
      IMPORTED_LOCATION "${BoostLibDir}/libboost_${Component}.a")
  endif()
endmacro()

add_dependencies(boost_headers get_boost)

foreach(BoostLib ${BoostLibs})
  add_library(Boost::${BoostLib} STATIC IMPORTED)
  set_boost_libs_location(${BoostLib})
  add_dependencies(Boost::${BoostLib} get_boost)
endforeach()
