#include "boost/test/unit_test.hpp"

#include "CppSip/parser/abnf_core_parsers.h"

#include "parsers/utils.h"

namespace
{
// clang-format off
define_parser(ALPHA, char)
define_parser(DIGIT, char)
define_parser(HEXDIG, char)
define_noattr_parser(SP)
define_noattr_parser(CR)
define_noattr_parser(LF)
define_noattr_parser(HTAB)
define_noattr_parser(WSP)
define_noattr_parser(CRLF)

const auto ALPHA_test_data = BoostTestData::xrange( 'a', 'z' ) + BoostTestData::xrange( 'A', 'Z' );
const auto DIGIT_test_data = BoostTestData::xrange( '0', '9' );
const auto HEX_test_data   = DIGIT_test_data + BoostTestData::xrange( 'A', 'F' );
// clang-format on
}  // namespace


BOOST_AUTO_TEST_SUITE( abnf_core_parsers )

BOOST_DATA_TEST_CASE( test_ALPHA_parser, ALPHA_test_data )
{
  BOOST_CHECK_EQUAL( sample, parse_ALPHA( std::string_view( &sample, 1 ) ) );
}

BOOST_AUTO_TEST_CASE( test_ALPHA_parser_failures )
{
  BOOST_CHECK_THROW( parse_ALPHA( "@" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_ALPHA( "[" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_ALPHA( "`" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_ALPHA( "{" ), std::runtime_error );
}

BOOST_DATA_TEST_CASE( test_DIGIT_parser, DIGIT_test_data )
{
  BOOST_CHECK_EQUAL( sample, parse_DIGIT( std::string_view( &sample, 1 ) ) );
}

BOOST_AUTO_TEST_CASE( test_DIGIT_parser_failures )
{
  BOOST_CHECK_THROW( parse_DIGIT( "x" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_DIGIT( "/" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_DIGIT( ":" ), std::runtime_error );
}

BOOST_DATA_TEST_CASE( test_HEXDIG_parser, HEX_test_data )
{
  BOOST_CHECK_EQUAL( sample, parse_HEXDIG( std::string_view( &sample, 1 ) ) );
}

BOOST_AUTO_TEST_CASE( test_HEXDIG_parser_failures )
{
  BOOST_CHECK_THROW( parse_HEXDIG( "-" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_HEXDIG( "a" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_HEXDIG( "G" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_SP_parser )
{
  BOOST_CHECK_NO_THROW( parse_SP( " " ) );

  BOOST_CHECK_THROW( parse_SP( "a" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_SP( "1" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_SP( "!" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_CR_parser )
{
  BOOST_CHECK_NO_THROW( parse_CR( "\r" ) );

  BOOST_CHECK_THROW( parse_SP( "a" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_SP( "1" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_SP( "!" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_LF_parser )
{
  BOOST_CHECK_NO_THROW( parse_LF( "\n" ) );

  BOOST_CHECK_THROW( parse_LF( "a" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_LF( "1" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_LF( "!" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_HTAB_parser )
{
  BOOST_CHECK_NO_THROW( parse_HTAB( "\t" ) );

  BOOST_CHECK_THROW( parse_HTAB( "a" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_HTAB( "1" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_HTAB( "!" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_WSP_parser )
{
  BOOST_CHECK_NO_THROW( parse_WSP( " " ) );
  BOOST_CHECK_NO_THROW( parse_WSP( "\t" ) );

  BOOST_CHECK_THROW( parse_WSP( "a" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_WSP( "1" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_WSP( "!" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_CRLF_parser )
{
  BOOST_CHECK_NO_THROW( parse_CRLF( "\r\n" ) );

  BOOST_CHECK_THROW( parse_CRLF( "\r" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_CRLF( "\n" ), std::runtime_error );
  BOOST_CHECK_THROW( parse_CRLF( "\n\r" ), std::runtime_error );
}

BOOST_AUTO_TEST_SUITE_END()
