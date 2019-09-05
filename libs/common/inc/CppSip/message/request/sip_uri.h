#pragma once

#include "CppSip/message/address.h"
#include "CppSip/message/request/sip_uri_header.h"
#include "CppSip/message/request/userinfo.h"

#include <optional>

namespace CppSip
{

namespace Message
{

struct SipUri
{
  bool sips;

  std::optional<UserInfo> userinfo;
  HostPort host_port;
  SipUriHeaders headers;
};

}  // namespace Message

}  // namespace CppSip
