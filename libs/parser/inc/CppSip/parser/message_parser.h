#pragma once

#include "CppSip/message/message.h"
#include "CppSip/parser/abnf_core_parsers.h"

#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/spirit/home/x3.hpp"

#include <stdexcept>

BOOST_FUSION_ADAPT_STRUCT( CppSip::SipVersion, major, minor )
BOOST_FUSION_ADAPT_STRUCT( CppSip::HostPort, host, port )
BOOST_FUSION_ADAPT_STRUCT( CppSip::IPv4Address, a, b, c, d )

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
inline const auto hostname = bsx3::rule<struct _hostname, std::string>{} = *( domainlabel >> bsx3::char_( '.' ) >> &alphanum ) >> toplabel >> -bsx3::char_( '.' );

// port = 1*DIGIT
inline const auto port = bsx3::uint16;

// h16 = 1*4HEXDIG
inline const auto h16 = bsx3::uint_parser<std::uint16_t, 16, 1, 4>{};

// dec-octet = DIGIT               ; 0-9
//             / %x31-39 DIGIT     ; 10-99
//             / "1" 2DIGIT        ; 100-199
//             / "2" %x30-34 DIGIT ; 200-249
//             / "25" %x30-35      ; 250-255
inline const auto dec_octet = bsx3::uint8;

// IPv4address = 1*3DIGIT "." 1*3DIGIT "." 1*3DIGIT "." 1*3DIGIT
inline const auto IPv4address = bsx3::rule<struct _ipv4address, CppSip::IPv4Address>{} = dec_octet > '.' > dec_octet > '.' > dec_octet > '.' > dec_octet;

// ls32 = ( h16 ":" h16 ) / IPv4address
inline const auto ls32 = ( h16 >> ':' >> h16 ) | IPv4address;

// According to RFC5954:
//
// IPv6address =                              6( h16 ":" ) ls32
//               /                       "::" 5( h16 ":" ) ls32
//               / [               h16 ] "::" 4( h16 ":" ) ls32
//               / [ *1( h16 ":" ) h16 ] "::" 3( h16 ":" ) ls32
//               / [ *2( h16 ":" ) h16 ] "::" 2( h16 ":" ) ls32
//               / [ *3( h16 ":" ) h16 ] "::" h16 ":" ls32
//               / [ *4( h16 ":" ) h16 ] "::" ls32
//               / [ *5( h16 ":" ) h16 ] "::" h16
//               / [ *6( h16 ":" ) h16 ] "::"            (!!!)
// clang-format off
inline const auto IPv6address = (                            bsx3::repeat(6)[ h16 >> ':' ] >> ls32 |
                                                     "::" >> bsx3::repeat(5)[ h16 >> ':' ] >> ls32 |
                                           -h16   >> "::" >> bsx3::repeat(4)[ h16 >> ':' ] >> ls32 |
   -( bsx3::repeat( 0, 1 )[ h16 >> ':' ] >> h16 ) >> "::" >> bsx3::repeat(3)[ h16 >> ':' ] >> ls32 |
   -( bsx3::repeat( 0, 2 )[ h16 >> ':' ] >> h16 ) >> "::" >> bsx3::repeat(2)[ h16 >> ':' ] >> ls32 |
   -( bsx3::repeat( 0, 3 )[ h16 >> ':' ] >> h16 ) >> "::" >> bsx3::repeat(1)[ h16 >> ':' ] >> ls32 |
   -( bsx3::repeat( 0, 4 )[ h16 >> ':' ] >> h16 ) >> "::" >> ls32                                  |
   -( bsx3::repeat( 0, 5 )[ h16 >> ':' ] >> h16 ) >> "::" >> h16                                   |
   -( bsx3::repeat( 0, 6 )[ h16 >> ':' ] >> h16 ) >> "::"
);
// clang-format on

// host = hostname / IPv4address / IPv6address (!!!)
inline const auto host = bsx3::rule<struct _host, CppSip::Host>{} = hostname | IPv4address;

// hostport = host [ ":" port ]
inline const auto hostport = bsx3::rule<struct _hostport, CppSip::HostPort>{} = host >> -( ':' >> port );

// SIP-URI = "sip:" [ userinfo ] hostport uri-parameters [ headers ] (!!!)
inline const auto SIP_URI = bsx3::lit( "sip:" ) > hostport;

// SIPS-URI = "sips:" [ userinfo ] hostport uri-parameters [ headers ] (!!!)
inline const auto SIPS_URI = bsx3::lit( "sips:" ) > hostport;

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

// Request-Line = Method SP Request-URI SP SIP-Version CRLF
inline const auto Request_Line = Method > SP > Request_URI > SP > SIP_Version > CRLF;

}  // namespace Parsers
}  // namespace CppSip
