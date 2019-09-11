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

  set(PARSERS_TO_TEST
    # ABNF
    ALPHA CR CRLF DIGIT DQUOTE HEXDIG HTAB LF SP WSP
    # COMMON
    alphanum LWS SWS HCOLON SLASH SEMI EQUAL RAQUOT LAQUOT quoted-pair quoted-string qdtext token mark unreserved reserved escaped Method SIP-Version word callid
    hnv-unreserved hvalue hname header headers domainlabel toplabel hostname port h16 dec-octet IPv4address ls32 host hostport password user-unreserved user
    userinfo SIP-URI SIPS-URI
    # HEADERS
    ietf-token iana-token x-token m-subtype extension-token discrete-type composite-type m-attribute m-type m-value m-parameter media-type display-name addr-spec
    Call-ID Content-Length Content-Type CSeq Max-Forwards message-header
    # REQUEST
    Request-URI Request-Line Request
    # RESPONSE
    Reason-Phrase Status-Code Status-Line Response
    # MESSAGE
    SIP-message
  )

  # TODO: add IPv6address test

  foreach(PARSER ${PARSERS_TO_TEST})
    add_parser_test(${PARSER})
  endforeach()

endif()
