add_library(CppSipLibParser message_parser.h
                            parser_utils.cpp
                            parser_utils.h)
add_library(CppSip::Parser ALIAS CppSipLibParser)

target_include_directories(CppSipLibParser PUBLIC ${CppSipLibPublicIncludeDir} ${CppSipLibPrivateIncludeDir})
target_link_libraries(CppSipLibParser PUBLIC Boost::boost)
