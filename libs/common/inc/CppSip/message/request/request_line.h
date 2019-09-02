#pragma once

#include "CppSip/message/request/method.h"
#include "CppSip/message/request/request_uri.h"
#include "CppSip/message/request/sip_version.h"

namespace CppSip
{

namespace Message
{

struct RequestLine
{
  Method method;
  RequestUri request_uri;
  SipVersion sip_version;
};

}  // namespace Message

}  // namespace CppSip
