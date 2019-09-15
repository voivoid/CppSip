#pragma once

#include "CppSip/message/headers/via.h"

#include "CppSip/parser/common.h"
#include "CppSip/parser/headers/common.h"

#include "boost/fusion/include/adapt_struct.hpp"

BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::Via::Protocol, name, version, transport )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::Via::TTL, ttl )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::Via::MAddr, host )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::Via::Received, address )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::Via::Branch, branch )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::Via::Extension, ext )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::Via::Param, protocol, by, params )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::Via, vias )

namespace CppSip
{
namespace Parsers
{

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

// Via = ( "Via" / "v" ) HCOLON via-parm *(COMMA via-parm)
inline const auto Via = bsx3::rule<struct _via, CppSip::Message::Headers::Via>{ "Via" } =
    ( bsx3::no_case[ bsx3::lit( "Via" ) | 'v' ] >> HCOLON ) > via_param % COMMA;

}  // namespace Parsers
}  // namespace CppSip
