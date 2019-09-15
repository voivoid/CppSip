#include "boost/test/unit_test.hpp"

#include "CppSip/parser/header.h"

#include "parsers/utils.h"

namespace CppSipHdr = CppSip::Message::Headers;

namespace
{
define_parser( message_header, CppSip::Message::Header )
}  // namespace

BOOST_AUTO_TEST_SUITE( header_parsers )

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

  {
    auto header = parse_message_header( "Via: SIP/2.0/UDP domain.com;branch=abc123\r\n" );
    BOOST_CHECK( boost::get<CppSipHdr::Via>( &header ) );
  }
}

BOOST_AUTO_TEST_SUITE_END()
