add_executable(SipParserApp main.cpp)
target_link_libraries(SipParserApp PRIVATE Boost::boost Boost::program_options CppSipParser)
