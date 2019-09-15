add_library(CppSipParser inc/CppSip/parser/abnf_core.h
                         inc/CppSip/parser/common.h
                         inc/CppSip/parser/header.h
                         inc/CppSip/parser/message.h
                         inc/CppSip/parser/request.h
                         inc/CppSip/parser/response.h
                         src/CppSip/parser_utils.cpp
                         src/CppSip/parser_utils.h)
add_library(CppSip::Parser ALIAS CppSipParser)

target_include_directories(CppSipParser PUBLIC inc PRIVATE src)
target_link_libraries(CppSipParser PUBLIC CppSip::Common Boost::boost)
