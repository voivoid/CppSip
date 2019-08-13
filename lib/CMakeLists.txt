set(CppSipLibPublicIncludeDir ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(CppSipLibPrivateIncludeDir ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src/CppSip/parser)

add_library(CppSipLib STATIC inc/CppSip/message/message.h
                             inc/CppSip/message/method.h
                             inc/CppSip/message/sip_version.h
                             src/CppSip/lib.cpp)
add_library(CppSip::Lib ALIAS CppSipLib)

target_link_libraries(CppSipLib PRIVATE CppSip::Parser Boost::boost Boost::log)

target_include_directories(CppSipLib PUBLIC inc PRIVATE src)
