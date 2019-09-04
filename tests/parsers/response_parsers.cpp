#include "boost/test/unit_test.hpp"

#include "CppSip/parser/response_parsers.h"

#include "parsers/utils.h"


#include <iostream>

namespace CppSipMsg = CppSip::Message;


namespace
{
// clang-format off
define_parser(Reason_Phrase, std::string)
define_parser(Status_Code, std::uint16_t)
define_parser(Status_Line, CppSipMsg::StatusLine)
define_parser(Response, CppSipMsg::Response)
// clang-format on
}  // namespace

BOOST_AUTO_TEST_SUITE( response_parsers )

BOOST_AUTO_TEST_CASE( test_Reason_Phrase_parser )
{
  BOOST_CHECK_EQUAL( "OK", parse_Reason_Phrase( "OK" ) );
}

BOOST_DATA_TEST_CASE( test_Status_Code_parser, TestDatasets::Status_Code )
{
  BOOST_CHECK_EQUAL( sample, parse_Status_Code( std::to_string( sample ) ) );
}

BOOST_AUTO_TEST_CASE( test_Status_Line_parser )
{
  {
    auto [ sip_version, status_code, reason ] = parse_Status_Line( "SIP/2.0 200 OK\r\n" );
    BOOST_CHECK_EQUAL( "2", sip_version.major );
    BOOST_CHECK_EQUAL( "0", sip_version.minor );
    BOOST_CHECK_EQUAL( 200, status_code );
    BOOST_CHECK_EQUAL( "OK", reason );
  }
}

BOOST_AUTO_TEST_CASE( test_Response_parser )
{
}

BOOST_AUTO_TEST_SUITE_END()
