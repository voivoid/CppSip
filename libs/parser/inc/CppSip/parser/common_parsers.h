#pragma once

#include "CppSip/parser/abnf_core_parsers.h"

#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/spirit/home/x3.hpp"

#include "CppSip/message/method.h"
#include "CppSip/message/sip_version.h"

BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::SipVersion, major, minor )

namespace CppSip
{
namespace Parsers
{

namespace bsx3 = boost::spirit::x3;

// alphanum = ALPHA / DIGIT
inline const auto alphanum = ALPHA | DIGIT;

// LWS  =  [*WSP CRLF] 1*WSP ; linear whitespace
inline const auto LWS = -( *WSP >> CRLF ) >> +WSP;

// SWS  =  [LWS] ; sep whitespace
inline const auto SWS = -LWS;

// HCOLON = *( SP / HTAB ) ":" SWS
inline const auto HCOLON = *( SP | HTAB ) >> ':' >> SWS;

// mark = "-" / "_" / "." / "!" / "~" / "*" / "'" / "(" / ")"
inline const auto mark = bsx3::char_( "-_.!~*'()" );

// unreserved = alphanum / mark
inline const auto unreserved = alphanum | mark;

// reserved = ";" / "/" / "?" / ":" / "@" / "&" / "=" / "+" / "$" / ","
inline const auto reserved = bsx3::char_( ";/?:@&=+$," );

// escaped = "%" HEXDIG HEXDIG
inline const auto escaped = bsx3::lit( '%' ) > HEXDIG > HEXDIG;

// Method = INVITEm / ACKm / OPTIONSm / BYEm / CANCELm / REGISTERm /
// extension-method (!!!)
inline bsx3::symbols<CppSip::Message::Method> get_Method_parser()
{
  bsx3::symbols<CppSip::Message::Method> method_symbols;
  method_symbols.add( "ACK", Message::Method::Ack )( "BYE", Message::Method::Bye )( "CANCEL", Message::Method::Cancel )(
      "INVITE", Message::Method::Invite )( "OPTIONS", Message::Method::Options )( "REGISTER", Message::Method::Register );

  return method_symbols;
}
inline const auto Method = get_Method_parser();

// SIP-Version = "SIP" "/" 1*DIGIT "." 1*DIGIT
inline const auto SIP_Version = bsx3::rule<struct _sip_version, CppSip::Message::SipVersion>{} = bsx3::lit( "SIP/" ) >> +bsx3::digit >>
                                                                                                 bsx3::lit( '.' ) >> +bsx3::digit;

// word = 1*( alphanum / "-" / "." / "!" / "%" / "*" / "_" / "+" / "`" / "'" / "~" / "(" / ")" / "<" / ">" / ":" / "\" / DQUOTE / "/" / "["
// / "]" / "?" / "{" / "}" )
inline const auto word = +( alphanum | bsx3::char_( "-.!%*_+`'~()<>:\\\"/[]?{}" ) );

// callid = word[ "@" word ]
inline const auto callid = bsx3::rule<struct _callid, std::string>{} = word >> -( bsx3::char_( '@' ) > word );

}  // namespace Parsers
}  // namespace CppSip
