#pragma once

#include "CppSip/parser/abnf_core_parsers.h"

#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/spirit/home/x3.hpp"

#include "CppSip/message/headers/cseq.h"
#include "CppSip/message/method.h"
#include "CppSip/message/sip_version.h"

BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Header::CSeq, id, method )
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

// CSeq  =  "CSeq" HCOLON 1*DIGIT LWS Method
inline const auto CSEQ = bsx3::lit( "CSeq" ) > HCOLON > +DIGIT > LWS > Method;

// SIP-Version = "SIP" "/" 1*DIGIT "." 1*DIGIT
inline const auto SIP_Version = bsx3::rule<struct _sip_version, CppSip::Message::SipVersion>{} = bsx3::lit( "SIP/" ) >> +bsx3::digit >>
                                                                                                 bsx3::lit( '.' ) >> +bsx3::digit;

}  // namespace Parsers
}  // namespace CppSip