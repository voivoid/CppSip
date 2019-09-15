#pragma once

#include "CppSip/message/headers/max_forwards.h"

#include "CppSip/parser/common.h"

#include "boost/fusion/include/adapt_struct.hpp"

BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::MaxForwards, forwards )

namespace CppSip
{
namespace Parsers
{

// Max-Forwards = "Max-Forwards" HCOLON 1*DIGIT
inline const auto Max_Forwards = bsx3::rule<struct _max_forwards, CppSip::Message::Headers::MaxForwards>{ "Max-Forwards" } =
    bsx3::no_case[ "Max-Forwards" ] > HCOLON > bsx3::uint32;

}  // namespace Parsers
}  // namespace CppSip
