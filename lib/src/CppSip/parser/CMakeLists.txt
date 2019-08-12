add_library(CppSipLibParser parser.cpp parser.h)
add_library(CppSip::Parser ALIAS CppSipLibParser)

target_include_directories(CppSipLibParser PUBLIC ${CppSipLibPublicIncludeDir} ${CppSipLibPrivateIncludeDir})