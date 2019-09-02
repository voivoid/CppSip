add_library(CppSipCommon STATIC inc/CppSip/message/headers/callid.h
                                inc/CppSip/message/headers/cseq.h
                                inc/CppSip/message/headers/headers.h
                                inc/CppSip/message/headers/max_forwards.h
                                inc/CppSip/message/address.h
                                src/CppSip/message/address.cpp
                                inc/CppSip/message/method.h
                                inc/CppSip/message/sip_version.h
                                inc/CppSip/message/request/request.h
                                inc/CppSip/message/request/request_line.h
                                inc/CppSip/message/request/request_uri.h
                                inc/CppSip/message/request/sip_uri.h
                                inc/CppSip/message/response/response.h
                                src/CppSip/common.cpp)
add_library(CppSip::Common ALIAS CppSipCommon)
target_include_directories(CppSipCommon PUBLIC inc PRIVATE src)
