#pragma once

#include "CppSip/message/headers/headers.h"
#include "CppSip/parser/common_parsers.h"

#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/spirit/home/x3.hpp"

BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::MediaType, type, subtype, parameters )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::MediaType::Parameter, attribute, value )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::CallId, id )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::ContentLength, length )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::ContentType, media_type )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::CSeq, id, method )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::MaxForwards, forwards )

namespace CppSip
{
namespace Parsers
{

// ietf-token = token
inline const auto ietf_token = token;

// iana-token = token
inline const auto iana_token = token;

// m-attribute = token
inline const auto m_attribute = token;

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

// m-parameter = m-attribute EQUAL m-value
inline const auto m_parameter = bsx3::rule<struct _m_parameter, CppSip::Message::MediaType::Parameter>{} = m_attribute > EQUAL > m_value;

// media-type = m-type SLASH m-subtype *(SEMI m-parameter)
inline const auto media_type = bsx3::rule<struct _media_type, CppSip::Message::MediaType>{} = m_type > SLASH > m_subtype >>
                                                                                              *( SEMI > m_parameter );

// display-name = *(token LWS)/ quoted-string
inline const auto display_name = ( *( token > LWS ) ) | quoted_string;

// addr-spec = SIP-URI / SIPS-URI / absoluteURI (!!!)
inline const auto addr_spec = SIP_URI | SIPS_URI;

// Call-ID = ( "Call-ID" / "i" ) HCOLON callid
inline const auto Call_ID = bsx3::rule<struct _callid, CppSip::Message::Headers::CallId>{} =
    ( bsx3::lit( "Call-ID" ) | 'i' ) > HCOLON > callid;

// CSeq  =  "CSeq" HCOLON 1*DIGIT LWS Method
inline const auto CSeq = bsx3::rule<struct _cseq, CppSip::Message::Headers::CSeq>{} = bsx3::lit( "CSeq" ) > HCOLON > +DIGIT > LWS > Method;

// Max-Forwards = "Max-Forwards" HCOLON 1*DIGIT
inline const auto Max_Forwards = bsx3::rule<struct _max_forwards, CppSip::Message::Headers::MaxForwards>{} =
    bsx3::lit( "Max-Forwards" ) > HCOLON > bsx3::uint32;

// Content-Length  =  ( "Content-Length" / "l" ) HCOLON 1*DIGIT
inline const auto Content_Length = bsx3::rule<struct _content_length, CppSip::Message::Headers::ContentLength>{} =
    ( bsx3::lit( "Content-Length" ) | 'i' ) > HCOLON > bsx3::uint64;

// Content-Type =  ( "Content-Type" / "c" ) HCOLON media-type
inline const auto Content_Type = bsx3::rule<struct _content_type, CppSip::Message::Headers::ContentType>{} =
    ( bsx3::lit( "Content-Type" ) | 'c' ) > HCOLON > media_type;

// name-addr = [ display-name ] LAQUOT addr-spec RAQUOT

// gen-value = token / host / quoted-string

// generic-param = token [ EQUAL gen-value ]

// tag-param = "tag" EQUAL token

// from-param = tag-param / generic-param

// from-spec = ( name-addr / addr-spec ) *( SEMI from-param )

// From = ( "From" / "f" ) HCOLON from-spec

// to-param = tag-param / generic-param

// To = ( "To" / "t" ) HCOLON ( name-addr / addr-spec ) *( SEMI to-param )

/* message-header = (Accept / Accept-Encoding / Accept-Language / Alert-Info / Allow / Authentication-Info / Authorization / Call-ID /
 Call-Info / Contact / Content-Disposition / Content-Encoding / Content-Language / Content-Length / Content-Type / CSeq / Date / Error-Info
 / Expires / From / In-Reply-To / Max-Forwards / MIME-Version / Min-Expires / Organization / Priority / Proxy-Authenticate /
 Proxy-Authorization / Proxy-Require / Record-Route / Reply-To / Require / Retry-After / Route / Server / Subject /
 Supported / Timestamp / To / Unsupported / User-Agent / Via / Warning / WWW-Authenticate / extension-header) CRLF (!!!) */
inline const auto message_header = bsx3::rule<struct _msg_header, CppSip::Message::Header>{} =
    ( Call_ID | Content_Length | Content_Type | CSeq | Max_Forwards ) > CRLF;


}  // namespace Parsers
}  // namespace CppSip
