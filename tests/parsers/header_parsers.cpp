#include "boost/test/unit_test.hpp"

#include "CppSip/parser/header_parsers.h"

#include "output/sip_message.h"
#include "output/std.h"
#include "parsers/utils.h"

namespace CppSipMsg = CppSip::Message;

namespace
{

// clang-format off
define_parser(Call_ID, CppSipMsg::Headers::CallId)
define_parser(CSeq, CppSipMsg::Headers::CSeq)
define_parser(Max_Forwards, CppSipMsg::Headers::MaxForwards)
//define_parser(message_header, CppSipMsg::Header)
// clang-format on

}  // namespace

BOOST_AUTO_TEST_SUITE( header_parsers )

BOOST_AUTO_TEST_CASE( test_Call_ID_parser )
{
  BOOST_CHECK_EQUAL("1234567890abcdefg@domain.com", parse_Call_ID("Call-ID: 1234567890abcdefg@domain.com").id );
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
  BOOST_CHECK_EQUAL( "0", parse_Max_Forwards( "Max-Forwards:0" ).forwards );
  BOOST_CHECK_EQUAL( "1", parse_Max_Forwards( "Max-Forwards:1" ).forwards );
  BOOST_CHECK_EQUAL( "1024", parse_Max_Forwards( "Max-Forwards:1024" ).forwards );

  BOOST_CHECK_THROW( parse_Max_Forwards( "Max-Forwards:-1" ), std::runtime_error );
}

BOOST_AUTO_TEST_SUITE_END()
