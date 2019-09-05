#include "boost/test/unit_test.hpp"

#include "CppSip/parser/request_parsers.h"

#include "parsers/utils.h"

#include <limits>

namespace CppSipMsg = CppSip::Message;

namespace
{

// clang-format off
define_parser(domainlabel, std::string)
define_parser(toplabel, std::string)
define_parser(hostname, CppSipMsg::HostName)
define_parser(port, CppSipMsg::Port)
define_parser(h16, std::uint16_t)
define_parser(IPv4address, CppSipMsg::IPv4Address)
define_raw_parser(ls32)
define_raw_parser(IPv6address)
define_parser(host, CppSipMsg::Host)
define_parser(hostport, CppSipMsg::HostPort)
define_parser(password, std::string);
define_parser(user_unreserved, char);
define_parser(user, std::string);
define_parser(userinfo, CppSipMsg::UserInfo);
define_parser(hnv_unreserved, char);
define_parser(hvalue, CppSipMsg::SipUriHeader::Value)
define_parser(hname, CppSipMsg::SipUriHeader::Name)
define_parser(header, CppSipMsg::SipUriHeader)
define_parser(headers, std::vector<CppSipMsg::SipUriHeader>);
define_parser(SIP_URI, CppSipMsg::SipUri);
define_parser(SIPS_URI, CppSipMsg::SipUri);
define_parser(Request_URI, CppSipMsg::RequestUri)
define_parser(Request_Line, CppSipMsg::RequestLine)
define_parser(Request, CppSipMsg::Request)
// clang-format on

}  // namespace

BOOST_AUTO_TEST_SUITE( message_parsers )

