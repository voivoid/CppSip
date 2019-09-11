#pragma once

#include <string>
#include <vector>

namespace CppSip
{
namespace Message
{
namespace Headers
{

struct MediaType
{
  struct Parameter
  {
    std::string attribute;
    std::string value;
  };

  std::string type;
  std::string subtype;
  std::vector<Parameter> parameters;
};

}  // namespace Headers
}  // namespace Message
}  // namespace CppSip
