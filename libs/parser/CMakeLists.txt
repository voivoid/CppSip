add_library(CppSipParser inc/CppSip/parser/headers/common.h
                         inc/CppSip/parser/headers/call_id.h
                         inc/CppSip/parser/headers/content_length.h
                         inc/CppSip/parser/headers/content_type.h
                         inc/CppSip/parser/headers/cseq.h
                         inc/CppSip/parser/headers/from_to.h
                         inc/CppSip/parser/headers/max_forwards.h
                         inc/CppSip/parser/headers/via.h
                         inc/CppSip/parser/abnf_core.h
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
