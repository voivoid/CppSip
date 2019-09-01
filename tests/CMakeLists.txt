add_executable(CppSipTests main.cpp
                           parser.cpp
                           test_utils/output_message.h
                           test_utils/output_message.cpp
                           test_utils/output_std.h)

target_include_directories(CppSipTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(CppSipTests PRIVATE Boost::boost Boost::unit_test_framework CppSip::Common CppSip::Parser)
#target_compile_definitions(CppSipTests PRIVATE BOOST_SPIRIT_X3_DEBUG)



add_test(NAME CppSipTests
         COMMAND $<TARGET_FILE:CppSipTests>)
