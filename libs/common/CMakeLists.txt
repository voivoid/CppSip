add_library(CppSipCommon STATIC inc/CppSip/message/headers/callid.h
                                inc/CppSip/message/headers/content_length.h
                                inc/CppSip/message/headers/content_type.h
                                inc/CppSip/message/headers/cseq.h
                                inc/CppSip/message/headers/headers.h
                                inc/CppSip/message/headers/max_forwards.h
                                inc/CppSip/message/headers/media_type.h
                                inc/CppSip/message/request/request.h
                                inc/CppSip/message/request/request_line.h
                                inc/CppSip/message/request/request_uri.h
                                inc/CppSip/message/response/response.h
                                inc/CppSip/message/response/status_code.h
                                inc/CppSip/message/response/status_line.h
                                inc/CppSip/message/address.h
                                src/CppSip/message/address.cpp
                                inc/CppSip/message/message.h
                                inc/CppSip/message/method.h
                                inc/CppSip/message/sip_uri.h
                                inc/CppSip/message/sip_uri_header.h
                                inc/CppSip/message/sip_version.h
                                inc/CppSip/message/userinfo.h)

add_library(CppSip::Common ALIAS CppSipCommon)
target_link_libraries(CppSipCommon PUBLIC Boost::boost)
target_include_directories(CppSipCommon PUBLIC inc PRIVATE src)
