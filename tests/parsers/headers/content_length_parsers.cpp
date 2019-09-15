#include "boost/test/unit_test.hpp"

#include "CppSip/parser/headers/content_length.h"

#include "parsers/utils.h"

namespace CppSipHdr = CppSip::Message::Headers;

namespace
{
define_parser( Content_Length, CppSipHdr::ContentLength )
}


BOOST_AUTO_TEST_SUITE( header_parsers )

BOOST_AUTO_TEST_CASE( test_Content_Length_parser )
{
  BOOST_CHECK_EQUAL( 0, parse_Content_Length( "Content-Length: 0" ).length );
  BOOST_CHECK_EQUAL( 1024, parse_Content_Length( "Content-Length: 1024" ).length );
  BOOST_CHECK_EQUAL( 4294967295, parse_Content_Length( "Content-Length: 4294967295" ).length );
  BOOST_CHECK_EQUAL( 18446744073709551615ULL, parse_Content_Length( "Content-Length: 18446744073709551615" ).length );
}

BOOST_AUTO_TEST_SUITE_END()
