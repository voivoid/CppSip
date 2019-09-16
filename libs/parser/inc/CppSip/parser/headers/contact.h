#pragma once

#include "CppSip/message/headers/contact.h"

#include "CppSip/parser/common.h"

#include "boost/fusion/include/adapt_struct.hpp"

namespace CppSip
{
namespace Parsers
{

namespace bsx3 = boost::spirit::x3;

// c-p-q = "q" EQUAL qvalue

// delta-seconds = 1*DIGIT

// c-p-expires = "expires" EQUAL delta-seconds

// contact-extension = generic-param

// contact-params = c-p-q / c-p-expires / contact-extension

// contact-param = (name-addr / addr-spec) *(SEMI contact-params)

// Contact = ("Contact" / "m" ) HCOLON  ( STAR / (contact-param *(COMMA contact-param)))


}  // namespace Parsers
}  // namespace CppSip
