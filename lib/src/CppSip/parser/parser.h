#pragma once

#include "CppSip/message.h"

#include "boost/spirit/home/x3/string/symbols.hpp"

namespace CppSip { namespace Parsers {

  namespace bsx3 = boost::spirit::x3;

  extern const bsx3::symbols<Method> method;
} }