#include "boost/test/unit_test.hpp"

#include "CppSip/parser/headers/via.h"

#include "parsers/utils.h"

namespace CppSipMsg = CppSip::Message;
namespace CppSipHdr = CppSip::Message::Headers;

namespace
{
// clang-format off
define_parser(protocol_name, CppSipMsg::Token)
define_parser(protocol_version, CppSipMsg::Token)
define_parser(other_transport, CppSipMsg::Token)
define_parser(transport, CppSipMsg::Token)
define_parser(sent_protocol, CppSipHdr::Via::Protocol)
define_parser(sent_by, CppSipMsg::HostPort)
define_parser(ttl, std::uint8_t)
define_parser(via_extension, CppSipHdr::Via::Extension)
define_parser(via_branch, CppSipHdr::Via::Branch)
define_parser(via_received, CppSipHdr::Via::Received)
define_parser(via_maddr, CppSipHdr::Via::MAddr)
define_parser(via_ttl, CppSipHdr::Via::TTL)
define_parser(via_params, CppSipHdr::Via::Param::Type)
define_parser(via_param, CppSipHdr::Via::Param)
define_parser( Via, CppSipHdr::Via )
// clang-format on
}  // namespace

BOOST_AUTO_TEST_SUITE( header_parsers )

BOOST_AUTO_TEST_CASE( test_protocol_name_parser )
{
}

BOOST_AUTO_TEST_CASE( test_protocol_version_parser )
{
}

BOOST_AUTO_TEST_CASE( test_other_transport_parser )
{
}

BOOST_AUTO_TEST_CASE( test_transport_parser )
{
}

BOOST_AUTO_TEST_CASE( test_sent_protocol_parser )
{
}

BOOST_AUTO_TEST_CASE( test_sent_by_parser )
{
}

BOOST_AUTO_TEST_CASE( test_ttl_parser )
{
}

BOOST_AUTO_TEST_CASE( test_via_extension_parser )
{
}

BOOST_AUTO_TEST_CASE( test_via_branch_parser )
{
}

BOOST_AUTO_TEST_CASE( test_via_received_parser )
{
}

BOOST_AUTO_TEST_CASE( test_via_maddr_parser )
{
}

BOOST_AUTO_TEST_CASE( test_via_ttl_parser )
{
}

BOOST_AUTO_TEST_CASE( test_via_params_parser )
{
}

BOOST_AUTO_TEST_CASE( test_via_param_parser )
{
}

BOOST_AUTO_TEST_CASE( test_Via_parser )
{
}

BOOST_AUTO_TEST_SUITE_END()
