#pragma once

#include "CppSip/message/method.h"
#include "CppSip/message/sip_version.h"

#include "boost/spirit/home/x3.hpp"
#include "boost/fusion/include/adapt_struct.hpp"

#include <stdexcept>

BOOST_FUSION_ADAPT_STRUCT(CppSip::SipVersion, major, minor)

namespace CppSip {
namespace Parsers {

namespace bsx3 = boost::spirit::x3;

namespace Details {
bsx3::symbols<Method> get_method_parser() {

  bsx3::symbols<Method> method_symbols;
  method_symbols.add("ACK", Method::Ack)("BYE", Method::Bye)(
      "CANCEL", Method::Cancel)("INVITE", Method::Invite)(
      "OPTIONS", Method::Options)("REGISTER", Method::Register);

  return method_symbols;
}

auto get_sip_version_parser() {
  auto parser =
      bsx3::lit("SIP/") >> bsx3::ulong_ >> bsx3::lit('.') >> bsx3::ulong_;
  return parser;
}
} // namespace Details

inline const auto method = Details::get_method_parser();
inline const auto sip_version = Details::get_sip_version_parser();

} // namespace Parsers
} // namespace CppSip
