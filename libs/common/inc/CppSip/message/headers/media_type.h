#pragma once

#include <string>
#include <vector>

namespace CppSip
{
namespace Message
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

}  // namespace Message
}  // namespace CppSip
