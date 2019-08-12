#include "catch2/catch.hpp"

#include "CppSip/parser/parser.h"
#include "test_utils/message.h"

TEST_CASE("Parse SIP methods", "parser")
{
  CHECK( CppSip::Method::Ack == CppSip::parse_method( "ACK" ) );
  CHECK( CppSip::Method::Bye == CppSip::parse_method( "BYE" ) );
  CHECK( CppSip::Method::Cancel == CppSip::parse_method( "CANCEL" ) );
  CHECK( CppSip::Method::Invite == CppSip::parse_method( "INVITE" ) );
  CHECK( CppSip::Method::Options == CppSip::parse_method( "OPTIONS" ) );
  CHECK( CppSip::Method::Register == CppSip::parse_method( "REGISTER" ) );  
}