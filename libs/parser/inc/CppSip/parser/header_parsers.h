#pragma once

#include "CppSip/message/headers/headers.h"
#include "CppSip/parser/common_parsers.h"

#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/spirit/home/x3.hpp"

BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Header::CSeq, id, method )

namespace CppSip
{
namespace Parsers
{

// word = 1*( alphanum / "-" / "." / "!" / "%" / "*" / "_" / "+" / "`" / "'" / "~" / "(" / ")" / "<" / ">" / ":" / "\" / DQUOTE / "/" / "["
// / "]" / "?" / "{" / "}" )
inline const auto word = +( alphanum | bsx3::char_( "-.!%*_+`'~()<>:\\\"/[]?{}" ) );

// callid = word[ "@" word ]
inline const auto callid = word >> -( bsx3::char_( '@' ) > word );

// Call-ID = ( "Call-ID" / "i" ) HCOLON callid
inline const auto Call_ID = ( bsx3::lit( "Call-ID" ) | bsx3::lit( 'i' ) ) > HCOLON > callid;

// CSeq  =  "CSeq" HCOLON 1*DIGIT LWS Method
inline const auto CSEQ = bsx3::lit( "CSeq" ) > HCOLON > +DIGIT > LWS > Method;

// Max-Forwards = "Max-Forwards" HCOLON 1*DIGIT
inline const auto Max_Forwards = bsx3::lit( "Max-Forwards" ) > HCOLON > +DIGIT;

}  // namespace Parsers
}  // namespace CppSip
