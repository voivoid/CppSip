add_library(CppSipCommon STATIC inc/CppSip/message/message.h
                                inc/CppSip/message/method.h
                                inc/CppSip/message/sip_version.h
                                src/CppSip/common.cpp)
add_library(CppSip::Common ALIAS CppSipCommon)
target_include_directories(CppSipCommon PUBLIC inc PRIVATE src)
