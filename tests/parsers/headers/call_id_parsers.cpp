#include "boost/test/unit_test.hpp"

#include "CppSip/parser/headers/call_id.h"

#include "parsers/utils.h"

namespace CppSipHdr = CppSip::Message::Headers;

namespace
{
define_parser( Call_ID, CppSipHdr::CallId )
}

BOOST_AUTO_TEST_SUITE( header_parsers )

BOOST_AUTO_TEST_CASE( test_Call_ID_parser )
{
  BOOST_CHECK_EQUAL( "1234567890abcdefg@domain.com", parse_Call_ID( "Call-ID: 1234567890abcdefg@domain.com" ).id );
}

BOOST_AUTO_TEST_SUITE_END()
