add_library(CppSipParser inc/CppSip/parser/abnf_core_parsers.h
                         inc/CppSip/parser/common_sip_parsers.h
                         inc/CppSip/parser/message_parser.h
                         inc/CppSip/parser/response_parser.h
                         src/CppSip/parser_utils.cpp
                         src/CppSip/parser_utils.h)
add_library(CppSip::Parser ALIAS CppSipParser)

target_include_directories(CppSipParser PUBLIC inc PRIVATE src)
target_link_libraries(CppSipParser PUBLIC CppSip::Common Boost::boost)
