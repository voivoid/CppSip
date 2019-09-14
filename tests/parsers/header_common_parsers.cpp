#include "boost/test/unit_test.hpp"

#include "CppSip/parser/header_parsers.h"

#include "parsers/utils.h"

namespace CppSipMsg = CppSip::Message;
namespace CppSipHdr = CppSipMsg::Headers;


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
define_parser(display_name, std::string)
define_parser(addr_spec, CppSipHdr::AddrSpec)
define_parser(name_addr, CppSipHdr::NameAddr)
define_parser(gen_value, std::string)
define_parser(generic_param, CppSipHdr::GenericParam)
define_parser(tag_param, CppSipHdr::GenericParam)
define_parser(from_to_param, CppSipHdr::FromTo::Param)
define_parser(from_to_spec, CppSipHdr::FromTo)
define_parser(protocol_name, CppSipMsg::Token)
define_parser(protocol_version, CppSipMsg::Token)
define_parser(other_transport, CppSipMsg::Token)
define_parser(transport, CppSipMsg::Token)

// clang-format on

}  // namespace

BOOST_AUTO_TEST_SUITE( header_common_parsers )

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

BOOST_AUTO_TEST_CASE( test_display_name_parser )
{
  BOOST_CHECK_EQUAL( "name", parse_display_name( "\"name\"" ) );
  BOOST_CHECK_EQUAL( "name", parse_display_name( "name  " ) );
  BOOST_CHECK_EQUAL( "cool name", parse_display_name( "\"cool\\ name\"" ) );
  BOOST_CHECK_EQUAL( "cool name", parse_display_name( "cool name " ) );
}

BOOST_AUTO_TEST_CASE( test_addr_spec_parser )
{
  {
    const auto [ sips, userinfo, hostport, sip_uri_headers ] = parse_addr_spec( "sip:domain.com" ).sip_uri;
    BOOST_CHECK( !sips );
    BOOST_CHECK( !userinfo );
    BOOST_CHECK_EQUAL( ( CppSip::Message::HostPort{ { "domain.com" }, {} } ), hostport );
    BOOST_CHECK( sip_uri_headers.empty() );
  }
}

BOOST_AUTO_TEST_CASE( test_name_addr_parser )
{
  {
    const auto [ display_name, addr ] = parse_name_addr( "<sip:domain.com>" );
    BOOST_CHECK( display_name.empty() );
    BOOST_CHECK_EQUAL( ( CppSip::Message::HostPort{ { "domain.com" }, {} } ), addr.sip_uri.host_port );
  }

  {
    const auto [ display_name, addr ] = parse_name_addr( "john doe <sip:domain.com>" );
    BOOST_CHECK_EQUAL( "john doe", display_name );
  }
}

BOOST_AUTO_TEST_CASE( test_gen_value_parser )
{
  BOOST_CHECK_EQUAL( "gen_value", parse_gen_value( "gen_value" ) );
  BOOST_CHECK_EQUAL( "127.0.0.1", parse_gen_value( "127.0.0.1" ) );
}

BOOST_AUTO_TEST_CASE( test_generic_param_parser )
{
  {
    const auto [ param, value ] = parse_generic_param( "param" );
    BOOST_CHECK_EQUAL( "param", param );
    BOOST_CHECK( !value );
  }

  {
    const auto [ param, value ] = parse_generic_param( "param=value" );
    BOOST_CHECK_EQUAL( "param", param );
    BOOST_REQUIRE( value );
    BOOST_CHECK_EQUAL( "value", *value );
  }
}

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

BOOST_AUTO_TEST_SUITE_END()
