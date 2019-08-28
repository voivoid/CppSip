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

struct IPaddress
{
  std::uint8_t a;
  std::uint8_t b;
  std::uint8_t c;
  std::uint8_t d;


private:
};

bool operator==( const IPaddress& ip1, const IPaddress& ip2 );
bool operator<( const IPaddress& ip1, const IPaddress& ip2 );

}  // namespace CppSip
