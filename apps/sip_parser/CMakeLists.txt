add_executable(SipParserApp main.cpp parse_cmd_line.h parse_cmd_line.cpp run_parser.h run_parser.cpp)
target_link_libraries(SipParserApp PRIVATE Boost::boost Boost::program_options CppSipParser)
