#include "boost/test/unit_test.hpp"

#include "CppSip/parser/headers/contact.h"

#include "parsers/utils.h"

namespace CppSipHdr = CppSip::Message::Headers;

namespace
{
// clang-format off
define_parser(c_p_q, std::string)
define_parser(delta_seconds, std::uint32_t)
define_parser(c_p_expires, std::uint32_t)
define_parser(contact_extension, CppSipHdr::GenericParam)
// clang-format on
}  // namespace

BOOST_AUTO_TEST_SUITE( header_parsers )

BOOST_AUTO_TEST_SUITE_END()
