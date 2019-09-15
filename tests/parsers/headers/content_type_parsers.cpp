#include "boost/test/unit_test.hpp"

#include "CppSip/parser/headers/content_type.h"

#include "parsers/utils.h"

namespace CppSipMsg = CppSip::Message;
namespace CppSipHdr = CppSip::Message::Headers;

namespace
{
// clang-format off
define_parser(ietf_token, CppSipMsg::Token)
define_parser(iana_token, CppSipMsg::Token)
define_parser(x_token, CppSipMsg::Token)
define_parser(extension_token, CppSipMsg::Token)
define_parser(m_subtype, CppSipMsg::Token)
define_parser(discrete_type, CppSipMsg::Token)
define_parser(composite_type, CppSipMsg::Token)
define_parser(m_type, CppSipMsg::Token)
define_parser(m_value, std::string)
define_parser(m_attribute, std::string)
define_parser(m_parameter, CppSipHdr::MediaType::Parameter)
define_parser(media_type, CppSipHdr::MediaType)

define_parser( Content_Type, CppSipHdr::ContentType )
// clang-format on
}  // namespace


BOOST_AUTO_TEST_SUITE( header_parsers )


BOOST_AUTO_TEST_CASE( test_ietf_token_parser )
{
  BOOST_CHECK_EQUAL( "ietf-token", parse_ietf_token( "ietf-token" ) );
}

BOOST_AUTO_TEST_CASE( test_iana_token_parser )
{
  BOOST_CHECK_EQUAL( "iana-token", parse_iana_token( "iana-token" ) );
}

BOOST_AUTO_TEST_CASE( test_x_token_parser )
{
  BOOST_CHECK_EQUAL( "x-abc123", parse_x_token( "x-abc123" ) );

  BOOST_CHECK_THROW( parse_x_token( "abc123" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_extension_token_parser )
{
  BOOST_CHECK_EQUAL( "extension-token", parse_extension_token( "extension-token" ) );
}

BOOST_AUTO_TEST_CASE( test_m_subtype_parser )
{
  BOOST_CHECK_EQUAL( "subtype", parse_m_subtype( "subtype" ) );
}

BOOST_DATA_TEST_CASE( test_discrete_type_parser, TestDatasets::discrete_type )
{
  BOOST_CHECK_EQUAL( sample, parse_discrete_type( sample ) );
}

BOOST_DATA_TEST_CASE( test_composite_type_parser, TestDatasets::composite_type )
{
  BOOST_CHECK_EQUAL( sample, parse_composite_type( sample ) );
}

BOOST_DATA_TEST_CASE( test_m_type_parser, TestDatasets::discrete_type + TestDatasets::composite_type )
{
  BOOST_CHECK_EQUAL( sample, parse_composite_type( sample ) );
}

BOOST_AUTO_TEST_CASE( test_m_value_parser )
{
  BOOST_CHECK_EQUAL( "token", parse_m_value( "token" ) );
  BOOST_CHECK_EQUAL( "token", parse_m_value( "\"token\"" ) );
}

BOOST_AUTO_TEST_CASE( test_m_attribute_parser )
{
  BOOST_CHECK_EQUAL( "attribute", parse_m_attribute( "attribute" ) );
}

BOOST_AUTO_TEST_CASE( test_m_parameter_parser )
{
  {
    const auto [ attr, value ] = parse_m_parameter( "attr=value" );
    BOOST_CHECK_EQUAL( "attr", attr );
    BOOST_CHECK_EQUAL( "value", value );
  }
}

BOOST_AUTO_TEST_CASE( test_media_type_parser )
{
  {
    const auto [ type, subtype, params ] = parse_media_type( "text/html" );
    BOOST_CHECK_EQUAL( "text", type );
    BOOST_CHECK_EQUAL( "html", subtype );
    BOOST_CHECK( params.empty() );
  }

  {
    const auto [ type, subtype, params ] = parse_media_type( "text/html;attr1=value1;attr2=value2" );
    BOOST_CHECK_EQUAL( "text", type );
    BOOST_CHECK_EQUAL( "html", subtype );
    BOOST_REQUIRE_EQUAL( 2, params.size() );
    BOOST_CHECK_EQUAL( "attr1", params[ 0 ].attribute );
    BOOST_CHECK_EQUAL( "value1", params[ 0 ].value );
    BOOST_CHECK_EQUAL( "attr2", params[ 1 ].attribute );
    BOOST_CHECK_EQUAL( "value2", params[ 1 ].value );
  }
}

BOOST_AUTO_TEST_CASE( test_Content_Type_parser )
{
  const auto [ type, subtype, params ] = parse_Content_Type( "Content-Type: application/sdp" ).media_type;
  BOOST_CHECK_EQUAL( "application", type );
  BOOST_CHECK_EQUAL( "sdp", subtype );
  BOOST_CHECK( params.empty() );
}

BOOST_AUTO_TEST_SUITE_END()
