#pragma once

#include "CppSip/message/headers/from_to.h"
#include "CppSip/parser/common.h"

#include "boost/algorithm/string/trim.hpp"
#include "boost/fusion/include/adapt_struct.hpp"

BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::AddrSpec, sip_uri )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::NameAddr, display_name, addr_spec )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::GenericParam, param, value )

namespace CppSip
{
namespace Parsers
{

// display-name = *(token LWS)/ quoted-string
inline const auto display_name_raw = bsx3::rule<struct _display_name_raw, std::string>{ "display-name-raw" } =
    quoted_string | bsx3::raw[ *( token >> LWS ) ];
inline const auto display_name = bsx3::rule<struct _display_name, std::string>{ "display-name" } = display_name_raw[ ( []( auto& ctx ) {
  boost::trim_right( _attr( ctx ) );
  _val( ctx ) = _attr( ctx );
} ) ];

// addr-spec = SIP-URI / SIPS-URI / absoluteURI (!!!)
inline const auto addr_spec = bsx3::rule<struct _addr_spec, CppSip::Message::Headers::AddrSpec>{ "addr-spec" } = SIP_URI | SIPS_URI;

// name-addr = [ display-name ] LAQUOT addr-spec RAQUOT
inline const auto name_addr = bsx3::rule<struct _name_addr, CppSip::Message::Headers::NameAddr>{ "name-addr" } =
    ( -display_name >> LAQUOT ) > addr_spec > RAQUOT;

// gen-value = token / host / quoted-string
inline const auto gen_value = bsx3::rule<struct _gen_value, std::string>{ "gen-value" } = token | bsx3::raw[ host ] | quoted_string;

// generic-param = token [ EQUAL gen-value ]
inline const auto generic_param = bsx3::rule<struct _generic_param, CppSip::Message::Headers::GenericParam>{
  "generic-param"
} = token > -( EQUAL > gen_value );

}  // namespace Parsers
}  // namespace CppSip
