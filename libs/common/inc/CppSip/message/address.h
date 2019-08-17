#pragma once

#include <string>
#include <optional>

namespace CppSip {

using Host = std::string;
using Port = unsigned int;

struct HostPort {
  Host host;
  std::optional<Port> port;
};

}