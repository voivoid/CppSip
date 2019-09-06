#pragma once

#include "CppSip/parser/abnf_core_parsers.h"

#include "boost/fusion/container/vector.hpp"
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

// SLASH = SWS "/" SWS; slash
inline const auto SLASH = SWS >> '/' > SWS;

// SEMI = SWS ";" SWS; semicolon
inline const auto SEMI = SWS >> ';' > SWS;

// EQUAL = SWS "=" SWS; equal
inline const auto EQUAL = SWS >> '=' > SWS;

// RAQUOT  =  ">" SWS ; right angle quote
inline const auto RAQUOT = '>' > SWS;

// LAQUOT  =  SWS "<"; left angle quote
inline const auto LAQUOT = SWS > '<';

// quoted-pair = "\" (%x00-09 / %x0B-0C / %x0E-7F)
inline const auto quoted_pair = bsx3::lit( '\\' ) >>
                                ( bsx3::char_( '\x00', '\x09' ) | bsx3::char_( '\x0B', '\x0C' ) | bsx3::char_( '\x0E', '\x7F' ) );

// qdtext = LWS / %x21 / %x23-5B / %x5D-7E / UTF8-NONASCII (!!!)
inline const auto qdtext = LWS | bsx3::char_( '\x21' ) | bsx3::char_( '\x23', '\x5B' ) | bsx3::char_( '\x5D', '\x7E' );

// quoted-string = SWS DQUOTE *(qdtext / quoted-pair ) DQUOTE
inline const auto quoted_string = SWS > DQUOTE > *( qdtext | quoted_pair ) > DQUOTE;

// token = 1*(alphanum / "-" / "." / "!" / "%" / "*" / "_" / "+" / "`" / "'" / "~" )
inline const auto token = +( alphanum | bsx3::char_( "-.!%*_+`'~" ) );

// mark = "-" / "_" / "." / "!" / "~" / "*" / "'" / "(" / ")"
inline const auto mark = bsx3::char_( "-_.!~*'()" );

// unreserved = alphanum / mark
inline const auto unreserved = alphanum | mark;

// reserved = ";" / "/" / "?" / ":" / "@" / "&" / "=" / "+" / "$" / ","
inline const auto reserved = bsx3::char_( ";/?:@&=+$," );

// escaped = "%" HEXDIG HEXDIG
inline const auto escaped = bsx3::rule<struct _espaced, char>{} = '%' > bsx3::uint_parser<std::uint8_t, 16, 2, 2>{};

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
inline const auto SIP_Version = bsx3::rule<struct _sip_version, CppSip::Message::SipVersion>{} =
    bsx3::lit( "SIP/" ) >> bsx3::uint32 >> '.' >> bsx3::uint32;

// word = 1*( alphanum / "-" / "." / "!" / "%" / "*" / "_" / "+" / "`" / "'" / "~" / "(" / ")" / "<" / ">" / ":" / "\" / DQUOTE / "/" / "["
// / "]" / "?" / "{" / "}" )
inline const auto word = +( alphanum | bsx3::char_( "-.!%*_+`'~()<>:\\\"/[]?{}" ) );

// callid = word[ "@" word ]
inline const auto callid = bsx3::rule<struct _callid, std::string>{} = word >> -( bsx3::char_( '@' ) > word );


}  // namespace Parsers
}  // namespace CppSip
