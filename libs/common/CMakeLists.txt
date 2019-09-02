add_library(CppSipCommon STATIC inc/CppSip/message/header/callid.h
                                inc/CppSip/message/header/cseq.h
                                inc/CppSip/message/address.h
                                src/CppSip/message/address.cpp
                                inc/CppSip/message/message.h
                                inc/CppSip/message/method.h
                                inc/CppSip/message/request_line.h
                                inc/CppSip/message/request_uri.h
                                inc/CppSip/message/sip_uri.h
                                inc/CppSip/message/sip_version.h
                                inc/CppSip/response/response.h
                                src/CppSip/common.cpp)
add_library(CppSip::Common ALIAS CppSipCommon)
target_include_directories(CppSipCommon PUBLIC inc PRIVATE src)
