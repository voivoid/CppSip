add_executable(CppSipTests main.cpp
                           parsers/abnf_core_parsers.cpp
                           parsers/common_parsers.cpp
                           parsers/message_parser.cpp
                           parsers/request_parsers.cpp
                           parsers/response_parsers.cpp
                           parsers/utils.h
                           output/sip_message.h
                           output/sip_message.cpp
                           output/std.h)

target_include_directories(CppSipTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(CppSipTests PRIVATE Boost::boost Boost::unit_test_framework CppSip::Common CppSip::Parser)
#target_compile_definitions(CppSipTests PRIVATE BOOST_SPIRIT_X3_DEBUG)



add_test(NAME CppSipTests
         COMMAND $<TARGET_FILE:CppSipTests>)
