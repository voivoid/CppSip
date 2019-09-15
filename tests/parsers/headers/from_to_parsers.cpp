#include "boost/test/unit_test.hpp"

#include "CppSip/parser/headers/from_to.h"

#include "parsers/utils.h"

namespace CppSipHdr = CppSip::Message::Headers;

namespace
{
// clang-format off
define_parser( tag_param, CppSipHdr::GenericParam )
define_parser( from_to_param, CppSipHdr::FromTo::Param )
define_parser( from_to_spec, CppSipHdr::FromTo )
define_parser( From, CppSipHdr::From )
define_parser( To, CppSipHdr::To )
// clang-format on
}  // namespace

BOOST_AUTO_TEST_SUITE( header_parsers )

BOOST_AUTO_TEST_CASE( test_tag_param_parser )
{
  {
    const auto [ param, value ] = parse_tag_param( "tag=value" );
    BOOST_CHECK_EQUAL( "tag", param );
    BOOST_REQUIRE( value );
    BOOST_CHECK_EQUAL( "value", *value );
  }

  BOOST_CHECK_THROW( parse_tag_param( "tag" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_from_to_param_parser )
{
  {
    const auto [ param, value ] = parse_from_to_param( "param" );
    BOOST_CHECK_EQUAL( "param", param );
    BOOST_REQUIRE( !value );
  }

  {
    const auto [ param, value ] = parse_from_to_param( "param=value" );
    BOOST_CHECK_EQUAL( "param", param );
    BOOST_REQUIRE( value );
    BOOST_CHECK_EQUAL( "value", *value );
  }

  {
    const auto [ param, value ] = parse_from_to_param( "tag=value" );
    BOOST_CHECK_EQUAL( "tag", param );
    BOOST_REQUIRE( value );
    BOOST_CHECK_EQUAL( "value", *value );
  }
}

BOOST_AUTO_TEST_CASE( test_from_to_spec_parser )
{
  {
    const auto [ addr, params ] = parse_from_to_spec( "<sip:domain.com>" );
    BOOST_CHECK( boost::get<CppSipHdr::NameAddr>( &addr ) );
    BOOST_CHECK( params.empty() );
  }

  {
    const auto [ addr, params ] = parse_from_to_spec( "sip:domain.com" );
    BOOST_CHECK( boost::get<CppSipHdr::AddrSpec>( &addr ) );
    BOOST_CHECK( params.empty() );
  }

  {
    const auto [ addr, params ] = parse_from_to_spec( "<sip:domain.com>;tag=12345" );
    BOOST_REQUIRE( params.size() == 1 );
    BOOST_CHECK_EQUAL( "tag", params[ 0 ].param );
    BOOST_CHECK_EQUAL( "12345", *params[ 0 ].value );
  }
}

BOOST_AUTO_TEST_CASE( test_From_parser )
{
  {
    const auto [ addr, params ] = parse_From( "From: <sip:domain.com>" );
    BOOST_CHECK( boost::get<CppSipHdr::NameAddr>( &addr ) );
    BOOST_CHECK( params.empty() );
  }

  {
    const auto [ addr, params ] = parse_From( "From: <sip:domain.com>;tag=12345" );
    BOOST_REQUIRE( params.size() == 1 );
    BOOST_CHECK_EQUAL( "tag", params[ 0 ].param );
    BOOST_CHECK_EQUAL( "12345", *params[ 0 ].value );
  }
}

BOOST_AUTO_TEST_CASE( test_To_parser )
{
  {
    const auto [ addr, params ] = parse_To( "To: <sip:domain.com>" );
    BOOST_CHECK( boost::get<CppSipHdr::NameAddr>( &addr ) );
    BOOST_CHECK( params.empty() );
  }

  {
    const auto [ addr, params ] = parse_To( "To: <sip:domain.com>;tag=12345" );
    BOOST_REQUIRE( params.size() == 1 );
    BOOST_CHECK_EQUAL( "tag", params[ 0 ].param );
    BOOST_CHECK_EQUAL( "12345", *params[ 0 ].value );
  }
}

BOOST_AUTO_TEST_SUITE_END()
