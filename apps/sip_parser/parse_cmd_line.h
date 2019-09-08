#pragma once

#include <string>
#include <variant>

namespace SipParserApp
{
  struct ParseCmd
  {
    std::string parser;
  };

  struct HelpCmd
  {
    std::string help_message;
  };

  std::variant<ParseCmd, HelpCmd> parse_cmd_line(int argc, char** const argv);
}