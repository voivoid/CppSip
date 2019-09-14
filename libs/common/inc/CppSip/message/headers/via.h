#pragma once

#include "CppSip/message/address.h"
#include "CppSip/message/headers/param.h"
#include "CppSip/message/token.h"

#include "boost/variant.hpp"

#include <string>

#include <cstdint>


namespace CppSip
{
namespace Message
{
namespace Headers
{

struct Protocol
{
  std::string name;
  std::string version;
  std::string transport;
};

struct Via
{
  struct TTL
  {
    std::uint8_t ttl;
  };

  struct MAddr
  {
    Host host;
  };

  struct Received
  {
    Address address;
  };

  struct Branch
  {
    Token branch;
  };

  struct Extension
  {
    GenericParam ext;
  };

  using Param = boost::variant<TTL, MAddr, Received, Branch, Extension>;
  std::vector<Param> params;
};

}  // namespace Headers
}  // namespace Message
}  // namespace CppSip
