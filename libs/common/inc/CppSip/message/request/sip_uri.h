#pragma once

#include "CppSip/message/address.h"

namespace CppSip
{

namespace Message
{

struct SipUri
{
  bool sips;
  HostPort host_port;
};

}  // namespace Message

}  // namespace CppSip
