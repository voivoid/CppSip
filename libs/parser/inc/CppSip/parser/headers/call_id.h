#pragma once

#include "CppSip/message/headers/callid.h"

#include "CppSip/parser/common.h"

#include "boost/fusion/include/adapt_struct.hpp"

BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::CallId, id )

namespace CppSip
{
namespace Parsers
{

namespace bsx3 = boost::spirit::x3;

// Call-ID = ( "Call-ID" / "i" ) HCOLON callid
inline const auto Call_ID = bsx3::rule<struct _callid, CppSip::Message::Headers::CallId>{ "Call-ID" } =
    ( bsx3::no_case[ ( bsx3::lit( "Call-ID" ) | 'i' ) ] >> HCOLON ) > callid;

}  // namespace Parsers
}  // namespace CppSip
