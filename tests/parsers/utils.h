#pragma once

#include "boost/spirit/home/x3.hpp"

#include "boost/test/data/monomorphic/generators/xrange.hpp"
#include "boost/test/data/test_case.hpp"

#include <stdexcept>
#include <string>

namespace BoostTestData = boost::unit_test::data;

template <typename Attr, typename Parser>
Attr parse( Parser parser, const std::string_view input )
{
  Attr attr;

  auto begin = input.begin();
  auto end   = input.end();

  const bool parsed = boost::spirit::x3::parse( begin, end, parser, attr );
  if ( !parsed || begin != end )
  {
    throw std::runtime_error( "failed to parse" );
  }

  return attr;
}

template <typename Parser>
void parse_noattr( Parser parser, const std::string_view input )
{
  auto begin = input.begin();
  auto end   = input.end();

  const bool parsed = boost::spirit::x3::parse( begin, end, parser );
  if ( !parsed || begin != end )
  {
    throw std::runtime_error( "failed to parse" );
  }
}

#define define_parser( parser, type )                                                                                                      \
  type parse_##parser( const std::string_view input )                                                                                      \
  {                                                                                                                                        \
    return parse<type>( CppSip::Parsers::parser, input );                                                                                  \
  }

#define define_raw_parser( parser )                                                                                                        \
  bool parse_##parser( const std::string_view input )                                                                                      \
  {                                                                                                                                        \
    return input == parse<std::string>( boost::spirit::x3::raw[ CppSip::Parsers::parser ], input );                                        \
  }

#define define_noattr_parser( parser )                                                                                                     \
  void parse_##parser( const std::string_view input )                                                                                      \
  {                                                                                                                                        \
    parse_noattr( CppSip::Parsers::parser, input );                                                                                        \
  }
