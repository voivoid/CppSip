#pragma once

#include "CppSip/message/method.h"
#include "CppSip/message/sip_version.h"

#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/spirit/home/x3.hpp"

#include <stdexcept>

BOOST_FUSION_ADAPT_STRUCT(CppSip::SipVersion, major, minor)

namespace CppSip {
namespace Parsers {

namespace bsx3 = boost::spirit::x3;

// ABNF rules

// ALPHA = %x41-5A / %x61-7A ; A-Z / a-z
auto get_ALPHA_parser() {
  return bsx3::char_('A', 'Z') | bsx3::char_('a', 'z');
}
inline const auto ALPHA = get_ALPHA_parser();

// DIGIT = %x30-39 ; 0-9
auto get_DIGIT_parser() { return bsx3::char_('0', '9'); }
inline const auto DIGIT = get_DIGIT_parser();

// SIP rules

// alphanum = ALPHA / DIGIT
auto get_alphanum_parser() { return ALPHA | DIGIT; }
inline const auto alphanum = get_alphanum_parser();

// domainlabel = alphanum / alphanum *( alphanum / "-" ) alphanum
auto get_domainlabel_parser() {
  return alphanum >> *(alphanum | ( '-' >> alphanum ) );
}
inline const auto domainlabel = get_domainlabel_parser();

// toplabel = ALPHA / ALPHA *( alphanum / "-" ) alphanum
auto get_toplabel_parser() {
  return ALPHA >> *(alphanum | ( '-' >> alphanum ) );
}
inline const auto toplabel = get_toplabel_parser();

// hostname = *( domainlabel "." ) toplabel [ "." ] (!!!)
auto get_hostname_parser() {}

// host = hostname / IPv4address / IPv6reference (!!!)
auto get_host_parser() { return get_hostname_parser(); }

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
