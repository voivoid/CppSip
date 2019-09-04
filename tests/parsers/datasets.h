#pragma once

#include "boost/test/data/monomorphic/generators/xrange.hpp"
#include "boost/test/data/test_case.hpp"

namespace BoostTestData = boost::unit_test::data;

namespace TestDatasets
{

const auto ALPHA           = BoostTestData::xrange( 'a', 'z' ) + BoostTestData::xrange( 'A', 'Z' );
const auto DIGIT           = BoostTestData::xrange( '0', '9' );
const auto HEX             = DIGIT + BoostTestData::xrange( 'A', 'F' );
const auto alphanum        = ALPHA + DIGIT;
const auto mark            = BoostTestData::make( '-', '_', '.', '!', '~', '*', '\'', '(', ')' );
const auto reserved        = BoostTestData::make( ';', '/', '?', ':', '@', '&', '=', '+', '$', ',' );
const auto unreserved      = alphanum + mark;
const auto user_unreserved = BoostTestData::make( '&', '=', '+', '$', ',', ';', '?', '/' );
const auto hnv_unreserved  = BoostTestData::make( '[', ']', '/', '?', ':', '+', '$' );
const auto Status_Code     = BoostTestData::make( 100, 200, 300, 400, 500, 600 );

}  // namespace TestDatasets
