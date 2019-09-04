#include "boost/test/unit_test.hpp"

#include "CppSip/parser/message_parser.h"

#include "parsers/utils.h"

namespace
{
define_parser( SIP_message, CppSip::Message::Message )
}

BOOST_AUTO_TEST_SUITE( message_parsers )

BOOST_AUTO_TEST_CASE( test_SIP_message_parser )
{
}

BOOST_AUTO_TEST_SUITE_END()
