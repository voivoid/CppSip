#include "run_parser.h"

#include "CppSip/parser/message_parser.h"

#include "boost/hof/lift.hpp"
#include "boost/spirit/include/support_istream_iterator.hpp"

#include <functional>
#include <iostream>
#include <unordered_map>

namespace
{
template <typename Parser>
bool parse_stdin( const Parser& parser )
{
  boost::spirit::istream_iterator begin( std::cin >> std::noskipws ), end;

  const bool is_parsed = boost::spirit::x3::parse( begin, end, parser );
  if ( !is_parsed || begin != end )
  {
    return false;
  }

  return true;
}

#define CPPSIP_CURRY_PARSER( P ) std::bind( BOOST_HOF_LIFT( parse_stdin ), CppSip::Parsers::P )

using ParseFunc = std::function<bool()>;
const auto& get_parse_map()
{
  // clang-format off
  static std::unordered_map<std::string_view, ParseFunc> map = {
    // ABNF
    { "ALPHA", CPPSIP_CURRY_PARSER( ALPHA ) },
    { "CR", CPPSIP_CURRY_PARSER( CR ) },
    { "CRLF", CPPSIP_CURRY_PARSER( CRLF ) },
    { "DIGIT", CPPSIP_CURRY_PARSER( DIGIT ) },
    { "DQUOTE", CPPSIP_CURRY_PARSER( DQUOTE ) },
    { "HEXDIG", CPPSIP_CURRY_PARSER( HEXDIG ) },
    { "HTAB", CPPSIP_CURRY_PARSER( HTAB ) },
    { "LF", CPPSIP_CURRY_PARSER( LF ) },
    { "SP", CPPSIP_CURRY_PARSER( SP ) },
    { "WSP", CPPSIP_CURRY_PARSER( WSP ) },

    // COMMON
    { "alphanum", CPPSIP_CURRY_PARSER( alphanum ) },
    { "LWS", CPPSIP_CURRY_PARSER( LWS ) },
    { "SWS", CPPSIP_CURRY_PARSER( SWS ) },
    { "HCOLON", CPPSIP_CURRY_PARSER( HCOLON ) },

    { "token", CPPSIP_CURRY_PARSER( token ) },

    // HEADERS

    // REQUEST

    // RESPONSE

    // MESSAGE
    { "SIP-message", CPPSIP_CURRY_PARSER( SIP_message ) }
  };
  // clang-format on
  return map;
}

}  // namespace

namespace SipParserApp
{
void parse( const std::string_view& parser_name )
{
  auto parser_iter = get_parse_map().find( parser_name );
  if ( parser_iter == get_parse_map().cend() )
  {
    throw std::runtime_error( "Unknown parser name" );
  }

  const auto& [ _, run_parser ] = *parser_iter;
  const bool is_parsed          = run_parser();

  if ( !is_parsed )
  {
    throw std::runtime_error( "Parser failed" );
  }
}
}  // namespace SipParserApp
