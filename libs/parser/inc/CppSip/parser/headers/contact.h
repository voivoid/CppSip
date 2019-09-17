#pragma once

#include "CppSip/message/headers/contact.h"

#include "CppSip/parser/common.h"
#include "CppSip/parser/headers/common.h"

#include "boost/fusion/include/adapt_struct.hpp"

namespace CppSip
{
namespace Parsers
{

namespace bsx3 = boost::spirit::x3;

// c-p-q = "q" EQUAL qvalue
inline const auto c_p_q = bsx3::rule<struct _c_p_q, std::string>{ "c_p_q" } = bsx3::no_case[ bsx3::lit( 'q' ) ] > EQUAL > qvalue;

// delta-seconds = 1*DIGIT
inline const auto delta_seconds = bsx3::uint32;

// c-p-expires = "expires" EQUAL delta-seconds
inline const auto c_p_expires = bsx3::no_case[ bsx3::lit( "expires" ) ] > EQUAL > delta_seconds;

// contact-extension = generic-param
inline const auto contact_extension = bsx3::rule<struct _contact_extension, bsx3::unused_type>{ "contact-extension" } = generic_param;

// contact-params = c-p-q / c-p-expires / contact-extension
inline const auto contact_params = bsx3::rule<struct _contact_params, bsx3::unused_type>{ "contact-params" } =
    contact_extension | c_p_q | c_p_expires;

// contact-param = (name-addr / addr-spec) *(SEMI contact-params)
inline const auto contact_param = bsx3::rule<struct _contact_param, bsx3::unused_type>{ "contact-param" } = ( name_addr | addr_spec ) >
                                                                                                            *( SEMI > contact_params );

// Contact = ("Contact" / "m" ) HCOLON  ( STAR / (contact-param *(COMMA contact-param)))
inline const auto Contact = bsx3::rule<struct _contact, bsx3::unused_type>{
  "Contact"
} = ( bsx3::no_case[ ( bsx3::lit( "Contact" ) | 'm' ) ] >> HCOLON ) > ( STAR | ( contact_param % COMMA ) );

}  // namespace Parsers
}  // namespace CppSip
