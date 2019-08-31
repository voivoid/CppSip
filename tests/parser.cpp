#include "boost/test/unit_test.hpp"

#include "CppSip/parser/message_parser.h"
#include "test_utils/message.h"

#include "boost/spirit/home/x3.hpp"

#include <limits>
#include <string>

namespace
{
template <typename Attr, typename Parser>
Attr parse( Parser parser, const std::string_view input )
{
  Attr attr;

  auto begin = input.begin();
  auto end   = input.end();

  const bool parsed = boost::spirit::x3::parse( begin, end, parser, attr );
  if ( !parsed || begin != end )
  {
    throw std::runtime_error( "failed to parse" );
  }

  return attr;
}

template <typename Parser>
void parse_noattr( Parser parser, const std::string_view input )
{
  auto begin = input.begin();
  auto end   = input.end();

  const bool parsed = boost::spirit::x3::parse( begin, end, parser );
  if ( !parsed || begin != end )
  {
    throw std::runtime_error( "failed to parse" );
  }
}

#define define_parser( parser, type )                                                                                                      \
  type parse_##parser( const std::string_view input )                                                                                      \
  {                                                                                                                                        \
    return parse<type>( CppSip::Parsers::parser, input );                                                                                  \
  }

#define define_raw_parser( parser )                                                                                                        \
  bool parse_##parser( const std::string_view input )                                                                                      \
  {                                                                                                                                        \
    return input == parse<std::string>( boost::spirit::x3::raw[ CppSip::Parsers::parser ], input );                                        \
  }

#define define_noattr_parser( parser )                                                                                                     \
  void parse_##parser( const std::string_view input )                                                                                      \
  {                                                                                                                                        \
    parse_noattr( CppSip::Parsers::parser, input );                                                                                        \
  }

// clang-format off
define_parser(ALPHA, char)
define_parser(DIGIT, char)
define_parser(HEXDIG, char)
define_noattr_parser(SP)
define_noattr_parser(CR)
define_noattr_parser(LF)
define_noattr_parser(HTAB)
define_noattr_parser(WSP)
define_noattr_parser(CRLF)


define_parser(alphanum, char)
define_noattr_parser(LWS)
define_noattr_parser(SWS)
define_noattr_parser(HCOLON)
define_parser(domainlabel, std::string)
define_parser(toplabel, std::string)
define_parser(hostname, std::string)
define_parser(port, std::string)
define_parser(h16, unsigned)
define_parser(IPv4address, CppSip::Message::IPv4Address)
define_raw_parser(ls32)
define_raw_parser(IPv6address)
define_parser(host, CppSip::Message::Host)
define_parser(hostport, CppSip::Message::HostPort)
define_parser(Method, CppSip::Message::Method)
define_parser(SIP_Version, CppSip::Message::SipVersion)
define_parser(CSEQ, CppSip::Message::Header::CSeq)
// clang-format on

}  // namespace

BOOST_AUTO_TEST_SUITE( parser )

// BOOST_AUTO_TEST_CASE( test_XXX_parser )
//{
//  namespace x3 = boost::spirit::x3;

//  std::string input = "a ab";
//  std::string result;

//  auto parser = x3::lexeme[ x3::char_('a') >> !x3::char_ | ( x3::char_('a') >> x3::char_('b') ) ];

//  auto b = input.begin();
//  auto e = input.end();

//  auto is_parsed = x3::phrase_parse( b, e, ( parser > parser ), x3::space );

//  BOOST_CHECK( is_parsed );
//  BOOST_CHECK( b == e );
//  //BOOST_CHECK_EQUAL( result, "ab" );
//}

