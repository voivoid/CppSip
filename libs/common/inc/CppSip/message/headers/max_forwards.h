#pragma once

#include <cstdint>

namespace CppSip
{
namespace Message
{
namespace Headers
{
struct MaxForwards
{
  std::uint32_t forwards;
};
}  // namespace Headers
}  // namespace Message
}  // namespace CppSip