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

struct Via
{
  struct Protocol
  {
    std::string name;
    std::string version;
    std::string transport;
  };

  struct TTL
  {
    std::uint8_t value;
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

  struct Param
  {
    Protocol protocol;
    HostPort by;

    using Value = boost::variant<TTL, MAddr, Received, Branch, Extension>;
    std::vector<Value> values;
  };

  std::vector<Param> vias;
};

}  // namespace Headers
}  // namespace Message
}  // namespace CppSip