BOOST_AUTO_TEST_CASE( test_domainlabel_parser )
{
  BOOST_CHECK_EQUAL( "X", parse_domainlabel( "X" ) );
  BOOST_CHECK_EQUAL( "XX", parse_domainlabel( "XX" ) );
  BOOST_CHECK_EQUAL( "domain", parse_domainlabel( "domain" ) );
  BOOST_CHECK_EQUAL( "123", parse_domainlabel( "123" ) );
  BOOST_CHECK_EQUAL( "X-X", parse_domainlabel( "X-X" ) );
  BOOST_CHECK_EQUAL( "XX-X", parse_domainlabel( "XX-X" ) );
  BOOST_CHECK_EQUAL( "X-XX", parse_domainlabel( "X-XX" ) );
  BOOST_CHECK_EQUAL( "XX-XX", parse_domainlabel( "XX-XX" ) );
  BOOST_CHECK_EQUAL( "X-X-X", parse_domainlabel( "X-X-X" ) );
  BOOST_CHECK_EQUAL( "X---X", parse_domainlabel( "X---X" ) );

  BOOST_CHECK_THROW( parse_domainlabel( "!" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_domainlabel( "-" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_domainlabel( "X-" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_domainlabel( "X-X-" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_toplabel_parser )
{
  BOOST_CHECK_EQUAL( "d", parse_toplabel( "d" ) );
  BOOST_CHECK_EQUAL( "ru", parse_toplabel( "ru" ) );
  BOOST_CHECK_EQUAL( "com", parse_toplabel( "com" ) );
  BOOST_CHECK_EQUAL( "co2", parse_toplabel( "co2" ) );

  BOOST_CHECK_EQUAL( "X-X", parse_toplabel( "X-X" ) );
  BOOST_CHECK_EQUAL( "XX-X", parse_toplabel( "XX-X" ) );
  BOOST_CHECK_EQUAL( "X-XX", parse_toplabel( "X-XX" ) );
  BOOST_CHECK_EQUAL( "XX-XX", parse_toplabel( "XX-XX" ) );
  BOOST_CHECK_EQUAL( "X-X-X", parse_toplabel( "X-X-X" ) );
  BOOST_CHECK_EQUAL( "X---X", parse_toplabel( "X---X" ) );

  BOOST_CHECK_THROW( parse_toplabel( "22" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_toplabel( "@" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_toplabel( "-" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_toplabel( "X-" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_hostname_parser )
{
  BOOST_CHECK_EQUAL( "a.b", parse_hostname( "a.b" ) );
  BOOST_CHECK_EQUAL( "5.b", parse_hostname( "5.b" ) );
  BOOST_CHECK_EQUAL( "domain.com", parse_hostname( "domain.com" ) );
  BOOST_CHECK_EQUAL( "domain.com.", parse_hostname( "domain.com." ) );
  BOOST_CHECK_EQUAL( "dom--ain.com.", parse_hostname( "dom--ain.com." ) );

  BOOST_CHECK_THROW( parse_hostname( "dom#ain.com" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_hostname( "domain.5" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_hostname( "domain.co-" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_port_parser )
{
  BOOST_CHECK_EQUAL( 0, parse_port( "0" ) );
  BOOST_CHECK_EQUAL( 5060, parse_port( "5060" ) );
  BOOST_CHECK_EQUAL( 65535, parse_port( "65535" ) );

  BOOST_CHECK_THROW( parse_port( "port" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_port( "-1" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_h16_parser )
{
  BOOST_CHECK_EQUAL( 0, parse_h16( "0" ) );
  BOOST_CHECK_EQUAL( 17, parse_h16( "11" ) );
  BOOST_CHECK_EQUAL( 3822, parse_h16( "EEE" ) );
  BOOST_CHECK_EQUAL( 65535, parse_h16( "FFFF" ) );
  BOOST_CHECK_EQUAL( 43981, parse_h16( "ABCD" ) );

  BOOST_CHECK_THROW( parse_h16( "" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_h16( "ABCDE" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_IPv4address_parser )
{
  BOOST_CHECK_EQUAL( ( CppSipMsg::IPv4Address{ 127, 0, 0, 1 } ), parse_IPv4address( "127.0.0.1" ) );
  BOOST_CHECK_EQUAL( ( CppSipMsg::IPv4Address{ 0, 0, 0, 0 } ), parse_IPv4address( "0.0.0.0" ) );
  BOOST_CHECK_EQUAL( ( CppSipMsg::IPv4Address{ 255, 255, 255, 255 } ), parse_IPv4address( "255.255.255.255" ) );

  BOOST_CHECK_THROW( parse_IPv4address( "1" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_IPv4address( "1.2" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_IPv4address( "1.2.3" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_ls32_parser )
{
  BOOST_CHECK( parse_ls32( "ABCD:1234" ) );
  BOOST_CHECK( parse_ls32( "A:BBBB" ) );
  BOOST_CHECK( parse_ls32( "AAAA:B" ) );
}

BOOST_AUTO_TEST_CASE( test_IPv6address_parser )
{
  BOOST_CHECK( parse_IPv6address( "0000:1111:2222:3333:4444:5555:AAAA:BBBB" ) );  //                            6( h16 ":" ) ls32
  BOOST_CHECK( parse_IPv6address( "::1111:2222:3333:4444:5555:AAAA:BBBB" ) );     //                       "::" 5( h16 ":" ) ls32
  BOOST_CHECK( parse_IPv6address( "::2222:3333:4444:5555:AAAA:BBBB" ) );          //                       "::" 4( h16 ":" ) ls32
  BOOST_CHECK( parse_IPv6address( "FFFF::2222:3333:4444:5555:AAAA:BBBB" ) );      //                 h16   "::" 4( h16 ":" ) ls32
  // BOOST_CHECK( parse_IPv6address( "FFFF::3333:4444:5555:AAAA:BBBB" ) );        // [ *1( h16 ":" ) h16 ] "::" 3( h16 ":" ) ls32
  BOOST_CHECK( parse_IPv6address( "FFFF:FFFF::3333:4444:5555:AAAA:BBBB" ) );   // [ *1( h16 ":" ) h16 ] "::" 3( h16 ":" ) ls32
  BOOST_CHECK( parse_IPv6address( "::3333:4444:5555:AAAA:BBBB" ) );            //                       "::" 3( h16 ":" ) ls32
  BOOST_CHECK( parse_IPv6address( "FFFF:FFFF:FFFF::4444:5555:AAAA:BBBB" ) );   // [ *2( h16 ":" ) h16 ] "::" 2( h16 ":" ) ls32
  BOOST_CHECK( parse_IPv6address( "::4444:5555:AAAA:BBBB" ) );                 //                       "::" 2( h16 ":" ) ls32
  BOOST_CHECK( parse_IPv6address( "FFFF:FFFF:FFFF:FFFF::5555:AAAA:BBBB" ) );   // [ *3( h16 ":" ) h16 ] "::" 1( h16 ":" ) ls32
  BOOST_CHECK( parse_IPv6address( "::5555:AAAA:BBBB" ) );                      //                       "::" 1( h16 ":" ) ls32
  BOOST_CHECK( parse_IPv6address( "FFFF:FFFF:FFFF:FFFF:FFFF::AAAA:BBBB" ) );   // [ *4( h16 ":" ) h16 ] "::" ls32
  BOOST_CHECK( parse_IPv6address( "::AAAA:BBBB" ) );                           //                       "::" ls32
  BOOST_CHECK( parse_IPv6address( "FFFF:FFFF:FFFF:FFFF:FFFF:FFFF::BBBB" ) );   // [ *5( h16 ":" ) h16 ] "::" h16
  BOOST_CHECK( parse_IPv6address( "::BBBB" ) );                                //                       "::" h16
  BOOST_CHECK( parse_IPv6address( "FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:FFFF::" ) );  // [ *6( h16 ":" ) h16 ] "::"
  BOOST_CHECK( parse_IPv6address( "::" ) );                                    //                       "::"
}

BOOST_AUTO_TEST_CASE( test_host_parser )
{
  BOOST_CHECK_EQUAL( CppSipMsg::Host( CppSipMsg::HostName( "domain.com" ) ), parse_host( "domain.com" ) );
  BOOST_CHECK_EQUAL( CppSipMsg::Host( CppSipMsg::IPv4Address{ 127, 0, 0, 1 } ), parse_host( "127.0.0.1" ) );
}

BOOST_AUTO_TEST_CASE( test_hostport_parser )
{
  BOOST_CHECK_EQUAL( ( CppSipMsg::HostPort{ { "domain.com" }, {} } ), parse_hostport( "domain.com" ) );
  BOOST_CHECK_EQUAL( ( CppSipMsg::HostPort{ { "domain.com" }, { 5060 } } ), parse_hostport( "domain.com:5060" ) );
  BOOST_CHECK_EQUAL( ( CppSipMsg::HostPort{ CppSipMsg::IPv4Address{ 192, 168, 0, 1 }, { 5060 } } ), parse_hostport( "192.168.0.1:5060" ) );
}

BOOST_AUTO_TEST_CASE( test_password_parser )
{
  BOOST_CHECK_EQUAL( "password!!!", parse_password( "password!!!" ) );
}

BOOST_DATA_TEST_CASE( test_user_unreserved_parser, TestDatasets::user_unreserved )
{
  BOOST_CHECK_EQUAL( sample, parse_user_unreserved( std::string_view( &sample, 1 ) ) );
}

BOOST_AUTO_TEST_CASE( test_user_parser )
{
  BOOST_CHECK_EQUAL( "user???", parse_user( "user???" ) );
}

BOOST_AUTO_TEST_CASE( test_userinfo_parser )
{
  {
    auto [ user, password ] = parse_userinfo( "user@" );
    BOOST_CHECK_EQUAL( "user", user );
    BOOST_CHECK( password.empty() );
  }
  {
    auto [ user, password ] = parse_userinfo( "user:password@" );
    BOOST_CHECK_EQUAL( "user", user );
    BOOST_CHECK_EQUAL( "password", password );
  }
}

BOOST_DATA_TEST_CASE( test_hnv_unreserved_parser, TestDatasets::hnv_unreserved )
{
  BOOST_CHECK_EQUAL( sample, parse_hnv_unreserved( std::string_view( &sample, 1 ) ) );
}

BOOST_AUTO_TEST_CASE( test_hvalue_parser )
{
  std::string input = "[]/?:+$abc123-_.!~*'()";
  BOOST_CHECK_EQUAL( input, parse_hvalue( input ) );
  BOOST_CHECK_EQUAL( "", parse_hvalue( "" ) );
}

BOOST_AUTO_TEST_CASE( test_hname_parser )
{
  std::string input = "[]/?:+$abc123-_.!~*'()";
  BOOST_CHECK_EQUAL( input, parse_hname( input ) );
}

BOOST_AUTO_TEST_CASE( test_header_parser )
{
  {
    const auto [ name, value ] = parse_header( "name=value" );
    BOOST_CHECK_EQUAL( "name", name );
    BOOST_CHECK_EQUAL( "value", value );
  }
}

BOOST_AUTO_TEST_CASE( test_headers_parser )
{
  {
    const auto headers = parse_headers( "?name1=value1" );
    BOOST_REQUIRE_EQUAL( 1, headers.size() );
    BOOST_CHECK_EQUAL( "name1", headers[ 0 ].name );
    BOOST_CHECK_EQUAL( "value1", headers[ 0 ].value );
  }

  {
    const auto headers = parse_headers( "?name1=value1&name2=value2" );
    BOOST_REQUIRE_EQUAL( 2, headers.size() );
    BOOST_CHECK_EQUAL( "name1", headers[ 0 ].name );
    BOOST_CHECK_EQUAL( "value1", headers[ 0 ].value );
    BOOST_CHECK_EQUAL( "name2", headers[ 1 ].name );
    BOOST_CHECK_EQUAL( "value2", headers[ 1 ].value );
  }
}

BOOST_AUTO_TEST_CASE( test_SIP_URI_parser )
{
  {
    const auto [ sips, userinfo, hostport ] = parse_SIP_URI( "sip:domain.com" );
    BOOST_CHECK( !sips );
    BOOST_CHECK( !userinfo );
    BOOST_CHECK_EQUAL( ( CppSipMsg::HostPort{ { "domain.com" }, {} } ), hostport );
  }

  {
    const auto [ sips, userinfo, hostport ] = parse_SIP_URI( "sip:user:password@domain.com" );
    BOOST_CHECK( !sips );
    BOOST_REQUIRE( userinfo );
    BOOST_CHECK_EQUAL( "user", userinfo->user );
    BOOST_CHECK_EQUAL( "password", userinfo->password );
    BOOST_CHECK_EQUAL( ( CppSipMsg::HostPort{ { "domain.com" }, {} } ), hostport );
  }

  BOOST_CHECK_THROW( parse_SIP_URI( "sips:domain.com" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_SIPS_URI_parser )
{
  {
    const auto [ sips, userinfo, hostport ] = parse_SIPS_URI( "sips:domain.com" );
    BOOST_CHECK( sips );
    BOOST_CHECK( !userinfo );
    BOOST_CHECK_EQUAL( ( CppSipMsg::HostPort{ { "domain.com" }, {} } ), hostport );
  }

  BOOST_CHECK_THROW( parse_SIPS_URI( "sip:domain.com" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_Request_URI_parser )
{
  {
    const auto [ sips, userinfo, hostport ] = parse_Request_URI( "sip:domain.com" ).sip_uri;

    BOOST_CHECK( !sips );
    BOOST_CHECK( !userinfo );
    BOOST_CHECK_EQUAL( ( CppSipMsg::HostPort{ { "domain.com" }, {} } ), hostport );
  }
}

BOOST_AUTO_TEST_CASE( test_Request_Line_parser )
{
  {
    const auto [ method, request_uri, sip_version ] = parse_Request_Line( "INVITE sip:domain.com SIP/2.0\r\n" );
    const auto& [ sips, userinfo, hostport ]        = request_uri.sip_uri;
    const auto& [ major, minor ]                    = sip_version;

    BOOST_CHECK_EQUAL( CppSipMsg::Method::Invite, method );
    BOOST_CHECK( !sips );
    BOOST_CHECK( !userinfo );
    BOOST_CHECK_EQUAL( ( CppSipMsg::HostPort{ { "domain.com" }, {} } ), hostport );
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
