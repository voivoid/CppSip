#pragma once

#include "CppSip/message/sip_uri.h"

namespace CppSip
{
namespace Message
{
namespace Headers
{

struct AddrSpec
{
  SipUri sip_uri;
};

struct NameAddr
{
  std::string display_name;
  AddrSpec addr_spec;
};

}  // namespace Headers
}  // namespace Message
}  // namespace CppSip
