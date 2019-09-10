add_executable(CppSipTests main.cpp
                           parsers/abnf_core_parsers.cpp
                           parsers/common_parsers.cpp
                           parsers/header_parsers.cpp
                           parsers/message_parser.cpp
                           parsers/request_parsers.cpp
                           parsers/response_parsers.cpp
                           parsers/datasets.h
                           parsers/utils.h
                           output/sip_message.h
                           output/sip_message.cpp)

target_include_directories(CppSipTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(CppSipTests PRIVATE Boost::boost Boost::unit_test_framework CppSip::Common CppSip::Parser)
#target_compile_definitions(CppSipTests PRIVATE BOOST_SPIRIT_X3_DEBUG)

add_test(NAME CppSipTests
         COMMAND $<TARGET_FILE:CppSipTests>)


option(CPPSIP_PARSER_ABNFGEN_TESTS "Build parser abnfgen tests" ON)
if(UNIX AND CPPSIP_PARSER_ABNFGEN_TESTS)
  find_program(Bash bash)

  include(${PROJECT_SOURCE_DIR}/cmake/thirdparties/abnfgen.cmake)

  set(SIP_GRAMMAR_PATH ${CMAKE_CURRENT_SOURCE_DIR}/parsers/SIP_grammar.txt)

  function(add_parser_test parser)
      add_test(NAME CppSipParser_${parser}
           COMMAND bash -c "$<TARGET_FILE:ABNFGen> -c -x -s ${parser} ${SIP_GRAMMAR_PATH} | $<TARGET_FILE:SipParserApp> ${parser}")
  endfunction()

  # ABNF
  add_parser_test(ALPHA)
  add_parser_test(CR)
  add_parser_test(CRLF)
  add_parser_test(DIGIT)
  add_parser_test(DQUOTE)
  add_parser_test(HEXDIG)
  add_parser_test(HTAB)
  add_parser_test(LF)
  add_parser_test(SP)
  add_parser_test(WSP)

  # COMMON
  add_parser_test(alphanum)
  add_parser_test(LWS)
  add_parser_test(SWS)
  add_parser_test(HCOLON)
  add_parser_test(SLASH)
  add_parser_test(SEMI)
  add_parser_test(EQUAL)
  add_parser_test(RAQUOT)
  add_parser_test(LAQUOT)
  add_parser_test(quoted-pair)
  add_parser_test(quoted-string)
  add_parser_test(qdtext)
  add_parser_test(token)
  add_parser_test(mark)
  add_parser_test(unreserved)
  add_parser_test(reserved)
  add_parser_test(escaped)
  add_parser_test(Method)
  add_parser_test(SIP-Version)
  add_parser_test(word)
  add_parser_test(callid)
  add_parser_test(hnv-unreserved)
  add_parser_test(hvalue)
  add_parser_test(hname)
  add_parser_test(header)
  add_parser_test(headers)
  add_parser_test(domainlabel)
  add_parser_test(toplabel)
  add_parser_test(hostname)
  add_parser_test(port)
  add_parser_test(h16)
  add_parser_test(dec-octet)
  add_parser_test(IPv4address)
  add_parser_test(ls32)
#  add_parser_test(IPv6address)
  add_parser_test(host)
  add_parser_test(hostport)
  add_parser_test(password)
  add_parser_test(user-unreserved)
  add_parser_test(user)
  add_parser_test(userinfo)
  add_parser_test(SIP-URI)
  add_parser_test(SIPS-URI)
endif()