BOOST_AUTO_TEST_CASE( test_ALPHA_parser )
{
  BOOST_CHECK_EQUAL( 'a', parse_ALPHA( "a" ) );
  BOOST_CHECK_EQUAL( 's', parse_ALPHA( "s" ) );
  BOOST_CHECK_EQUAL( 'z', parse_ALPHA( "z" ) );
  BOOST_CHECK_EQUAL( 'A', parse_ALPHA( "A" ) );
  BOOST_CHECK_EQUAL( 'S', parse_ALPHA( "S" ) );
  BOOST_CHECK_EQUAL( 'Z', parse_ALPHA( "Z" ) );

  BOOST_CHECK_THROW( parse_ALPHA( "@" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_ALPHA( "[" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_ALPHA( "`" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_ALPHA( "{" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_DIGIT_parser )
{
  BOOST_CHECK_EQUAL( '0', parse_DIGIT( "0" ) );
  BOOST_CHECK_EQUAL( '5', parse_DIGIT( "5" ) );
  BOOST_CHECK_EQUAL( '9', parse_DIGIT( "9" ) );

  BOOST_CHECK_THROW( parse_DIGIT( "x" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_DIGIT( "/" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_DIGIT( ":" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_HEXDIG_parser )
{
  BOOST_CHECK_EQUAL( '0', parse_HEXDIG( "0" ) );
  BOOST_CHECK_EQUAL( '3', parse_HEXDIG( "3" ) );
  BOOST_CHECK_EQUAL( '9', parse_HEXDIG( "9" ) );
  BOOST_CHECK_EQUAL( 'A', parse_HEXDIG( "A" ) );
  BOOST_CHECK_EQUAL( 'F', parse_HEXDIG( "F" ) );

  BOOST_CHECK_THROW( parse_HEXDIG( "G" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_SP_parser )
{
  BOOST_CHECK_NO_THROW( parse_SP( " " ) );

  BOOST_CHECK_THROW( parse_SP( "a" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_SP( "1" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_SP( "!" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_CR_parser )
{
  BOOST_CHECK_NO_THROW( parse_CR( "\x0D" ) );

  BOOST_CHECK_THROW( parse_SP( "a" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_SP( "1" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_SP( "!" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_LF_parser )
{
  BOOST_CHECK_NO_THROW( parse_LF( "\x0A" ) );

  BOOST_CHECK_THROW( parse_LF( "a" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_LF( "1" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_LF( "!" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_HTAB_parser )
{
  BOOST_CHECK_NO_THROW( parse_HTAB( "\x09" ) );

  BOOST_CHECK_THROW( parse_HTAB( "a" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_HTAB( "1" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_HTAB( "!" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_WSP_parser )
{
  BOOST_CHECK_NO_THROW( parse_WSP( " " ) );
  BOOST_CHECK_NO_THROW( parse_WSP( "\x09" ) );

  BOOST_CHECK_THROW( parse_WSP( "a" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_WSP( "1" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_WSP( "!" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_CRLF_parser )
{
  BOOST_CHECK_NO_THROW( parse_CRLF( "\x0D\x0A" ) );

  BOOST_CHECK_THROW( parse_CRLF( "\x0D" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_CRLF( "\x0A" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_CRLF( "\x0A\x0D" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_alphanum_parser )
{
  BOOST_CHECK_EQUAL( 'a', parse_alphanum( "a" ) );
  BOOST_CHECK_EQUAL( 's', parse_alphanum( "s" ) );
  BOOST_CHECK_EQUAL( 'z', parse_alphanum( "z" ) );
  BOOST_CHECK_EQUAL( 'A', parse_alphanum( "A" ) );
  BOOST_CHECK_EQUAL( 'S', parse_alphanum( "S" ) );
  BOOST_CHECK_EQUAL( 'Z', parse_alphanum( "Z" ) );
  BOOST_CHECK_EQUAL( '0', parse_alphanum( "0" ) );
  BOOST_CHECK_EQUAL( '5', parse_alphanum( "5" ) );
  BOOST_CHECK_EQUAL( '9', parse_alphanum( "9" ) );

  BOOST_CHECK_THROW( parse_alphanum( "*" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_LWS_parser )
{
  BOOST_CHECK_NO_THROW( parse_LWS( " " ) );
  BOOST_CHECK_NO_THROW( parse_LWS( "  " ) );
  BOOST_CHECK_NO_THROW( parse_LWS( " \x09 " ) );

  BOOST_CHECK_NO_THROW( parse_LWS( "  \x0D\x0A   " ) );

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
  BOOST_CHECK_NO_THROW( parse_HCOLON( ": \x09" ) );
  BOOST_CHECK_NO_THROW( parse_HCOLON( " : " ) );
  BOOST_CHECK_NO_THROW( parse_HCOLON( "  : " ) );
  BOOST_CHECK_NO_THROW( parse_HCOLON( " \x09: " ) );

  BOOST_CHECK_THROW( parse_HCOLON( " " ), std::runtime_error );
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
  BOOST_CHECK_EQUAL( "google.com", parse_hostname( "google.com" ) );
  BOOST_CHECK_EQUAL( "google.com.", parse_hostname( "google.com." ) );
  BOOST_CHECK_EQUAL( "goo--gle.com.", parse_hostname( "goo--gle.com." ) );

  BOOST_CHECK_THROW( parse_hostname( "go#gle.com" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_hostname( "google.5" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_hostname( "google.co-" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_port_parser )
{
  BOOST_CHECK_EQUAL( "0", parse_port( "0" ) );
  BOOST_CHECK_EQUAL( "5060", parse_port( "5060" ) );
  BOOST_CHECK_EQUAL( "65535", parse_port( "65535" ) );

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
  BOOST_CHECK_EQUAL( ( CppSip::Message::IPv4Address{ 127, 0, 0, 1 } ), parse_IPv4address( "127.0.0.1" ) );
  BOOST_CHECK_EQUAL( ( CppSip::Message::IPv4Address{ 0, 0, 0, 0 } ), parse_IPv4address( "0.0.0.0" ) );
  BOOST_CHECK_EQUAL( ( CppSip::Message::IPv4Address{ 255, 255, 255, 255 } ), parse_IPv4address( "255.255.255.255" ) );

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
  parse_host( "google.com" );
  parse_host( "127.0.0.1" );
}

BOOST_AUTO_TEST_CASE( test_hostport_parser )
{
  parse_hostport( "google.com" );
  parse_hostport( "google.com:5060" );
  parse_hostport( "192.168.0.1:5060" );
}

BOOST_AUTO_TEST_CASE( test_Method_parser )
{
  BOOST_CHECK_EQUAL( CppSip::Message::Method::Ack, parse_Method( "ACK" ) );
  BOOST_CHECK_EQUAL( CppSip::Message::Method::Bye, parse_Method( "BYE" ) );
  BOOST_CHECK_EQUAL( CppSip::Message::Method::Cancel, parse_Method( "CANCEL" ) );
  BOOST_CHECK_EQUAL( CppSip::Message::Method::Invite, parse_Method( "INVITE" ) );
  BOOST_CHECK_EQUAL( CppSip::Message::Method::Options, parse_Method( "OPTIONS" ) );
  BOOST_CHECK_EQUAL( CppSip::Message::Method::Register, parse_Method( "REGISTER" ) );

  BOOST_CHECK_THROW( parse_Method( "UNKNOWN" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_SIP_Version_parser )
{
  {
    const auto [ major, minor ] = parse_SIP_Version( "SIP/1.0" );
    BOOST_CHECK_EQUAL( "1", major );
    BOOST_CHECK_EQUAL( "0", minor );
  }

  {
    const auto [ major, minor ] = parse_SIP_Version( "SIP/2.1" );
    BOOST_CHECK_EQUAL( "2", major );
    BOOST_CHECK_EQUAL( "1", minor);
  }

  BOOST_CHECK_THROW( parse_SIP_Version( "SIP/2" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_SIP_Version( "SIP2.1" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_SIP_Version( "2.1" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_Request_Line_parser )
{
  // INVITE sip:bob@biloxi.com SIP/2.0
}

BOOST_AUTO_TEST_SUITE_END()
