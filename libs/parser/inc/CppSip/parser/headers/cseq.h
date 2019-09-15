#pragma once

#include "CppSip/message/headers/cseq.h"

#include "CppSip/parser/common.h"

#include "boost/fusion/include/adapt_struct.hpp"

BOOST_FUSION_ADAPT_STRUCT( CppSip::Message::Headers::CSeq, id, method )

namespace CppSip
{
namespace Parsers
{

// CSeq  =  "CSeq" HCOLON 1*DIGIT LWS Method
inline const auto CSeq = bsx3::rule<struct _cseq, CppSip::Message::Headers::CSeq>{ "CSeq" } =
    bsx3::no_case[ "CSeq" ] > HCOLON > +DIGIT > LWS > Method;

}  // namespace Parsers
}  // namespace CppSip
