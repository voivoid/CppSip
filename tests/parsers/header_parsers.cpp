#include "boost/test/unit_test.hpp"

#include "CppSip/parser/header_parsers.h"

#include "output/sip_message.h"
#include "output/std.h"
#include "parsers/utils.h"

namespace CppSipMsg = CppSip::Message;

namespace
{
// clang-format off

define_parser(Call_ID, std::string)
define_parser(CSEQ, CppSipMsg::Header::CSeq)
define_parser(Max_Forwards, std::string)

// clang-format on
}  // namespace

BOOST_AUTO_TEST_SUITE( header_parsers )

BOOST_AUTO_TEST_CASE( test_Call_ID_parser )
{
  BOOST_CHECK_EQUAL( "1234567890abcdefg@domain.com", parse_Call_ID( "Call-ID: 1234567890abcdefg@domain.com" ) );
}

BOOST_AUTO_TEST_CASE( test_CSEQ_parser )
{
  {
    const auto [ id, method ] = parse_CSEQ( "CSeq: 12345 INVITE" );
    BOOST_CHECK_EQUAL( "12345", id );
    BOOST_CHECK_EQUAL( CppSipMsg::Method::Invite, method );
  }
}

BOOST_AUTO_TEST_CASE( test_Max_Forwards_parser )
{
  BOOST_CHECK_EQUAL( "0", parse_Max_Forwards( "Max-Forwards:0" ) );
  BOOST_CHECK_EQUAL( "1", parse_Max_Forwards( "Max-Forwards:1" ) );
  BOOST_CHECK_EQUAL( "1024", parse_Max_Forwards( "Max-Forwards:1024" ) );

  BOOST_CHECK_THROW( parse_Max_Forwards( "Max-Forwards:-1" ), std::runtime_error );
}

BOOST_AUTO_TEST_SUITE_END()
