#include "CppSip/parser/parser.h"
#include "CppSip/parser/parser_utils.h"

#include <stdexcept>

namespace CppSip { namespace Parsers {
  namespace
  {
    bsx3::symbols<Method> get_method_parser()
    {
      namespace x3 = boost::spirit::x3;

      x3::symbols<Method> method_symbols;
      method_symbols.add("ACK", Method::Ack)("BYE", Method::Bye)("CANCEL", Method::Cancel)("INVITE", Method::Invite)("OPTIONS", Method::Options)("REGISTER", Method::Register);

      return method_symbols;
    }
  }

  const bsx3::symbols<Method> method = get_method_parser();

} }