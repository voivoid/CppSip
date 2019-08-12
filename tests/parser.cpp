#include "boost/test/unit_test.hpp"

#include "CppSip/parser/parser.h"
#include "test_utils/message.h"

BOOST_AUTO_TEST_SUITE( parser )

BOOST_AUTO_TEST_CASE( parse_sip_method )
{
  BOOST_CHECK( CppSip::Method::Ack == CppSip::parse_method( "ACK" ) );
  BOOST_CHECK( CppSip::Method::Bye == CppSip::parse_method( "BYE" ) );
  BOOST_CHECK( CppSip::Method::Cancel == CppSip::parse_method( "CANCEL" ) );
  BOOST_CHECK( CppSip::Method::Invite == CppSip::parse_method( "INVITE" ) );
  BOOST_CHECK( CppSip::Method::Options == CppSip::parse_method( "OPTIONS" ) );
  BOOST_CHECK( CppSip::Method::Register == CppSip::parse_method( "REGISTER" ) );  
}

BOOST_AUTO_TEST_SUITE_END()