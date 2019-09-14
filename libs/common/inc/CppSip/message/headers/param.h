#pragma once

#include <optional>
#include <string>

namespace CppSip
{
namespace Message
{
namespace Headers
{
struct GenericParam
{
  std::string param;
  std::optional<std::string> value;
};

}  // namespace Headers
}  // namespace Message
}  // namespace CppSip
