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
define_parser(token, std::string)
define_parser(mark, char)
define_parser(unreserved, char)
define_parser(reserved, char)
define_parser(escaped, char)
define_parser(word, std::string)
define_parser(callid, std::string)
define_parser(Method, CppSipMsg::Method)
define_parser(SIP_Version, CppSipMsg::SipVersion)
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

BOOST_AUTO_TEST_CASE(test_SLASH_parser)
{
  BOOST_CHECK_NO_THROW(parse_SLASH("/"));
  BOOST_CHECK_NO_THROW(parse_SLASH("/ "));
  BOOST_CHECK_NO_THROW(parse_SLASH(" /"));
  BOOST_CHECK_NO_THROW(parse_SLASH(" / "));
}

BOOST_AUTO_TEST_CASE(test_SEMI_parser)
{
  BOOST_CHECK_NO_THROW(parse_SEMI(";"));
  BOOST_CHECK_NO_THROW(parse_SEMI("; "));
  BOOST_CHECK_NO_THROW(parse_SEMI(" ;"));
  BOOST_CHECK_NO_THROW(parse_SEMI(" ; "));
}

BOOST_AUTO_TEST_CASE(test_token_parser)
{
  BOOST_CHECK_EQUAL("abc-.!%*_+`'~", parse_token("abc-.!%*_+`'~"));
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


BOOST_AUTO_TEST_SUITE_END()
