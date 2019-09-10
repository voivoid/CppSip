#include "boost/test/unit_test.hpp"

#include "CppSip/parser/common_parsers.h"

#include "parsers/utils.h"

namespace CppSipMsg = CppSip::Message;

namespace
{
// clang-format off
define_parser(alphanum, char)
define_noattr_parser(LWS)
define_noattr_parser(SWS)
define_noattr_parser(HCOLON)
define_noattr_parser(SLASH)
define_noattr_parser(SEMI)
define_noattr_parser(EQUAL)
define_noattr_parser(RAQUOT)
define_noattr_parser(LAQUOT)
define_parser(quoted_pair, char)
define_parser(qdtext, char)
define_parser(quoted_string, std::string)
define_parser(token, std::string)
define_parser(mark, char)
define_parser(unreserved, char)
define_parser(reserved, char)
define_parser(escaped, char)
define_parser(word, std::string)
define_parser(callid, std::string)
define_parser(Method, CppSipMsg::Method)
define_parser(SIP_Version, CppSipMsg::SipVersion)
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
define_parser(headers, CppSipMsg::SipUriHeaders);
define_parser(SIP_URI, CppSipMsg::SipUri);
define_parser(SIPS_URI, CppSipMsg::SipUri);
// clang-format on
}  // namespace

BOOST_AUTO_TEST_SUITE( common_sip_parsers )

BOOST_DATA_TEST_CASE( test_alphanum_parser, TestDatasets::alphanum )
{
  BOOST_CHECK_EQUAL( sample, parse_alphanum( std::string_view( &sample, 1 ) ) );
}

