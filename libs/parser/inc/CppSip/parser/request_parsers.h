#pragma once

#include "CppSip/message/request/request.h"
#include "CppSip/parser/abnf_core_parsers.h"
#include "CppSip/parser/common_parsers.h"

#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/spirit/home/x3.hpp"

BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::HostPort, host, port )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::IPv4Address, a, b, c, d )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::RequestLine, method, request_uri, sip_version );
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::RequestUri, sip_uri );
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::SipUri, sips, host_port )

namespace CppSip
{
namespace Parsers
{

namespace bsx3 = boost::spirit::x3;

// domainlabel = alphanum / alphanum *( alphanum / "-" ) alphanum
inline const auto domainchar  = alphanum | bsx3::char_( '-' );
inline const auto domainlabel = alphanum > -( *( domainchar >> &domainchar ) >> alphanum );

// toplabel = ALPHA / ALPHA *( alphanum / "-" ) alphanum
inline const auto toplabel = ALPHA > -( *( domainchar >> &domainchar ) >> alphanum );

// hostname = *( domainlabel "." ) toplabel [ "." ]
inline const auto hostname = bsx3::rule<struct _hostname, std::string>{} = *( domainlabel >> bsx3::char_( '.' ) >> &alphanum ) >>
                                                                           toplabel >> -bsx3::char_( '.' );

// port = 1*DIGIT
inline const auto port = bsx3::rule<struct _port, std::string>{} = +bsx3::digit;

// h16 = 1*4HEXDIG
inline const auto h16 = bsx3::uint_parser<std::uint16_t, 16, 1, 4>{};

// dec-octet = DIGIT               ; 0-9
//             / %x31-39 DIGIT     ; 10-99
//             / "1" 2DIGIT        ; 100-199
//             / "2" %x30-34 DIGIT ; 200-249
//             / "25" %x30-35      ; 250-255
inline const auto dec_octet = bsx3::uint8;

// IPv4address = 1*3DIGIT "." 1*3DIGIT "." 1*3DIGIT "." 1*3DIGIT
inline const auto IPv4address = bsx3::rule<struct _ipv4address, CppSip::Message::IPv4Address>{} =
    dec_octet > '.' > dec_octet > '.' > dec_octet > '.' > dec_octet;

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
inline const auto host = bsx3::rule<struct _host, CppSip::Message::Host>{} = hostname | IPv4address;

// hostport = host [ ":" port ]
inline const auto hostport = bsx3::rule<struct _host_port, CppSip::Message::HostPort>{} = host >> -( ':' >> port );

// SIP-URI = "sip:" [ userinfo ] hostport uri-parameters [ headers ] (!!!)
inline const auto SIP_URI = bsx3::rule<struct _sip_uri, CppSip::Message::SipUri>{} = bsx3::lit( "sip:" ) > bsx3::attr( false ) > hostport;

// SIPS-URI = "sips:" [ userinfo ] hostport uri-parameters [ headers ] (!!!)
inline const auto SIPS_URI = bsx3::rule<struct _sips_uri, CppSip::Message::SipUri>{} = bsx3::lit( "sips:" ) > bsx3::attr( true ) > hostport;

// Request-URI = SIP-URI / SIPS-URI / absoluteURI (!!!)
inline const auto Request_URI = bsx3::rule<struct _request_uri, CppSip::Message::RequestUri>{} = SIP_URI | SIPS_URI;

// Request-Line = Method SP Request-URI SP SIP-Version CRLF
inline const auto Request_Line = bsx3::rule<struct _request_line, CppSip::Message::RequestLine>{} =
    Method > SP > Request_URI > SP > SIP_Version > CRLF;



}  // namespace Parsers
}  // namespace CppSip
