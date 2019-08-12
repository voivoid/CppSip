#include "CppSip/parser/parser.h"

#include <stdexcept>

namespace CppSip
{
  Method parse_method( const std::string_view method)
  {
    if (method == "ACK")
    {
      return Method::Ack;
    }
    else if (method == "BYE")
    {
      return Method::Bye;
    }
    else if (method == "CANCEL")
    {
      return Method::Cancel;
    }
    else if (method == "INVITE")
    {
      return Method::Invite;
    }
    else if ( method == "OPTIONS" )
    {
      return Method::Options;
    }
    else if (method == "REGISTER")
    {
      return Method::Register;
    }

    throw std::invalid_argument("unknown SIP method");
  }
}