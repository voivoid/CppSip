#pragma once

#include <optional>
#include <string>

namespace CppSip
{

using Host = std::string;
using Port = std::uint16_t;

struct HostPort
{
  Host host;
  std::optional<Port> port;
};

struct IPv4Address
{
  std::uint8_t a;
  std::uint8_t b;
  std::uint8_t c;
  std::uint8_t d;


private:
};

bool operator==( const IPv4Address& ip1, const IPv4Address& ip2 );
bool operator<( const IPv4Address& ip1, const IPv4Address& ip2 );

}  // namespace CppSip
