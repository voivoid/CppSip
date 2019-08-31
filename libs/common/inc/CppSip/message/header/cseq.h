#pragma once

#include "CppSip/message/method.h"

#include <string>

namespace CppSip
{
namespace Message
{
namespace Header
{
struct CSeq
{
  using Id = std::string;

  Id id;
  Method method;
};

}  // namespace Header
}  // namespace Message
}  // namespace CppSip