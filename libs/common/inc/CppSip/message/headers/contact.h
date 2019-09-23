#pragma once

#include "CppSip/message/headers/addr.h"
#include "CppSip/message/headers/param.h"

#include "boost/variant.hpp"

#include <cstdint>
#include <vector>

namespace CppSip
{
namespace Message
{
namespace Headers
{

struct Contact
{
  struct Q
  {
    std::string value;
  };

  struct Expires
  {
    std::uint32_t value;
  };

  struct Extension
  {
    GenericParam ext;
  };

  struct Param
  {
    boost::variant<NameAddr, AddrSpec> addr;

    using Value = boost::variant<Q, Expires, Extension>;
    std::vector<Value> values;
  };

  std::vector<Param> contacts;
};

}  // namespace Headers
}  // namespace Message
}  // namespace CppSip
