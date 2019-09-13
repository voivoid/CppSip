#pragma once

#include "CppSip/message/headers/addr.h"
#include "CppSip/message/headers/param.h"
#include "boost/variant.hpp"

#include <string>
#include <vector>


namespace CppSip
{
namespace Message
{
namespace Headers
{

struct FromTo
{
  using Param  = GenericParam;
  using Params = std::vector<Param>;

  boost::variant<NameAddr, AddrSpec> addr;
  Params params;
};

struct From : FromTo
{
};

struct To : FromTo
{
};

}  // namespace Headers
}  // namespace Message
}  // namespace CppSip
