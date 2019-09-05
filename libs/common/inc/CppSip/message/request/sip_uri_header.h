#pragma once

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

}  // namespace Message

}  // namespace CppSip