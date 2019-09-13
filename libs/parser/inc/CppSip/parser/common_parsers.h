#pragma once

#include "CppSip/parser/abnf_core_parsers.h"

#include "boost/fusion/container/vector.hpp"
#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/spirit/home/x3.hpp"

#include "CppSip/message/address.h"
#include "CppSip/message/method.h"
#include "CppSip/message/sip_uri.h"
#include "CppSip/message/sip_version.h"
#include "CppSip/message/userinfo.h"

BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::HostPort, host, port )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::IPv4Address, a, b, c, d )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::SipVersion, major, minor )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::SipUri, sips, userinfo, host_port, headers )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::SipUriHeader, name, value )
BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::UserInfo, user, password )

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
inline const auto SLASH = ( SWS >> '/' ) > SWS;

// SEMI = SWS ";" SWS; semicolon
inline const auto SEMI = ( SWS >> ';' ) > SWS;

// EQUAL = SWS "=" SWS; equal
inline const auto EQUAL = ( SWS >> '=' ) > SWS;

// RAQUOT  =  ">" SWS ; right angle quote
inline const auto RAQUOT = '>' >> SWS;

// LAQUOT  =  SWS "<"; left angle quote
inline const auto LAQUOT = SWS >> '<';

// quoted-pair = "\" (%x00-09 / %x0B-0C / %x0E-7F)
inline const auto quoted_pair = '\\' >>
                                ( bsx3::char_( '\x00', '\x09' ) | bsx3::char_( '\x0B', '\x0C' ) | bsx3::char_( '\x0E', '\x7F' ) );

// qdtext = LWS / %x21 / %x23-5B / %x5D-7E / UTF8-NONASCII (!!!)
inline const auto qdtext = LWS | bsx3::char_( '\x21' ) | bsx3::char_( '\x23', '\x5B' ) | bsx3::char_( '\x5D', '\x7E' );

// quoted-string = SWS DQUOTE *(qdtext / quoted-pair ) DQUOTE
inline const auto quoted_string = ( SWS >> DQUOTE ) > *( qdtext | quoted_pair ) > DQUOTE;

// token = 1*(alphanum / "-" / "." / "!" / "%" / "*" / "_" / "+" / "`" / "'" / "~" )
inline const auto token = bsx3::rule<struct _token, std::string>{} = +( alphanum | bsx3::char_( "-.!%*_+`'~" ) );

// mark = "-" / "_" / "." / "!" / "~" / "*" / "'" / "(" / ")"
inline const auto mark = bsx3::char_( "-_.!~*'()" );

// unreserved = alphanum / mark
inline const auto unreserved = alphanum | mark;

// reserved = ";" / "/" / "?" / ":" / "@" / "&" / "=" / "+" / "$" / ","
inline const auto reserved = bsx3::char_( ";/?:@&=+$," );

// escaped = "%" HEXDIG HEXDIG
inline const auto escaped = bsx3::rule<struct _espaced, char>{} = '%' >> bsx3::uint_parser<std::uint8_t, 16, 2, 2>{};

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
    bsx3::no_case[ "SIP/" ] >> bsx3::uint32 >> '.' >> bsx3::uint32;

// word = 1*( alphanum / "-" / "." / "!" / "%" / "*" / "_" / "+" / "`" / "'" / "~" / "(" / ")" / "<" / ">" / ":" / "\" / DQUOTE / "/" / "["
// / "]" / "?" / "{" / "}" )
inline const auto word = +( alphanum | bsx3::char_( "-.!%*_+`'~()<>:\\\"/[]?{}" ) );

// callid = word[ "@" word ]
inline const auto callid = bsx3::rule<struct _callid, std::string>{} = word >> -( bsx3::char_( '@' ) > word );

// hnv-unreserved  =  "[" / "]" / "/" / "?" / ":" / "+" / "$"
inline const auto hnv_unreserved = bsx3::char_( "[]/?:+$" );

// hvalue          =  *( hnv-unreserved / unreserved / escaped )
inline const auto hvalue = bsx3::rule<struct _hvalue, CppSip::Message::SipUriHeader::Value>{} = *( hnv_unreserved | unreserved | escaped );

// hname           =  1*( hnv-unreserved / unreserved / escaped )
inline const auto hname = bsx3::rule<struct _hvalue, CppSip::Message::SipUriHeader::Name>{} = +( hnv_unreserved | unreserved | escaped );

// header          =  hname "=" hvalue
inline const auto header = bsx3::rule<struct _header, CppSip::Message::SipUriHeader>{} = hname > '=' > hvalue;

// headers         =  "?" header *( "&" header )
inline const auto headers = bsx3::rule<struct _headers, CppSip::Message::SipUriHeaders>{} = '?' > header > *( '&' > header );

// domainlabel = alphanum / alphanum *( alphanum / "-" ) alphanum
inline const auto domainchar  = alphanum | bsx3::char_( '-' );
inline const auto domainlabel = alphanum > -( *( domainchar >> &domainchar ) >> alphanum );

// toplabel = ALPHA / ALPHA *( alphanum / "-" ) alphanum
inline const auto toplabel = ALPHA > -( *( domainchar >> &domainchar ) >> alphanum );

// hostname = *( domainlabel "." ) toplabel [ "." ]
inline const auto hostname = bsx3::rule<struct _hostname, CppSip::Message::HostName>{} = *( domainlabel >> bsx3::char_( '.' ) >>
                                                                                            &alphanum ) >>
                                                                                         toplabel >> -bsx3::char_( '.' );

// port = 1*DIGIT
inline const auto port = bsx3::rule<struct _port, CppSip::Message::Port>{} = bsx3::uint16;

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

// IPv6reference = "[" IPv6address "]"
inline const auto IPv6reference = '[' > IPv6address > ']';

// host = hostname / IPv4address / IPv6reference (!!!)
inline const auto host = bsx3::rule<struct _host, CppSip::Message::Host>{} = hostname | IPv4address;

// hostport = host [ ":" port ]
inline const auto hostport = bsx3::rule<struct _host_port, CppSip::Message::HostPort>{} = host >> -( ':' >> port );

// password = *( unreserved / escaped / "&" / "=" / "+" / "$" / "," )
inline const auto password = *( unreserved | escaped | bsx3::char_( "&=+$," ) );

// user-unreserved = "&" / "=" / "+" / "$" / "," / ";" / "?" / "/"
inline const auto user_unreserved = bsx3::char_( "&=+$,;?/" );

// user = 1*( unreserved / escaped / user-unreserved )
inline const auto user = +( unreserved | escaped | user_unreserved );

// userinfo = ( user / telephone-subscriber ) [ ":" password ] "@" (!!!)
inline const auto userinfo = bsx3::rule<struct _userinfo, CppSip::Message::UserInfo>{} = user >> -( ':' >> password ) >> '@';

// SIP-URI = "sip:" [ userinfo ] hostport uri-parameters [ headers ] (!!!)
inline const auto SIP_URI = bsx3::rule<struct _sip_uri, CppSip::Message::SipUri>{} = bsx3::no_case[ "sip:" ] >
                                                                                     bsx3::attr( false ) > -userinfo > hostport > -headers;
// SIPS-URI = "sips:" [ userinfo ] hostport uri-parameters [ headers ] (!!!)
inline const auto SIPS_URI = bsx3::rule<struct _sips_uri, CppSip::Message::SipUri>{} = bsx3::no_case[ "sips:" ] >
                                                                                       bsx3::attr( true ) > -userinfo > hostport > -headers;


}  // namespace Parsers
}  // namespace CppSip
