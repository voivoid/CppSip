#include "parse_cmd_line.h"

#include "boost/program_options.hpp"

namespace SipParserApp
{
std::variant<ParseCmd, HelpCmd> parse_cmd_line( const int argc, char** const argv )
{
  boost::program_options::options_description description( "Settings" );
  description.add_options()( "help", "show help message" )( "parser", boost::program_options::value<std::string>(), "parser name" );

  boost::program_options::positional_options_description po_description;
  po_description.add( "parser", -1 );

  boost::program_options::variables_map vars_map;
  boost::program_options::store(
      boost::program_options::command_line_parser( argc, argv ).options( description ).positional( po_description ).run(), vars_map );

  boost::program_options::notify( vars_map );
  if ( vars_map.count( "parser" ) )
  {
    return ParseCmd{ vars_map[ "problem" ].as<std::string>() };
  }

  std::ostringstream ss;
  description.print( ss );
  return HelpCmd{ ss.str() };
}
}  // namespace SipParserApp
