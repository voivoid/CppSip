#pragma once

#include "CppSip/message/headers/addr.h"
#include "boost/variant.hpp"

#include <string>
#include <vector>


namespace CppSip
{
namespace Message
{
namespace Headers
{

struct From
{
  using Param  = std::string;
  using Params = std::vector<Param>;

  boost::variant<NameAddr, AddrSpec> addr;
  Params params;
};

struct To
{
  using Param  = std::string;
  using Params = std::vector<Param>;

  boost::variant<NameAddr, AddrSpec> addr;
  Params params;
};

}  // namespace Headers
}  // namespace Message
}  // namespace CppSip
