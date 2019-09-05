#pragma once

#include <string>
#include <vector>

namespace CppSip
{

namespace Message
{

struct SipUriHeader
{
  using Value = std::string;
  using Name  = std::string;

  Name name;
  Value value;
};

using SipUriHeaders = std::vector<SipUriHeader>;

}  // namespace Message

}  // namespace CppSip
