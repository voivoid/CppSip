#pragma once

#include "CppSip/message/headers/headers.h"
#include "CppSip/parser/common_parsers.h"

#include "boost/algorithm/string/trim.hpp"
#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/spirit/home/x3.hpp"

BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::MediaType, type, subtype, parameters )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::MediaType::Parameter, attribute, value )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::AddrSpec, sip_uri )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::NameAddr, display_name, addr_spec )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::GenericParam, param, value )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::FromTo, addr, params )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::Via::Protocol, name, version, transport )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::Via::TTL, ttl )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::Via::MAddr, host )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::Via::Received, address )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::Via::Branch, branch )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::Via::Extension, ext )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::Via::Param, protocol, by, params )

BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::CallId, id )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::ContentLength, length )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::ContentType, media_type )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::CSeq, id, method )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::From, addr, params )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::MaxForwards, forwards )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::To, addr, params )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::Via, vias )


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

// protocol-name = "SIP" / token
inline const auto protocol_name = token;

// protocol-version = token
inline const auto protocol_version = token;

// other-transport = token
inline const auto other_transport = token;

// transport = "UDP" / "TCP" / "TLS" / "SCTP" / other-transport
inline const auto transport = token | other_transport;

// sent-protocol = protocol-name SLASH protocol-version SLASH transport
inline const auto sent_protocol = bsx3::rule<struct _sent_protocol, CppSip::Message::Headers::Via::Protocol>{ "sent-protocol" } =
    protocol_name > SLASH > protocol_version > SLASH > transport;

// sent-by = host [ COLON port ]
inline const auto sent_by = bsx3::rule<struct _sent_by, CppSip::Message::HostPort>{ "sent-by" } = host >> -( COLON > port );

// ttl = 1*3DIGIT ; 0 to 255
inline const auto ttl = bsx3::uint8;

// via-extension = generic-param
inline const auto via_extension = bsx3::rule<struct _via_extension, CppSip::Message::Headers::Via::Extension>{ "via-extension" } =
    generic_param;

// via-branch = "branch" EQUAL token
inline const auto via_branch = bsx3::rule<struct _via_branch, CppSip::Message::Headers::Via::Branch>{ "via-branch" } =
    bsx3::no_case[ "branch" ] > EQUAL > token;

// via-received = "received" EQUAL (IPv4address / IPv6address)
inline const auto via_received = bsx3::rule<struct _via_branch, CppSip::Message::Headers::Via::Received>{ "via-received" } =
    bsx3::no_case[ "received" ] > EQUAL > IPv4address;  // IPv6address (!!!)

// via-maddr = "maddr" EQUAL host
inline const auto via_maddr = bsx3::rule<struct _via_branch, CppSip::Message::Headers::Via::MAddr>{ "via-maddr" } =
    bsx3::no_case[ "maddr" ] > EQUAL > host;

// via-ttl = "ttl" EQUAL ttl
inline const auto via_ttl = bsx3::rule<struct _via_branch, CppSip::Message::Headers::Via::TTL>{ "via-ttl" } =
    bsx3::no_case[ "ttl" ] > EQUAL > ttl;

// via-params = via-ttl / via-maddr / via-received / via-branch / via-extension
inline const auto via_params = bsx3::rule<struct _via_branch, CppSip::Message::Headers::Via::Param::Type>{ "via-param" } =
    via_ttl | via_maddr | via_received | via_branch | via_extension;

// via-parm = sent-protocol LWS sent-by *( SEMI via-params )
inline const auto via_param = bsx3::rule<struct _via_param, CppSip::Message::Headers::Via::Param>{ "via-parm" } = sent_protocol > LWS >
                                                                                                                  sent_by >
                                                                                                                  *( SEMI > via_params );



// Call-ID = ( "Call-ID" / "i" ) HCOLON callid
inline const auto Call_ID = bsx3::rule<struct _callid, CppSip::Message::Headers::CallId>{ "Call-ID" } =
    ( bsx3::no_case[ ( bsx3::lit( "Call-ID" ) | 'i' ) ] >> HCOLON ) > callid;

// Content-Length  =  ( "Content-Length" / "l" ) HCOLON 1*DIGIT
inline const auto Content_Length = bsx3::rule<struct _content_length, CppSip::Message::Headers::ContentLength>{ "Content-Length" } =
    ( bsx3::no_case[ ( bsx3::lit( "Content-Length" ) | 'l' ) ] >> HCOLON ) > bsx3::uint64;

// Content-Type =  ( "Content-Type" / "c" ) HCOLON media-type
inline const auto Content_Type = bsx3::rule<struct _content_type, CppSip::Message::Headers::ContentType>{ "Content-Type" } =
    ( bsx3::no_case[ ( bsx3::lit( "Content-Type" ) | 'c' ) ] >> HCOLON ) > media_type;

// CSeq  =  "CSeq" HCOLON 1*DIGIT LWS Method
inline const auto CSeq = bsx3::rule<struct _cseq, CppSip::Message::Headers::CSeq>{ "CSeq" } =
    bsx3::no_case[ "CSeq" ] > HCOLON > +DIGIT > LWS > Method;

// From = ( "From" / "f" ) HCOLON from-to-spec
inline const auto From = bsx3::rule<struct _from, CppSip::Message::Headers::From>{ "From" } =
    ( bsx3::no_case[ bsx3::lit( "From" ) | 'f' ] >> HCOLON ) > from_to_spec;

// Max-Forwards = "Max-Forwards" HCOLON 1*DIGIT
inline const auto Max_Forwards = bsx3::rule<struct _max_forwards, CppSip::Message::Headers::MaxForwards>{ "Max-Forwards" } =
    bsx3::no_case[ "Max-Forwards" ] > HCOLON > bsx3::uint32;

// To = ( "To" / "t" ) HCOLON from-to-spec
inline const auto To = bsx3::rule<struct _from, CppSip::Message::Headers::To>{ "To" } =
    ( bsx3::no_case[ bsx3::lit( "To" ) | 't' ] >> HCOLON ) > from_to_spec;

// Via = ( "Via" / "v" ) HCOLON via-parm *(COMMA via-parm)
inline const auto Via = bsx3::rule<struct _via, CppSip::Message::Headers::Via>{ "Via" } =
    ( bsx3::no_case[ bsx3::lit( "Via" ) | 'v' ] >> HCOLON ) > via_param % COMMA;

/* message-header = (Accept / Accept-Encoding / Accept-Language / Alert-Info / Allow / Authentication-Info / Authorization / Call-ID /
 Call-Info / Contact / Content-Disposition / Content-Encoding / Content-Language / Content-Length / Content-Type / CSeq / Date / Error-Info
 / Expires / From / In-Reply-To / Max-Forwards / MIME-Version / Min-Expires / Organization / Priority / Proxy-Authenticate /
 Proxy-Authorization / Proxy-Require / Record-Route / Reply-To / Require / Retry-After / Route / Server / Subject /
 Supported / Timestamp / To / Unsupported / User-Agent / Via / Warning / WWW-Authenticate / extension-header) CRLF (!!!) */
inline const auto message_header = bsx3::rule<struct _msg_header, CppSip::Message::Header>{} =
    ( Call_ID | Content_Length | Content_Type | CSeq | From | Max_Forwards | To | Via ) > CRLF;


}  // namespace Parsers
}  // namespace CppSip
