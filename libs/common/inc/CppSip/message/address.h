#pragma once

#include <optional>
#include <string>

namespace CppSip
{

using Host = std::string;
using Port = unsigned int;

struct HostPort
{
  Host host;
  std::optional<Port> port;
};

}  // namespace CppSip