add_library(CppSipLibParser parser.cpp parser.h parser_utils.h)
add_library(CppSip::Parser ALIAS CppSipLibParser)

target_include_directories(CppSipLibParser PUBLIC ${CppSipLibPublicIncludeDir} ${CppSipLibPrivateIncludeDir})
target_link_libraries(CppSipLibParser PUBLIC Boost::boost)
