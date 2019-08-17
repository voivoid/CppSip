#pragma once

#include "boost/spirit/home/x3.hpp"

namespace CppSip {
namespace Parsers {

namespace bsx3 = boost::spirit::x3;

// ALPHA = %x41-5A / %x61-7A ; A-Z / a-z
inline const auto ALPHA = bsx3::char_('A', 'Z') | bsx3::char_('a', 'z');;

// DIGIT = %x30-39 ; 0-9
inline const auto DIGIT = bsx3::char_('0', '9');

} // namespace Parsers
} // namespace CppSip
