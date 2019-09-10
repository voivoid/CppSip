#pragma once

#include "boost/test/data/monomorphic/generators/xrange.hpp"
#include "boost/test/data/test_case.hpp"

namespace BoostTestData = boost::unit_test::data;

namespace TestDatasets
{

const auto ALPHA           = BoostTestData::xrange( 'a', 'z' ) + BoostTestData::xrange( 'A', 'Z' );
const auto DIGIT           = BoostTestData::xrange( '0', '9' );
const auto HEXDIG          = DIGIT + BoostTestData::xrange( 'A', 'F' ) + BoostTestData::xrange( 'a', 'f' );
const auto alphanum        = ALPHA + DIGIT;
const auto mark            = BoostTestData::make( '-', '_', '.', '!', '~', '*', '\'', '(', ')' );
const auto reserved        = BoostTestData::make( ';', '/', '?', ':', '@', '&', '=', '+', '$', ',' );
const auto unreserved      = alphanum + mark;
const auto user_unreserved = BoostTestData::make( '&', '=', '+', '$', ',', ';', '?', '/' );
const auto hnv_unreserved  = BoostTestData::make( '[', ']', '/', '?', ':', '+', '$' );
const auto Status_Code     = BoostTestData::make( 100, 200, 300, 400, 500, 600 );
const auto discrete_type   = BoostTestData::make( std::string_view( "text" ),
                                                std::string_view( "image" ),
                                                std::string_view( "audio" ),
                                                std::string_view( "video" ),
                                                std::string_view( "application" ) );
const auto composite_type  = BoostTestData::make( std::string_view( "message" ), std::string_view( "multipart" ) );
const auto quoted_pair =
    BoostTestData::xrange( '\x01', '\x09' ) + BoostTestData::xrange( '\x0B', '\x0C' ) + BoostTestData::xrange( '\x0E', '\x7F' );
const auto qdtext = BoostTestData::make( '\x21' ) + BoostTestData::xrange( '\x23', '\x5B' ) + BoostTestData::xrange( '\x5D', '\x7E' );

}  // namespace TestDatasets
