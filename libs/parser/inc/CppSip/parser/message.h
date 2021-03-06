#pragma once

#include "CppSip/message/message.h"
#include "CppSip/parser/request.h"
#include "CppSip/parser/response.h"

#include "boost/spirit/home/x3.hpp"

namespace CppSip
{
namespace Parsers
{

// SIP-message = Request / Response
inline const auto SIP_message = bsx3::rule<struct _sip_message, CppSip::Message::Message>{} = Request | Response;

}  // namespace Parsers
}  // namespace CppSip
