add_library(CppSipCommon STATIC inc/CppSip/message/header/cseq.h
                                inc/CppSip/message/address.h
                                inc/CppSip/message/message.h
                                inc/CppSip/message/method.h
                                inc/CppSip/message/request_line.h
                                inc/CppSip/message/request_uri.h
                                inc/CppSip/message/sip_uri.h
                                inc/CppSip/message/sip_version.h
                                src/CppSip/message/address.cpp
                                src/CppSip/common.cpp)
add_library(CppSip::Common ALIAS CppSipCommon)
target_include_directories(CppSipCommon PUBLIC inc PRIVATE src)
