#pragma once

#include <string>

namespace CppSip
{
  namespace Message
  {
    namespace Headers
    {
      struct GenericParam
      {
        std::string param;
        std::optional<std::string> value;
      };

      struct Tag
      {
        std::string value;
      };

    }
  }
}