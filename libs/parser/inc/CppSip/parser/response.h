#pragma once

#include "CppSip/message/response/response.h"
#include "CppSip/parser/abnf_core.h"
#include "CppSip/parser/common.h"
#include "CppSip/parser/header.h"

#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/spirit/home/x3.hpp"

BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::StatusLine, sip_version, status_code, reason )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Response, status_line, headers )

namespace CppSip
{
namespace Parsers
{

namespace Details
{
inline bool is_valid_status_code( const std::uint16_t s )
{
  // clang-format off
    return s == 100 || s == 180 || s == 181 || s == 182 || s == 183 ||
           s == 200 ||
           s == 300 || s == 301 || s == 302 || s == 305 || s == 380 ||
           s == 400 || s == 401 || s == 402 || s == 403 || s == 404 || s == 405 || s == 406 || s == 407 || s == 408 ||
                       s == 410 || s == 413 || s == 414 || s == 415 || s == 416 ||
                       s == 420 || s == 421 || s == 423 ||
                       s == 480 || s == 481 || s == 482 || s == 483 || s == 484 || s == 485 || s == 486 || s == 487 || s == 488 ||
                       s == 491 || s == 493 ||
           s == 500 || s == 501 || s == 502 || s == 503 || s == 504 || s == 505 || s == 513 ||
           s == 600 || s == 603 || s == 604 || s == 606;
  // clang-format on
}
}  // namespace Details

namespace bsx3 = boost::spirit::x3;

// Reason-Phrase = *(reserved / unreserved / escaped / UTF8-NONASCII / UTF8-CONT / SP / HTAB) (!!!)
inline const auto Reason_Phrase = bsx3::rule<struct _reason_phrase, std::string>{} = *( reserved | unreserved | escaped | SP | HTAB );

// Status-Code = Informational / Redirection / Success / Client-Error / Server-Error / Global-Failure / extension-code (!!!)
inline const auto Status_Code =
    bsx3::uint_parser<std::uint16_t, 10, 3, 3>{}[ ( []( auto& ctx ) { _pass( ctx ) = Details::is_valid_status_code( _attr( ctx ) ); } ) ];

// Status-Line = SIP-Version SP Status-Code SP Reason-Phrase CRLF
inline const auto Status_Line = bsx3::rule<struct _status_line, CppSip::Message::StatusLine>{} %=
    SIP_Version > SP > Status_Code > SP > Reason_Phrase > CRLF;

// Response = Status-Line *( message-header ) CRLF [ message-body ] (!!!)
inline const auto Response = bsx3::rule<struct _response, CppSip::Message::Response>{} = Status_Line > *message_header > CRLF;

}  // namespace Parsers
}  // namespace CppSip
