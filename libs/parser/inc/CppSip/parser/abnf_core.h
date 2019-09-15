#pragma once

#include "boost/spirit/home/x3.hpp"

namespace CppSip
{
namespace Parsers
{

namespace bsx3 = boost::spirit::x3;

// ALPHA = %x41-5A / %x61-7A ; A-Z / a-z
inline const auto ALPHA = bsx3::char_( 'A', 'Z' ) | bsx3::char_( 'a', 'z' );

// DIGIT = %x30-39 ; 0-9
inline const auto DIGIT = bsx3::char_( '0', '9' );

// DQUOTE = %x22 ; " (Double Quote)
inline const auto DQUOTE = bsx3::lit( '"' );

// HEXDIG =  DIGIT / "A" / "B" / "C" / "D" / "E" / "F"
inline const auto HEXDIG = DIGIT | bsx3::char_( 'A', 'F' ) | bsx3::char_( 'a', 'f' );

// SP = %x20 ; space
inline const auto SP = bsx3::lit( ' ' );

// CR = %x0D ; carriage return
inline const auto CR = bsx3::lit( char( 0x0D ) );

// LF = %x0A ; linefeed
inline const auto LF = bsx3::lit( char( 0x0A ) );

// HTAB = % x09; horizontal tab
inline const auto HTAB = bsx3::lit( char( 0x09 ) );

// WSP = SP / HTAB; white space
inline const auto WSP = SP | HTAB;

// CRLF = CR LF ; Internet standard newline
inline const auto CRLF = CR >> LF;

}  // namespace Parsers
}  // namespace CppSip
