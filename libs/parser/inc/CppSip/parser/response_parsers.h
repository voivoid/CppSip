#pragma once

#include "CppSip/message/response/response.h"
#include "CppSip/parser/abnf_core_parsers.h"
#include "CppSip/parser/common_parsers.h"
#include "CppSip/parser/header_parsers.h"

#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/spirit/home/x3.hpp"

namespace CppSip
{
namespace Parsers
{

namespace bsx3 = boost::spirit::x3;

// Reason-Phrase = *(reserved / unreserved / escaped / UTF8-NONASCII / UTF8-CONT / SP / HTAB)

// extension-code = 3DIGIT

// Informational =   "100" ; Trying
//                 / "180" ; Ringing
//                 / "181" ; Call Is Being Forwarded
//                 / "182" ; Queued
//                 / "183" ; Session Progress

// Success = "200" ; OK

// Status-Code = Informational / Redirection / Success / Client-Error / Server-Error / Global-Failure / extension-code

// Status-Line = SIP-Version SP Status-Code SP Reason-Phrase CRLF

// Response = Status-Line *( message-header ) CRLF [ message-body ]

}  // namespace Parsers
}  // namespace CppSip
