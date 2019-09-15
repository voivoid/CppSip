#include "boost/test/unit_test.hpp"

#include "CppSip/parser/headers/max_forwards.h"

#include "parsers/utils.h"

namespace CppSipHdr = CppSip::Message::Headers;

namespace
{
define_parser( Max_Forwards, CppSipHdr::MaxForwards )
}

BOOST_AUTO_TEST_SUITE( header_parsers )

BOOST_AUTO_TEST_CASE( test_Max_Forwards_parser )
{
  BOOST_CHECK_EQUAL( 0, parse_Max_Forwards( "Max-Forwards:0" ).forwards );
  BOOST_CHECK_EQUAL( 1, parse_Max_Forwards( "Max-Forwards:1" ).forwards );
  BOOST_CHECK_EQUAL( 1024, parse_Max_Forwards( "Max-Forwards:1024" ).forwards );

  BOOST_CHECK_THROW( parse_Max_Forwards( "Max-Forwards:-1" ), std::runtime_error );
}


BOOST_AUTO_TEST_SUITE_END()
