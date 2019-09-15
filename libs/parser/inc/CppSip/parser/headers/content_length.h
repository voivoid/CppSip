#pragma once

#include "CppSip/message/headers/content_length.h"

#include "CppSip/parser/common.h"

#include "boost/fusion/include/adapt_struct.hpp"

BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::ContentLength, length )

namespace CppSip
{
namespace Parsers
{

// Content-Length  =  ( "Content-Length" / "l" ) HCOLON 1*DIGIT
inline const auto Content_Length = bsx3::rule<struct _content_length, CppSip::Message::Headers::ContentLength>{ "Content-Length" } =
    ( bsx3::no_case[ ( bsx3::lit( "Content-Length" ) | 'l' ) ] >> HCOLON ) > bsx3::uint64;

}  // namespace Parsers
}  // namespace CppSip
