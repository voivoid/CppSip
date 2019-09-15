#pragma once

#include "CppSip/parser/common.h"
#include "CppSip/parser/headers/common.h"

#include "boost/fusion/include/adapt_struct.hpp"

BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::FromTo, addr, params )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::From, addr, params )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::To, addr, params )

namespace CppSip
{
namespace Parsers
{

// tag-param = "tag" EQUAL token
inline const auto tag_param = bsx3::rule<struct _tag_param, CppSip::Message::Headers::GenericParam>{ "tag-param" } =
    bsx3::no_case[ bsx3::string( "tag" ) ] > EQUAL > token;

// from-to-param = tag-param / generic-param
inline const auto from_to_param = bsx3::rule<struct _from_to_param, CppSip::Message::Headers::FromTo::Param>{ "from-to-param" } =
    tag_param | generic_param;

// from-to-spec = ( name-addr / addr-spec ) *( SEMI from-to-param )
inline const auto from_to_spec = bsx3::rule<struct _from_to_spec, CppSip::Message::Headers::FromTo>{
  "from-to-spec"
} = ( name_addr | addr_spec ) > *( SEMI > from_to_param );

// From = ( "From" / "f" ) HCOLON from-to-spec
inline const auto From = bsx3::rule<struct _from, CppSip::Message::Headers::From>{ "From" } =
    ( bsx3::no_case[ bsx3::lit( "From" ) | 'f' ] >> HCOLON ) > from_to_spec;

// To = ( "To" / "t" ) HCOLON from-to-spec
inline const auto To = bsx3::rule<struct _from, CppSip::Message::Headers::To>{ "To" } =
    ( bsx3::no_case[ bsx3::lit( "To" ) | 't' ] >> HCOLON ) > from_to_spec;

}  // namespace Parsers
}  // namespace CppSip
