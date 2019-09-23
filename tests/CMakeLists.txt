add_executable(CppSipTests main.cpp
                           parsers/headers/headers_common_parsers.cpp
                           parsers/headers/headers_parsers.cpp
                           parsers/headers/call_id_parsers.cpp
                           parsers/headers/contact_parsers.cpp
                           parsers/headers/content_length_parsers.cpp
                           parsers/headers/content_type_parsers.cpp
                           parsers/headers/cseq_parsers.cpp
                           parsers/headers/from_to_parsers.cpp
                           parsers/headers/max_forward_parsers.cpp
                           parsers/headers/via_parsers.cpp
                           parsers/abnf_core_parsers.cpp
                           parsers/common_parsers.cpp
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
    alphanum LWS SWS HCOLON SLASH SEMI STAR EQUAL RAQUOT LAQUOT quoted-pair quoted-string qdtext qvalue token mark unreserved reserved escaped Method SIP-Version word
    callid hnv-unreserved hvalue hname header headers domainlabel toplabel hostname port h16 dec-octet IPv4address ls32 host hostport password user-unreserved user
    userinfo SIP-URI SIPS-URI
    # HEADERS
    ietf-token iana-token x-token m-subtype extension-token discrete-type composite-type m-attribute m-type m-value m-parameter media-type display-name addr-spec
    name-addr generic-param gen-value tag-param from-param from-spec to-param protocol-name protocol-version other-transport transport sent-protocol sent-by ttl
    via-extension via-branch via-received via-maddr via-ttl via-params via-parm c-p-q delta-seconds c-p-expires contact-extension contact-params contact-param

    Call-ID Contact Content-Length Content-Type CSeq From Max-Forwards To Via message-header
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
