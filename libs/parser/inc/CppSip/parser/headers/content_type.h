#pragma once

#include "CppSip/message/headers/content_type.h"

#include "CppSip/parser/common.h"

#include "boost/fusion/include/adapt_struct.hpp"

BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::MediaType, type, subtype, parameters )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::MediaType::Parameter, attribute, value )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::ContentType, media_type )

namespace CppSip
{
namespace Parsers
{

// ietf-token = token
inline const auto ietf_token = token;

// iana-token = token
inline const auto iana_token = token;

// x-token = "x-" token
inline const auto x_token = bsx3::no_case[ bsx3::string( "x-" ) ] > token;

// extension-token = ietf-token / x-token
inline const auto extension_token = ietf_token | x_token;

// m-subtype = extension-token / iana-token
inline const auto m_subtype = extension_token | iana_token;

// discrete-type = "text" / "image" / "audio" / "video" / "application" / extension-token
inline const auto discrete_type = bsx3::string( "text" ) | bsx3::string( "image" ) | bsx3::string( "audio" ) | bsx3::string( "video" ) |
                                  bsx3::string( "application" ) | extension_token;

// composite-type = "message" / "multipart" / extension-token
inline const auto composite_type = bsx3::string( "message" ) | bsx3::string( "multipart" ) | extension_token;

// m-type = discrete-type / composite-type
inline const auto m_type = discrete_type | composite_type;

// m-value = token / quoted-string
inline const auto m_value = token | quoted_string;

// m-attribute = token
inline const auto m_attribute = token;

// m-parameter = m-attribute EQUAL m-value
inline const auto m_parameter = bsx3::rule<struct _m_parameter, CppSip::Message::Headers::MediaType::Parameter>{ "m-parameter" } =
    m_attribute > EQUAL > m_value;

// media-type = m-type SLASH m-subtype *(SEMI m-parameter)
inline const auto media_type = bsx3::rule<struct _media_type, CppSip::Message::Headers::MediaType>{
  "media-type"
} = m_type > SLASH > m_subtype >> *( SEMI > m_parameter );

// Content-Type =  ( "Content-Type" / "c" ) HCOLON media-type
inline const auto Content_Type = bsx3::rule<struct _content_type, CppSip::Message::Headers::ContentType>{ "Content-Type" } =
    ( bsx3::no_case[ ( bsx3::lit( "Content-Type" ) | 'c' ) ] >> HCOLON ) > media_type;

}  // namespace Parsers
}  // namespace CppSip
