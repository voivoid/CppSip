#include "boost/test/unit_test.hpp"

#include "CppSip/parser/header_parsers.h"

#include "parsers/utils.h"

namespace CppSipHdr = CppSip::Message::Headers;

namespace
{

// clang-format off

define_parser(ietf_token, std::string)
define_parser(iana_token, std::string)
define_parser(x_token, std::string)
define_parser(extension_token, std::string)
define_parser(m_subtype, std::string)
define_parser(discrete_type, std::string)
define_parser(composite_type, std::string)
define_parser(m_type, std::string)
define_parser(m_value, std::string)
define_parser(m_attribute, std::string)
define_parser(m_parameter, CppSipHdr::MediaType::Parameter)
define_parser(media_type, CppSipHdr::MediaType)
define_parser(display_name, std::string)
define_parser(addr_spec, CppSipHdr::AddrSpec)
define_parser(name_addr, CppSipHdr::NameAddr)
define_parser(gen_value, std::string)

define_parser(Call_ID, CppSipHdr::CallId)
define_parser(Content_Length, CppSipHdr::ContentLength)
define_parser(Content_Type, CppSipHdr::ContentType)
define_parser(CSeq, CppSipHdr::CSeq)
define_parser(Max_Forwards, CppSipHdr::MaxForwards)

define_parser(message_header, CppSip::Message::Header)
// clang-format on

}  // namespace

BOOST_AUTO_TEST_SUITE( header_parsers )

BOOST_AUTO_TEST_CASE( test_ietf_token_parser )
{
}

BOOST_AUTO_TEST_CASE( test_iana_token_parser )
{
}

BOOST_AUTO_TEST_CASE( test_x_token_parser )
{
  BOOST_CHECK_EQUAL( "x-abc123", parse_x_token( "x-abc123" ) );

  BOOST_CHECK_THROW( parse_x_token( "abc123" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_extension_token_parser )
{
}

BOOST_AUTO_TEST_CASE( test_m_subtype_parser )
{
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
}

BOOST_AUTO_TEST_CASE( test_m_attribute_parser )
{
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
  // BOOST_CHECK_EQUAL( "cool name", parse_display_name( "cool name" ) );
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
    // const auto [ display_name, addr ] = parse_name_addr( "john doe <sip:domain.com>" );
  }
}

BOOST_AUTO_TEST_CASE( test_gen_value_parser )
{
}

BOOST_AUTO_TEST_CASE( test_Call_ID_parser )
{
  BOOST_CHECK_EQUAL( "1234567890abcdefg@domain.com", parse_Call_ID( "Call-ID: 1234567890abcdefg@domain.com" ).id );
}

BOOST_AUTO_TEST_CASE( test_Content_Length_parser )
{
  BOOST_CHECK_EQUAL( 0, parse_Content_Length( "Content-Length: 0" ).length );
  BOOST_CHECK_EQUAL( 1024, parse_Content_Length( "Content-Length: 1024" ).length );
  BOOST_CHECK_EQUAL( 4294967295, parse_Content_Length( "Content-Length: 4294967295" ).length );
  BOOST_CHECK_EQUAL( 18446744073709551615ULL, parse_Content_Length( "Content-Length: 18446744073709551615" ).length );
}

BOOST_AUTO_TEST_CASE( test_Content_Type_parser )
{
  {
    const auto [ type, subtype, params ] = parse_Content_Type( "Content-Type: application/sdp" ).media_type;
    BOOST_CHECK_EQUAL( "application", type );
    BOOST_CHECK_EQUAL( "sdp", subtype );
    BOOST_CHECK( params.empty() );
  }
}

BOOST_AUTO_TEST_CASE( test_CSEQ_parser )
{
  {
    const auto [ id, method ] = parse_CSeq( "CSeq: 12345 INVITE" );
    BOOST_CHECK_EQUAL( "12345", id );
    BOOST_CHECK_EQUAL( CppSip::Message::Method::Invite, method );
  }
}

BOOST_AUTO_TEST_CASE( test_Max_Forwards_parser )
{
  BOOST_CHECK_EQUAL( 0, parse_Max_Forwards( "Max-Forwards:0" ).forwards );
  BOOST_CHECK_EQUAL( 1, parse_Max_Forwards( "Max-Forwards:1" ).forwards );
  BOOST_CHECK_EQUAL( 1024, parse_Max_Forwards( "Max-Forwards:1024" ).forwards );

  BOOST_CHECK_THROW( parse_Max_Forwards( "Max-Forwards:-1" ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( test_message_header_parser )
{
}

BOOST_AUTO_TEST_SUITE_END()
