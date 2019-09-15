#include "boost/test/unit_test.hpp"

#include "CppSip/parser/headers/cseq.h"

#include "parsers/utils.h"

namespace CppSipHdr = CppSip::Message::Headers;

namespace
{
define_parser( CSeq, CppSipHdr::CSeq )
}


BOOST_AUTO_TEST_SUITE( header_parsers )

BOOST_AUTO_TEST_CASE( test_CSEQ_parser )
{
  {
    const auto [ id, method ] = parse_CSeq( "CSeq: 12345 INVITE" );
    BOOST_CHECK_EQUAL( "12345", id );
    BOOST_CHECK_EQUAL( CppSip::Message::Method::Invite, method );
  }
}

BOOST_AUTO_TEST_SUITE_END()
