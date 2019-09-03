#pragma once

#include "CppSip/message/method.h"

#include <string>

namespace CppSip
{
namespace Message
{
namespace Headers
{
struct CSeq
{
  using Id = std::string;

  Id id;
  Method method;
};

}  // namespace Headers
}  // namespace Message
}  // namespace CppSip
