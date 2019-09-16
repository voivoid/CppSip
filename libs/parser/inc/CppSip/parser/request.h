#pragma once

#include "CppSip/message/request/request.h"

#include "CppSip/parser/abnf_core.h"
#include "CppSip/parser/common.h"
#include "CppSip/parser/header.h"

#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/spirit/home/x3.hpp"

BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::RequestLine, method, request_uri, sip_version )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::RequestUri, sip_uri )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Request, request_line, headers )

namespace CppSip
{
namespace Parsers
{

namespace bsx3 = boost::spirit::x3;

// Request-URI = SIP-URI / SIPS-URI / absoluteURI (!!!)
inline const auto Request_URI = bsx3::rule<struct _request_uri, CppSip::Message::RequestUri>{ "Request_URI" } = SIP_URI | SIPS_URI;

// Request-Line = Method SP Request-URI SP SIP-Version CRLF
inline const auto Request_Line = bsx3::rule<struct _request_line, CppSip::Message::RequestLine>{ "Request_Line" } =
    Method > SP > Request_URI > SP > SIP_Version > CRLF;

// Request = Request-Line *(message-header) CRLF [message-body] (!!!)
inline const auto Request = Request_Line > *( message_header ) > CRLF;

}  // namespace Parsers
}  // namespace CppSip
