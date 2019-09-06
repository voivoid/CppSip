#include "boost/test/unit_test.hpp"

#include "CppSip/parser/request_parsers.h"

#include "parsers/utils.h"

#include <limits>

namespace CppSipMsg = CppSip::Message;

namespace
{

// clang-format off
define_parser(Request_URI, CppSipMsg::RequestUri)
define_parser(Request_Line, CppSipMsg::RequestLine)
define_parser(Request, CppSipMsg::Request)
// clang-format on

}  // namespace

BOOST_AUTO_TEST_SUITE( message_parsers )

BOOST_AUTO_TEST_CASE( test_Request_URI_parser )
{
  {
    const auto [ sips, userinfo, hostport, sip_uri_headers ] = parse_Request_URI( "sip:domain.com" ).sip_uri;

    BOOST_CHECK( !sips );
    BOOST_CHECK( !userinfo );
    BOOST_CHECK_EQUAL( ( CppSipMsg::HostPort{ { "domain.com" }, {} } ), hostport );
    BOOST_CHECK( sip_uri_headers.empty() );
  }
}

BOOST_AUTO_TEST_CASE( test_Request_Line_parser )
{
  {
    const auto [ method, request_uri, sip_version ]           = parse_Request_Line( "INVITE sip:domain.com SIP/2.0\r\n" );
    const auto& [ sips, userinfo, hostport, sip_uri_headers ] = request_uri.sip_uri;
    const auto& [ major, minor ]                              = sip_version;

    BOOST_CHECK_EQUAL( CppSipMsg::Method::Invite, method );
    BOOST_CHECK( !sips );
    BOOST_CHECK( !userinfo );
    BOOST_CHECK_EQUAL( ( CppSipMsg::HostPort{ { "domain.com" }, {} } ), hostport );
    BOOST_CHECK( sip_uri_headers.empty() );
    BOOST_CHECK_EQUAL( 2, major );
    BOOST_CHECK_EQUAL( 0, minor );
  }
}

BOOST_AUTO_TEST_CASE( test_Request_parser )
{
  const auto [ request_line, headers ] = parse_Request(
      "INVITE sip:domain.com SIP/2.0\r\n"
      "Call-ID: 1234567890\r\n"
      "CSeq: 12345 INVITE\r\n"
      "Max-Forwards: 10\r\n"
      "\r\n" );
}

BOOST_AUTO_TEST_SUITE_END()