BOOST_AUTO_TEST_CASE( test_alphanum_parser_failures )
{
  BOOST_CHECK_THROW( parse_alphanum( "*" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_LWS_parser )
{
  BOOST_CHECK_NO_THROW( parse_LWS( " " ) );
  BOOST_CHECK_NO_THROW( parse_LWS( "  " ) );
  BOOST_CHECK_NO_THROW( parse_LWS( " \t " ) );

  BOOST_CHECK_NO_THROW( parse_LWS( "  \r\n   " ) );

  BOOST_CHECK_THROW( parse_LWS( "" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_LWS( "x" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_SWS_parser )
{
  BOOST_CHECK_NO_THROW( parse_SWS( "" ) );
  BOOST_CHECK_NO_THROW( parse_SWS( " " ) );
  BOOST_CHECK_NO_THROW( parse_SWS( "  " ) );

  BOOST_CHECK_THROW( parse_SWS( "x" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_HCOLON_parser )
{
  BOOST_CHECK_NO_THROW( parse_HCOLON( ":" ) );
  BOOST_CHECK_NO_THROW( parse_HCOLON( ": " ) );
  BOOST_CHECK_NO_THROW( parse_HCOLON( ":  " ) );
  BOOST_CHECK_NO_THROW( parse_HCOLON( ": \t" ) );
  BOOST_CHECK_NO_THROW( parse_HCOLON( " : " ) );
  BOOST_CHECK_NO_THROW( parse_HCOLON( "  : " ) );
  BOOST_CHECK_NO_THROW( parse_HCOLON( " \t: " ) );

  BOOST_CHECK_THROW( parse_HCOLON( " " ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_SLASH_parser )
{
  BOOST_CHECK_NO_THROW( parse_SLASH( "/" ) );
  BOOST_CHECK_NO_THROW( parse_SLASH( "/ " ) );
  BOOST_CHECK_NO_THROW( parse_SLASH( " /" ) );
  BOOST_CHECK_NO_THROW( parse_SLASH( " / " ) );
}

BOOST_AUTO_TEST_CASE( test_SEMI_parser )
{
  BOOST_CHECK_NO_THROW( parse_SEMI( ";" ) );
  BOOST_CHECK_NO_THROW( parse_SEMI( "; " ) );
  BOOST_CHECK_NO_THROW( parse_SEMI( " ;" ) );
  BOOST_CHECK_NO_THROW( parse_SEMI( " ; " ) );
}

BOOST_AUTO_TEST_CASE( test_EQUAL_parser )
{
  BOOST_CHECK_NO_THROW( parse_EQUAL( "=" ) );
  BOOST_CHECK_NO_THROW( parse_EQUAL( "= " ) );
  BOOST_CHECK_NO_THROW( parse_EQUAL( " =" ) );
  BOOST_CHECK_NO_THROW( parse_EQUAL( " = " ) );
}

BOOST_AUTO_TEST_CASE( test_RAQUOT_parser )
{
  BOOST_CHECK_NO_THROW( parse_RAQUOT( ">" ) );
  BOOST_CHECK_NO_THROW( parse_RAQUOT( "> " ) );
  BOOST_CHECK_NO_THROW( parse_RAQUOT( ">  " ) );
}

BOOST_AUTO_TEST_CASE( test_LAQUOT_parser )
{
  BOOST_CHECK_NO_THROW( parse_LAQUOT( "<" ) );
  BOOST_CHECK_NO_THROW( parse_LAQUOT( " <" ) );
  BOOST_CHECK_NO_THROW( parse_LAQUOT( "  <" ) );
}

BOOST_DATA_TEST_CASE( test_quoted_pair_parser, TestDatasets::quoted_pair )
{
  BOOST_CHECK_EQUAL( sample, parse_quoted_pair( std::string( "\\" ) + sample ) );
}

BOOST_AUTO_TEST_CASE( test_quoted_pair_parser_failures )
{
  BOOST_CHECK_THROW( parse_quoted_pair( "a" ), std::runtime_error );
}

BOOST_DATA_TEST_CASE( test_qdtext_parser, TestDatasets::qdtext )
{
  BOOST_CHECK_EQUAL( sample, parse_qdtext( std::string_view( &sample, 1 ) ) );
}

BOOST_AUTO_TEST_CASE( test_quoted_string_parser )
{
  BOOST_CHECK_EQUAL( "", parse_quoted_string( "\"\"" ) );
  BOOST_CHECK_EQUAL( "abc", parse_quoted_string( "\"abc\"" ) );
}

BOOST_AUTO_TEST_CASE( test_token_parser )
{
  BOOST_CHECK_EQUAL( "abc-.!%*_+`'~", parse_token( "abc-.!%*_+`'~" ) );
}

BOOST_DATA_TEST_CASE( test_mark_parser, TestDatasets::mark )
{
  BOOST_CHECK_EQUAL( sample, parse_mark( std::string_view( &sample, 1 ) ) );
}

BOOST_DATA_TEST_CASE( test_unreserved_parser, TestDatasets::unreserved )
{
  BOOST_CHECK_EQUAL( sample, parse_unreserved( std::string_view( &sample, 1 ) ) );
}

BOOST_DATA_TEST_CASE( test_reserved_parser, TestDatasets::reserved )
{
  BOOST_CHECK_EQUAL( sample, parse_reserved( std::string_view( &sample, 1 ) ) );
}

BOOST_AUTO_TEST_CASE( test_escaped_parser )
{
  BOOST_CHECK_EQUAL( '0', parse_escaped( "%30" ) );
  BOOST_CHECK_EQUAL( 'A', parse_escaped( "%41" ) );
  BOOST_CHECK_EQUAL( '\x00', parse_escaped( "%00" ) );
  BOOST_CHECK_EQUAL( '\xff', parse_escaped( "%FF" ) );

  BOOST_CHECK_THROW( parse_escaped( "%F" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_Method_parser )
{
  BOOST_CHECK_EQUAL( CppSipMsg::Method::Ack, parse_Method( "ACK" ) );
  BOOST_CHECK_EQUAL( CppSipMsg::Method::Bye, parse_Method( "BYE" ) );
  BOOST_CHECK_EQUAL( CppSipMsg::Method::Cancel, parse_Method( "CANCEL" ) );
  BOOST_CHECK_EQUAL( CppSipMsg::Method::Invite, parse_Method( "INVITE" ) );
  BOOST_CHECK_EQUAL( CppSipMsg::Method::Options, parse_Method( "OPTIONS" ) );
  BOOST_CHECK_EQUAL( CppSipMsg::Method::Register, parse_Method( "REGISTER" ) );

  BOOST_CHECK_THROW( parse_Method( "UNKNOWN" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_SIP_Version_parser )
{
  {
    const auto [ major, minor ] = parse_SIP_Version( "SIP/1.0" );
    BOOST_CHECK_EQUAL( 1, major );
    BOOST_CHECK_EQUAL( 0, minor );
  }

  {
    const auto [ major, minor ] = parse_SIP_Version( "SIP/2.1" );
    BOOST_CHECK_EQUAL( 2, major );
    BOOST_CHECK_EQUAL( 1, minor );
  }

  BOOST_CHECK_THROW( parse_SIP_Version( "SIP/2" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_SIP_Version( "SIP2.1" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_SIP_Version( "2.1" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_word_parser )
{
  const std::string input = "aAzZ09-.!%*_+`'~()<>:\\\"/[]?{}";
  BOOST_CHECK_EQUAL( input, parse_word( "aAzZ09-.!%*_+`'~()<>:\\\"/[]?{}" ) );
}

BOOST_AUTO_TEST_CASE( test_callid_parser )
{
  BOOST_CHECK_EQUAL( "abc123!", parse_callid( "abc123!" ) );
  BOOST_CHECK_EQUAL( "abc123!@ABC123", parse_callid( "abc123!@ABC123" ) );
}

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
    const auto [ sips, userinfo, hostport, sip_uri_headers ] = parse_SIP_URI( "sip:domain.com" );
    BOOST_CHECK( !sips );
    BOOST_CHECK( !userinfo );
    BOOST_CHECK_EQUAL( ( CppSipMsg::HostPort{ { "domain.com" }, {} } ), hostport );
    BOOST_CHECK( sip_uri_headers.empty() );
  }

  {
    const auto [ sips, userinfo, hostport, sip_uri_headers ] = parse_SIP_URI( "sip:user:password@domain.com?name=value" );
    BOOST_CHECK( !sips );
    BOOST_REQUIRE( userinfo );
    BOOST_CHECK_EQUAL( "user", userinfo->user );
    BOOST_CHECK_EQUAL( "password", userinfo->password );
    BOOST_CHECK_EQUAL( ( CppSipMsg::HostPort{ { "domain.com" }, {} } ), hostport );
    BOOST_REQUIRE_EQUAL( 1, sip_uri_headers.size() );
    BOOST_CHECK_EQUAL( "name", sip_uri_headers[ 0 ].name );
    BOOST_CHECK_EQUAL( "value", sip_uri_headers[ 0 ].value );
  }

  BOOST_CHECK_THROW( parse_SIP_URI( "sips:domain.com" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_SIPS_URI_parser )
{
  {
    const auto [ sips, userinfo, hostport, sip_uri_headers ] = parse_SIPS_URI( "sips:domain.com" );
    BOOST_CHECK( sips );
    BOOST_CHECK( !userinfo );
    BOOST_CHECK_EQUAL( ( CppSipMsg::HostPort{ { "domain.com" }, {} } ), hostport );
    BOOST_CHECK( sip_uri_headers.empty() );
  }

  BOOST_CHECK_THROW( parse_SIPS_URI( "sip:domain.com" ), std::runtime_error );
}


BOOST_AUTO_TEST_SUITE_END()
