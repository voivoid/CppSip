#pragma once

#include "CppSip/message/response/status_code.h"
#include "CppSip/message/sip_version.h"

namespace CppSip
{
namespace Message
{

struct StatusLine
{
  SipVersion sip_version;
  StatusCode status_code;
  std::string reason;
};

}  // namespace Message
}  // namespace CppSip
