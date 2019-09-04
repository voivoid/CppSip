#pragma once

#include "CppSip/message/response/status_code.h"
#include "CppSip/message/response/status_line.h"

#include "CppSip/message/headers/headers.h"

namespace CppSip
{
namespace Message
{

struct Response
{
  StatusLine status_line;
  std::vector<Header> headers;
};

}  // namespace Message
}  // namespace CppSip
