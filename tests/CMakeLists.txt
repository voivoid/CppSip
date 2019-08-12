add_executable(CppSipTests main.cpp parser.cpp test_utils/message.h test_utils/message.cpp)
target_link_libraries(CppSipTests PRIVATE Boost::boost Boost::unit_test_framework CppSip::Parser)

add_test(NAME CppSipTests
         COMMAND $<TARGET_FILE:CppSipTests>)