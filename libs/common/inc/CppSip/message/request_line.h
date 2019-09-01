#pragma once

#include "CppSip/message/method.h"
#include "CppSip/message/request_uri.h"
#include "CppSip/message/sip_version.h"

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

}

}

