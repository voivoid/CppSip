#include "boost/test/unit_test.hpp"

#include "CppSip/parser/header_parsers.h"

#include "parsers/utils.h"

namespace CppSipHdr = CppSip::Message::Headers;

namespace
{

// clang-format off
define_parser(Call_ID, CppSipHdr::CallId)
define_parser(Content_Length, CppSipHdr::ContentLength)
define_parser(Content_Type, CppSipHdr::ContentType)
define_parser(CSeq, CppSipHdr::CSeq)
define_parser(From, CppSipHdr::From)
define_parser(Max_Forwards, CppSipHdr::MaxForwards)
define_parser(To, CppSipHdr::To)
define_parser(message_header, CppSip::Message::Header)
// clang-format on

}  // namespace

BOOST_AUTO_TEST_SUITE( header_parsers )

BOOST_AUTO_TEST_CASE( test_Call_ID_parser )
{
  BOOST_CHECK_EQUAL( "1234567890abcdefg@domain.com", parse_Call_ID( "Call-ID: 1234567890abcdefg@domain.com" ).id );
}

BOOST_AUTO_TEST_CASE( test_Content_Length_parser )
{
  BOOST_CHECK_EQUAL( 0, parse_Content_Length( "Content-Length: 0" ).length );
  BOOST_CHECK_EQUAL( 1024, parse_Content_Length( "Content-Length: 1024" ).length );
  BOOST_CHECK_EQUAL( 4294967295, parse_Content_Length( "Content-Length: 4294967295" ).length );
  BOOST_CHECK_EQUAL( 18446744073709551615ULL, parse_Content_Length( "Content-Length: 18446744073709551615" ).length );
}

BOOST_AUTO_TEST_CASE( test_Content_Type_parser )
{
  {
    const auto [ type, subtype, params ] = parse_Content_Type( "Content-Type: application/sdp" ).media_type;
    BOOST_CHECK_EQUAL( "application", type );
    BOOST_CHECK_EQUAL( "sdp", subtype );
    BOOST_CHECK( params.empty() );
  }
}

BOOST_AUTO_TEST_CASE( test_CSEQ_parser )
{
  {
    const auto [ id, method ] = parse_CSeq( "CSeq: 12345 INVITE" );
    BOOST_CHECK_EQUAL( "12345", id );
    BOOST_CHECK_EQUAL( CppSip::Message::Method::Invite, method );
  }
}

BOOST_AUTO_TEST_CASE( test_From_parser )
{
  {
    const auto [ addr, params ] = parse_From( "From: <sip:domain.com>" );
    BOOST_CHECK( boost::get<CppSipHdr::NameAddr>( &addr ) );
    BOOST_CHECK( params.empty() );
  }

  {
    const auto [ addr, params ] = parse_From( "From: <sip:domain.com>;tag=12345" );
    BOOST_REQUIRE( params.size() == 1 );
    BOOST_CHECK_EQUAL( "tag", params[ 0 ].param );
    BOOST_CHECK_EQUAL( "12345", *params[ 0 ].value );
  }
}

BOOST_AUTO_TEST_CASE( test_Max_Forwards_parser )
{
  BOOST_CHECK_EQUAL( 0, parse_Max_Forwards( "Max-Forwards:0" ).forwards );
  BOOST_CHECK_EQUAL( 1, parse_Max_Forwards( "Max-Forwards:1" ).forwards );
  BOOST_CHECK_EQUAL( 1024, parse_Max_Forwards( "Max-Forwards:1024" ).forwards );

  BOOST_CHECK_THROW( parse_Max_Forwards( "Max-Forwards:-1" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_To_parser )
{
  {
    const auto [ addr, params ] = parse_To( "To: <sip:domain.com>" );
    BOOST_CHECK( boost::get<CppSipHdr::NameAddr>( &addr ) );
    BOOST_CHECK( params.empty() );
  }

  {
    const auto [ addr, params ] = parse_To( "To: <sip:domain.com>;tag=12345" );
    BOOST_REQUIRE( params.size() == 1 );
    BOOST_CHECK_EQUAL( "tag", params[ 0 ].param );
    BOOST_CHECK_EQUAL( "12345", *params[ 0 ].value );
  }
}

BOOST_AUTO_TEST_CASE( test_message_header_parser )
{
  {
    auto header = parse_message_header( "Call-ID: 1234567890abcdefg@domain.com\r\n" );
    BOOST_CHECK( boost::get<CppSipHdr::CallId>( &header ) );
  }

  {
    auto header = parse_message_header( "Content-Length: 1024\r\n" );
    BOOST_CHECK( boost::get<CppSipHdr::ContentLength>( &header ) );
  }

  {
    auto header = parse_message_header( "Content-Type: application/sdp\r\n" );
    BOOST_CHECK( boost::get<CppSipHdr::ContentType>( &header ) );
  }

  {
    auto header = parse_message_header( "CSeq: 12345 INVITE\r\n" );
    BOOST_CHECK( boost::get<CppSipHdr::CSeq>( &header ) );
  }

  {
    auto header = parse_message_header( "From: <sip:domain.com>;tag=12345\r\n" );
    BOOST_CHECK( boost::get<CppSipHdr::From>( &header ) );
  }

  {
    auto header = parse_message_header( "Max-Forwards:70\r\n" );
    BOOST_CHECK( boost::get<CppSipHdr::MaxForwards>( &header ) );
  }

  {
    auto header = parse_message_header( "To: <sip:domain.com>;tag=12345\r\n" );
    BOOST_CHECK( boost::get<CppSipHdr::To>( &header ) );
  }
}

BOOST_AUTO_TEST_SUITE_END()
