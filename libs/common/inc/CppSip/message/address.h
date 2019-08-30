#pragma once

#include <optional>
#include <string>
#include <variant>

namespace CppSip
{

struct IPv4Address
{
  std::uint8_t a;
  std::uint8_t b;
  std::uint8_t c;
  std::uint8_t d;
};

using HostName = std::string;

using Host = std::variant<HostName, IPv4Address>;
using Port = std::uint16_t;

struct HostPort
{
  Host host;
  std::optional<Port> port;
};

bool operator==( const IPv4Address& ip1, const IPv4Address& ip2 );
bool operator<( const IPv4Address& ip1, const IPv4Address& ip2 );

}  // namespace CppSip
