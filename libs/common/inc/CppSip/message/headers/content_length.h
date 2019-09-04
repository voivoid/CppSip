#pragma once

#include <cstdint>

namespace CppSip
{
  namespace Message
  {
    namespace Headers
    {
      struct ContentLength
      {
        std::uint64_t length;
      };
    }
  }
}