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

#if defined( CPPSIP_CURRY_PARSER ) || defined( CPPSIP_PARSER_ITEM ) || defined( CPPSIP_PARSER_ITEM2 )
#  error macro redefinition
#endif

#define CPPSIP_CURRY_PARSER( P ) std::bind( BOOST_HOF_LIFT( parse_stdin ), CppSip::Parsers::P )
#define CPPSIP_PARSER_ITEM_WITH_NAME( PNAME, PF )                                                                                          \
  {                                                                                                                                        \
    PNAME, CPPSIP_CURRY_PARSER( PF )                                                                                                       \
  }
#define CPPSIP_PARSER_ITEM( P ) CPPSIP_PARSER_ITEM_WITH_NAME( #P, P )

using ParseFunc = std::function<bool()>;
const auto& get_parse_map()
{
  // clang-format off
  static std::unordered_map<std::string_view, ParseFunc> map = {
    // ABNF
    CPPSIP_PARSER_ITEM( ALPHA ),
    CPPSIP_PARSER_ITEM( CR ),
    CPPSIP_PARSER_ITEM( CRLF ),
    CPPSIP_PARSER_ITEM( DIGIT ),
    CPPSIP_PARSER_ITEM( DQUOTE ),
    CPPSIP_PARSER_ITEM( HEXDIG ),
    CPPSIP_PARSER_ITEM( HTAB ),
    CPPSIP_PARSER_ITEM( LF ),
    CPPSIP_PARSER_ITEM( SP ),
    CPPSIP_PARSER_ITEM( WSP ),

    // COMMON
    CPPSIP_PARSER_ITEM( alphanum ),
    CPPSIP_PARSER_ITEM( LWS ),
    CPPSIP_PARSER_ITEM( SWS ),
    CPPSIP_PARSER_ITEM( HCOLON ),

    CPPSIP_PARSER_ITEM( SLASH ),
    CPPSIP_PARSER_ITEM( SEMI ),
    CPPSIP_PARSER_ITEM( EQUAL ),
    CPPSIP_PARSER_ITEM( RAQUOT ),
    CPPSIP_PARSER_ITEM( LAQUOT ),

    CPPSIP_PARSER_ITEM_WITH_NAME( "quoted-pair", quoted_pair ),
    CPPSIP_PARSER_ITEM_WITH_NAME( "quoted-string", quoted_string ),
    CPPSIP_PARSER_ITEM( qdtext ),

    CPPSIP_PARSER_ITEM( token ),
    CPPSIP_PARSER_ITEM( mark ),
    CPPSIP_PARSER_ITEM( unreserved ),
    CPPSIP_PARSER_ITEM( reserved ),
    CPPSIP_PARSER_ITEM( escaped ),

    CPPSIP_PARSER_ITEM( Method ),
    CPPSIP_PARSER_ITEM_WITH_NAME( "SIP-Version", SIP_Version ),
    CPPSIP_PARSER_ITEM( word ),
    CPPSIP_PARSER_ITEM( callid ),
    CPPSIP_PARSER_ITEM_WITH_NAME( "hnv-unreserved", hnv_unreserved ),
    CPPSIP_PARSER_ITEM( hvalue ),
    CPPSIP_PARSER_ITEM( hname ),
    CPPSIP_PARSER_ITEM( header ),
    CPPSIP_PARSER_ITEM( headers ),
    CPPSIP_PARSER_ITEM( domainlabel ),
    CPPSIP_PARSER_ITEM( toplabel ),
    CPPSIP_PARSER_ITEM( hostname ),
    CPPSIP_PARSER_ITEM( port ),
    CPPSIP_PARSER_ITEM( h16 ),
    CPPSIP_PARSER_ITEM_WITH_NAME("dec-octet", dec_octet ),
    CPPSIP_PARSER_ITEM( IPv4address ),
    CPPSIP_PARSER_ITEM( ls32 ),
    CPPSIP_PARSER_ITEM( IPv6address ),
    CPPSIP_PARSER_ITEM( host ),
    CPPSIP_PARSER_ITEM( hostport ),
    CPPSIP_PARSER_ITEM( password ),
    CPPSIP_PARSER_ITEM_WITH_NAME( "user-unreserved", user_unreserved ),
    CPPSIP_PARSER_ITEM( user ),
    CPPSIP_PARSER_ITEM( userinfo ),
    CPPSIP_PARSER_ITEM_WITH_NAME( "SIP-URI", SIP_URI ),
    CPPSIP_PARSER_ITEM_WITH_NAME( "SIPS-URI", SIPS_URI ),


    // HEADERS

    // REQUEST

    // RESPONSE

    // MESSAGE
    CPPSIP_PARSER_ITEM_WITH_NAME( "SIP-message", SIP_message )
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
