#include "boost/test/unit_test.hpp"

#include "CppSip/parser/message.h"

#include "parsers/utils.h"

namespace
{
define_parser( SIP_message, CppSip::Message::Message )
}

BOOST_AUTO_TEST_SUITE( message_parsers )

BOOST_AUTO_TEST_CASE( test_SIP_message_parser )
{
  {
    auto message = parse_SIP_message(
        "INVITE sip:domain.com SIP/2.0\r\n"
        "Call-ID: 1234567890\r\n"
        "CSeq: 12345 INVITE\r\n"
        "Max-Forwards: 10\r\n"
        "\r\n" );
    BOOST_CHECK( boost::get<CppSip::Message::Request>( &message ) );
  }

  {
    auto message = parse_SIP_message(
        "SIP/2.0 100 Trying\r\n"
        "Call-ID: 1234567890\r\n"
        "CSeq: 12345 INVITE\r\n"
        "Max-Forwards: 10\r\n"
        "\r\n" );
    BOOST_CHECK( boost::get<CppSip::Message::Response>( &message ) );
  }
}

BOOST_AUTO_TEST_SUITE_END()
