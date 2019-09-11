#include "parse_cmd_line.h"
#include "run_parser.h"

#include "boost/functional/overloaded_function.hpp"

#include <iostream>
#include <stdexcept>

namespace
{
void exec_show_help( const SipParserApp::HelpCmd& cmd )
{
  std::cout << cmd.help_message << std::endl;
}

void exec_parse( const SipParserApp::ParseCmd& cmd )
{
  SipParserApp::parse( cmd.parser );
}

int safe_main( int argc, char* argv[] )
{
  auto cmd = SipParserApp::parse_cmd_line( argc, argv );

  const auto cmd_visitor = boost::make_overloaded_function( &exec_show_help, &exec_parse );
  std::visit( cmd_visitor, cmd );

  return 0;
}

}  // namespace

int main( int argc, char* argv[] )
{
  try
  {
    return safe_main( argc, argv );
  }
  catch ( const std::exception& ex )
  {
    std::cerr << "Unhandled exception: " << ex.what() << std::endl;
    return 1;
  }
  catch ( ... )
  {
    std::cerr << "Unhandled unknown exception" << std::endl;
    return 1;
  }
}
