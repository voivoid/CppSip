#include "boost/test/unit_test.hpp"

#include "CppSip/parser/header_parsers.h"

#include "parsers/utils.h"

namespace CppSipMsg = CppSip::Message;

namespace
{

// clang-format off
define_parser(Call_ID, CppSipMsg::Headers::CallId)
define_parser(Content_Length, CppSip::Message::Headers::ContentLength)
define_parser(ietf_token, std::string)
define_parser(iana_token, std::string)
define_parser(m_attribute, std::string)
define_parser(x_token, std::string)
define_parser(m_subtype, std::string)
define_parser(extension_token, std::string)
define_parser(discrete_type, std::string)
define_parser(composite_type, std::string)
define_parser(m_type, std::string)
define_parser(m_value, std::string)
define_parser(CSeq, CppSipMsg::Headers::CSeq)
define_parser(Max_Forwards, CppSipMsg::Headers::MaxForwards)
define_parser(message_header, CppSipMsg::Header)
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

BOOST_DATA_TEST_CASE( test_discrete_type_parser, TestDatasets::discrete_type )
{
  BOOST_CHECK_EQUAL( sample, parse_discrete_type( sample ) );
}

BOOST_AUTO_TEST_CASE( test_CSEQ_parser )
{
  {
    const auto [ id, method ] = parse_CSeq( "CSeq: 12345 INVITE" );
    BOOST_CHECK_EQUAL( "12345", id );
    BOOST_CHECK_EQUAL( CppSipMsg::Method::Invite, method );
  }
}

BOOST_AUTO_TEST_CASE( test_Max_Forwards_parser )
{
  BOOST_CHECK_EQUAL( 0, parse_Max_Forwards( "Max-Forwards:0" ).forwards );
  BOOST_CHECK_EQUAL( 1, parse_Max_Forwards( "Max-Forwards:1" ).forwards );
  BOOST_CHECK_EQUAL( 1024, parse_Max_Forwards( "Max-Forwards:1024" ).forwards );

  BOOST_CHECK_THROW( parse_Max_Forwards( "Max-Forwards:-1" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_message_header_parser )
{
}

BOOST_AUTO_TEST_SUITE_END()
