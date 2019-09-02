#include "boost/test/unit_test.hpp"

#include "CppSip/parser/common_sip_parsers.h"

#include "parsers/utils.h"

namespace
{
// clang-format off
define_parser(alphanum, char)
define_noattr_parser(LWS)
define_noattr_parser(SWS)
define_noattr_parser(HCOLON)
// clang-format on
}  // namespace

BOOST_AUTO_TEST_SUITE( common_sip_parsers )

BOOST_DATA_TEST_CASE( test_alphanum_parser,
                      BoostTestData::xrange( '0', '9' ) + BoostTestData::xrange( 'a', 'z' ) + BoostTestData::xrange( 'A', 'Z' ) )
{
  BOOST_CHECK_EQUAL( 'a', parse_alphanum( "a" ) );
  BOOST_CHECK_EQUAL( 's', parse_alphanum( "s" ) );
  BOOST_CHECK_EQUAL( 'z', parse_alphanum( "z" ) );
  BOOST_CHECK_EQUAL( 'A', parse_alphanum( "A" ) );
  BOOST_CHECK_EQUAL( 'S', parse_alphanum( "S" ) );
  BOOST_CHECK_EQUAL( 'Z', parse_alphanum( "Z" ) );
  BOOST_CHECK_EQUAL( '0', parse_alphanum( "0" ) );
  BOOST_CHECK_EQUAL( '5', parse_alphanum( "5" ) );
  BOOST_CHECK_EQUAL( '9', parse_alphanum( "9" ) );
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

BOOST_AUTO_TEST_SUITE_END()
