#include "boost/test/unit_test.hpp"

#include "CppSip/parser/header.h"

#include "parsers/utils.h"

namespace CppSipMsg = CppSip::Message;
namespace CppSipHdr = CppSipMsg::Headers;

namespace
{

// clang-format off
define_parser(display_name, std::string)
define_parser(addr_spec, CppSipHdr::AddrSpec)
define_parser(name_addr, CppSipHdr::NameAddr)
define_parser(gen_value, std::string)
define_parser(generic_param, CppSipHdr::GenericParam)
// clang-format on

}  // namespace

BOOST_AUTO_TEST_SUITE( header_common_parsers )



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

BOOST_AUTO_TEST_SUITE_END()
