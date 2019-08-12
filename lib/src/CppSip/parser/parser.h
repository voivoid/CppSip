#pragma once

#include <string>

#include "CppSip/message.h"

namespace CppSip
{
  Method parse_method( std::string_view method );
}