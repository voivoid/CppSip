#pragma once

#include "CppSip/message/method.h"
#include "CppSip/message/sip_version.h"
#include "CppSip/parser/abnf_core_parsers.h"

#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/spirit/home/x3.hpp"

#include <stdexcept>

BOOST_FUSION_ADAPT_STRUCT(CppSip::SipVersion, major, minor)

namespace CppSip {
namespace Parsers {

namespace bsx3 = boost::spirit::x3;

// alphanum = ALPHA / DIGIT
inline const auto alphanum = ALPHA | DIGIT;

// domainlabel = alphanum / alphanum *( alphanum / "-" ) alphanum
inline const auto domainlabel = alphanum >> *(alphanum | ('-' >> alphanum));

// toplabel = ALPHA / ALPHA *( alphanum / "-" ) alphanum
inline const auto toplabel = ALPHA >> *(alphanum | ('-' >> alphanum));

// hostname = *( domainlabel "." ) toplabel [ "." ] (!!!)
inline const auto hostname = *(domainlabel >> bsx3::char_('.')) > toplabel;

// host = hostname / IPv4address / IPv6reference (!!!)
auto get_host_parser() { return hostname; }

// hostport = host [ ":" port ] (!!!)
auto get_hostport_parser() { return get_host_parser(); }

// SIP-URI = "sip:" [ userinfo ] hostport uri-parameters [ headers ] (!!!)
auto get_SIP_URI_parser() { return bsx3::lit("sip:"); }
inline const auto SIP_URI = get_SIP_URI_parser();

// SIPS-URI = "sips:" [ userinfo ] hostport uri-parameters [ headers ] (!!!)
auto get_SIPS_URI_parser() { return bsx3::lit("sips:"); }
inline const auto SIPS_URI = get_SIPS_URI_parser();

// Request-URI = SIP-URI / SIPS-URI / absoluteURI (!!!)
auto get_Request_URI_parser() {
  return get_SIP_URI_parser() | get_SIPS_URI_parser();
}
inline const auto Request_URI = get_Request_URI_parser();

// SIP-Version = "SIP" "/" 1*DIGIT "." 1*DIGIT
auto get_SIP_Version_parser() {
  return bsx3::lit("SIP/") >> bsx3::ulong_ >> bsx3::lit('.') >> bsx3::ulong_;
}
inline const auto SIP_Version = get_SIP_Version_parser();

// Method = INVITEm / ACKm / OPTIONSm / BYEm / CANCELm / REGISTERm /
// extension-method (!!!)
bsx3::symbols<Method> get_Method_parser() {
  bsx3::symbols<Method> method_symbols;
  method_symbols.add("ACK", Method::Ack)("BYE", Method::Bye)(
      "CANCEL", Method::Cancel)("INVITE", Method::Invite)(
      "OPTIONS", Method::Options)("REGISTER", Method::Register);

  return method_symbols;
}
inline const auto Method = get_Method_parser();

} // namespace Parsers
} // namespace CppSip
