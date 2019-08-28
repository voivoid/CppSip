#pragma once

#include "CppSip/message/message.h"
#include "CppSip/parser/abnf_core_parsers.h"

#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/spirit/home/x3.hpp"

#include <stdexcept>

BOOST_FUSION_ADAPT_STRUCT( CppSip::SipVersion, major, minor )
BOOST_FUSION_ADAPT_STRUCT( CppSip::HostPort, host, port )
BOOST_FUSION_ADAPT_STRUCT( CppSip::IPaddress, a, b, c, d )

namespace CppSip
{
namespace Parsers
{

namespace bsx3 = boost::spirit::x3;

// alphanum = ALPHA / DIGIT
inline const auto alphanum = ALPHA | DIGIT;

// domainlabel = alphanum / alphanum *( alphanum / "-" ) alphanum
inline const auto domainchar  = alphanum | bsx3::char_( '-' );
inline const auto domainlabel = alphanum > -( *( domainchar >> &domainchar ) >> alphanum );

// toplabel = ALPHA / ALPHA *( alphanum / "-" ) alphanum
inline const auto toplabel = ALPHA > -( *( domainchar >> &domainchar ) >> alphanum );

// hostname = *( domainlabel "." ) toplabel [ "." ]
inline const auto hostname = *( domainlabel >> bsx3::char_( '.' ) >> &alphanum ) > toplabel > -bsx3::char_( '.' );

// port = 1*DIGIT
inline const auto port = bsx3::uint_[ ( []( auto& ctx ) {
  auto& attr = _attr( ctx );

  if ( attr > 65535 )
    _pass( ctx ) = false;
  else
    _val( ctx ) = attr;
} ) ];

// hex4 = 1*4HEXDIG
inline const auto hex4 = bsx3::hex;

// hexseq = hex4 *( ":" hex4)
inline const auto hexseq = hex4 >> *( ':' > hex4 );

// hexpart = hexseq / hexseq "::" [ hexseq ] / "::" [ hexseq ]
inline const auto hexpart = hexseq | ( hexseq > "::" > -hexseq ) | ( "::" > -hexseq );

// IPv4address = 1*3DIGIT "." 1*3DIGIT "." 1*3DIGIT "." 1*3DIGIT
inline const auto IPv4address = bsx3::uint8 > '.' > bsx3::uint8 > '.' > bsx3::uint8 > '.' > bsx3::uint8;

// IPv6address = hexpart [ ":" IPv4address ]

// IPv6reference = "[" IPv6address "]" (!!!) UPDATE ACCORDING TO RFC 5954

// host = hostname / IPv4address / IPv6reference (!!!)
inline const auto host = hostname | IPv4address;

// hostport = host [ ":" port ]
inline const auto hostport = host >> port;

// SIP-URI = "sip:" [ userinfo ] hostport uri-parameters [ headers ] (!!!)
inline const auto SIP_URI = bsx3::lit( "sip:" );

// SIPS-URI = "sips:" [ userinfo ] hostport uri-parameters [ headers ] (!!!)
inline const auto SIPS_URI = bsx3::lit( "sips:" );

// Request-URI = SIP-URI / SIPS-URI / absoluteURI (!!!)
inline const auto Request_URI = SIP_URI | SIPS_URI;

// SIP-Version = "SIP" "/" 1*DIGIT "." 1*DIGIT
inline const auto SIP_Version = bsx3::lit( "SIP/" ) >> bsx3::uint_ >> bsx3::lit( '.' ) >> bsx3::uint_;

// Method = INVITEm / ACKm / OPTIONSm / BYEm / CANCELm / REGISTERm /
// extension-method (!!!)
bsx3::symbols<CppSip::Method> get_Method_parser()
{
  bsx3::symbols<CppSip::Method> method_symbols;
  method_symbols.add( "ACK", Method::Ack )( "BYE", Method::Bye )( "CANCEL", Method::Cancel )( "INVITE", Method::Invite )(
      "OPTIONS", Method::Options )( "REGISTER", Method::Register );

  return method_symbols;
}
inline const auto Method = get_Method_parser();

}  // namespace Parsers
}  // namespace CppSip
