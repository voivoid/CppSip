#pragma once

#include "CppSip/message/headers/headers.h"
#include "CppSip/parser/common_parsers.h"

#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/spirit/home/x3.hpp"

BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::CallId, id )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::ContentLength, length )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::CSeq, id, method )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::MaxForwards, forwards )

namespace CppSip
{
namespace Parsers
{

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

// discrete-type = "text" / "image" / "audio" / "video" / "application" / extension-token (!!!)
inline const auto discrete_type =
    bsx3::string( "text" ) | bsx3::string( "image" ) | bsx3::string( "audio" ) | bsx3::string( "video" ) | bsx3::string( "application" );

/* message-header = (Accept / Accept-Encoding / Accept-Language / Alert-Info / Allow / Authentication-Info / Authorization / Call-ID /
 Call-Info / Contact / Content-Disposition / Content-Encoding / Content-Language / Content-Length / Content-Type / CSeq / Date / Error-Info
 / Expires / From / In-Reply-To / Max-Forwards / MIME-Version / Min-Expires / Organization / Priority / Proxy-Authenticate /
 Proxy-Authorization / Proxy-Require / Record-Route / Reply-To / Require / Retry-After / Route / Server / Subject /
 Supported / Timestamp / To / Unsupported / User-Agent / Via / Warning / WWW-Authenticate / extension-header) CRLF (!!!) */
inline const auto message_header = bsx3::rule<struct _msg_header, CppSip::Message::Header>{} =
    ( Call_ID | Content_Length | CSeq | Max_Forwards ) > CRLF;


}  // namespace Parsers
}  // namespace CppSip
