#pragma once

#include "CppSip/message/address.h"
#include "CppSip/message/method.h"
#include "CppSip/message/sip_version.h"

#include "CppSip/message/request/request_line.h"
#include "CppSip/message/request/request_uri.h"
#include "CppSip/message/request/sip_uri.h"
#include "CppSip/message/request/userinfo.h"

#include "CppSip/message/headers/headers.h"

#include <vector>

namespace CppSip
{

namespace Message
{

struct Request
{
  RequestLine request_line;
  std::vector<Header> headers;
};

}  // namespace Message
}  // namespace CppSip
